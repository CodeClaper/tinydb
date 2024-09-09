/*
 * ============================= The pager manger ================================
 * The pager manager supports manipulating disk data ways.
 * Page is the basic unit of which data is store/read/written to disk and memory.
 * PAGE_SIZE is the size of a page and data length of each IO operation.
 * ===============================================================================
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include "pager.h"
#include "cache.h"
#include "mmu.h"
#include "log.h"
#include "utils.h"
#include "ltree.h"
#include "table.h"


static List *FDESC_LIST = NULL;

/* Register FDescEntry. */
static void register_fdesc(char *table_name, int file_descriptor) {

    if (is_null(FDESC_LIST))
        FDESC_LIST = create_list(NODE_VOID);

    FDescEntry *entry = instance(FDescEntry);
    entry->file_descriptor = file_descriptor;
    strcpy(entry->table_name, table_name);
    append_list(FDESC_LIST, entry);
}


/* Find file descriptor in FDESC_LIST. 
 * Return file descriptor or -1 if not found.
 * */
static int find_fdesc(char *table_name) {
    
    if (FDESC_LIST) {
        ListCell *lc;
        foreach(lc, FDESC_LIST) {
            FDescEntry *entry = lfirst(lc);
            if (streq(entry->table_name, table_name))
                return entry->file_descriptor;
        }
    }

    return -1;
}


/* Load file descriptor. */
static int load_file_descriptor(char *file_path) {
    int file_descriptor = open(file_path, O_RDWR, S_IRUSR | S_IWUSR);
    if (file_descriptor == -1) 
        db_log(PANIC, "Open table file %d fail: %s.", file_path, strerror(errno));

    return file_descriptor;
}

/* For mult-processor model, it will reload the table file descriptor. */
void reload_file_descriptor(Pager *pager, char *table_name) {

    Assert(pager);
    Assert(table_name);

    int file_descriptor = find_fdesc(table_name);
    if (file_descriptor != -1) 
    {
        pager->file_descriptor = file_descriptor;
    }
    else 
    {
        Assert(pager->table_file_path);
        file_descriptor = load_file_descriptor(pager->table_file_path);
        pager->file_descriptor = file_descriptor;
        register_fdesc(table_name, file_descriptor);
    }
}


/* Open the pager. */
Pager *open_pager(char *table_file_path) {
    Pager *pager = instance(Pager);

    int file_descriptor = load_file_descriptor(table_file_path);

    off_t file_length = lseek(file_descriptor, 0, SEEK_END);
    if (file_length == -1)
        db_log(PANIC, "Error seeking: %s.", strerror(errno));
    
    pager->file_descriptor = file_descriptor;
    pager->table_file_path = db_strdup(table_file_path);
    pager->file_length = file_length;
    pager->size = (file_length / PAGE_SIZE);

    if (file_length % PAGE_SIZE != 0) 
        db_log(PANIC, "Db file is not a whole number pages");

    for (int i = 0; i < MAX_TABLE_PAGE; i++) {
        pager->pages[i] = NULL;
    }

    return pager;
}

/* Get page of a pager by page number. */
void *get_page(char *table_name, Pager *pager, uint32_t page_num) {

    /* Exceeds limitation check. */
    if (page_num >= MAX_TABLE_PAGE)
        db_log(PANIC, "Try to fetch page number out of bounds: %d >= %d", 
               page_num, 
               MAX_TABLE_PAGE);

    /* Cache dismiss, allocate memory and load file. */
    if (pager->pages[page_num] == NULL) {

        void *page = db_malloc(PAGE_SIZE, "pointer");
        lseek(pager->file_descriptor, page_num * PAGE_SIZE, SEEK_SET);
        ssize_t read_bytes = read(pager->file_descriptor, page, PAGE_SIZE);
        if (read_bytes == -1) 
            db_log(PANIC, "Table file read error: %s", strerror(errno));

        pager->pages[page_num] = page;

        /* synchronous memory page data. */
        sync_page(table_name, page_num, page);
    }

    /* Page extends and synchronous page size. */
    if (page_num >= pager->size) {
        pager->size++;
        sync_page_size(table_name, pager->size);
    }

    return pager->pages[page_num];
}


/* Flush page. 
 * Just make page FLUSH_STATE flag. */
void flush_page(char *table_name, Pager *pager, uint32_t page_num) {

    Assert(pager->pages[page_num]);

    void *node = pager->pages[page_num];

    set_node_state(node, FLUSH_STATE);
}


/* Flush Table. */
static void flush_table(Table *table) {

    Pager *pager = table->pager;

    uint32_t i;
    for (i = 0; i < pager->size; i++) {

        void *node = pager->pages[i];

        Assert(node);

        if (get_node_state(node) == FLUSH_STATE) {
    
            /* Reset to INUSE_STATE. */
            set_node_state(node, INUSE_STATE);

            /* Before flushing disk, synchronous page memory data. 
             * If synchronous page memory fail, not to flush disk. */
            if(!sync_page(table->meta_table->table_name, i, node))
                return;

            /* Flush disk. */
            off_t offset = lseek(pager->file_descriptor, PAGE_SIZE * i, SEEK_SET);
            if (offset == -1) 
                db_log(PANIC, "Error seeking: %s.", strerror(errno));
            
            /* Write. */
            ssize_t write_size = write(pager->file_descriptor, node, PAGE_SIZE);
            if (write_size == -1) 
                db_log(PANIC, "Try to write page error: %s.", strerror(errno));        
        }
    }

}

/* Flush all to disk. */
void flush(char *table_name) {

    Table *table = open_table(table_name);
    
    /* Flush self table. */
    flush_table(table);
    
    /* Flush refer tables. */
    uint32_t j;
    for (j = 0; j < table->meta_table->column_size; j++) {
        MetaColumn *meta_column = table->meta_table->meta_column[j];
        if (meta_column->column_type == T_REFERENCE) {
            char *table_name = meta_column->table_name;
            flush(table_name);
        }
    }
}

/* Close Pager. */
void close_pager(Pager *pager) {
    close(pager->file_descriptor);
}
