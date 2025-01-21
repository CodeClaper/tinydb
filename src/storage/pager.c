/********************************** Pager Manager Module **************************************************
 * Auth:        JerryZhou
 * Created:     2023/12/19
 * Modify:      2024/11/26
 * Locataion:   src/storage/pager.c
 * Description: The pager manager supports the ways to manipulate the disk file data.
 * One page is the basic unit of which data is store/read/write to disk and memory.
 * PAGE_SIZE is the size of a page and data length of each IO operation.
 * Not recommand that you get data via the pager manager direactly, but the buffer manager indireactly.
 ***********************************************************************************************************
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
#include "log.h"
#include "mmgr.h"
#include "utils.h"
#include "ltree.h"
#include "table.h"
#include "fdesc.h"
#include "bufmgr.h"

/* Open the pager. */
Pager *open_pager(char *table_name) {
    Pager *pager = instance(Pager);

    FDesc fdesc = get_file_desc(table_name);

    off_t file_length = lseek(fdesc, 0, SEEK_END);
    if (file_length == -1)
        db_log(PANIC, "Error seek end: %s.", strerror(errno));
    
    pager->table_name = dstrdup(table_name);
    pager->file_length = file_length;
    pager->size = (file_length / PAGE_SIZE);
    pager->pages = create_list(NODE_PAGE);
    pager->buffers = create_list(NODE_BUFFER_DESC);

    if (file_length % PAGE_SIZE != 0) 
        db_log(PANIC, "Db file is not a whole number pages");

    for (int i = 0; i < pager->size; i++) {
        append_list(pager->pages, NULL);
        append_list(pager->buffers, NULL);
    }

    Assert(len_list(pager->pages) == pager->size);

    return pager;
}

/* Get page of a pager by page number. */
void *get_page(char *table_name, Pager *pager, uint32_t page_num) {

    /* Exceeds limitation check. */
    if (page_num >= MAX_TABLE_PAGE) {
        db_log(PANIC, "Try to fetch page number out of bounds: %d >= %d", 
               page_num, MAX_TABLE_PAGE);
    }

    /* Get the file descriptor. */
    FDesc fdesc = get_file_desc(table_name);

    /* Exceeds the pager. */
    if (page_num >= pager->size) {
        Assert(page_num == pager->size);

        switch_shared();

        /* Generate new Page.*/
        void *page = dalloc(PAGE_SIZE);
        lseek(fdesc, page_num * PAGE_SIZE, SEEK_SET);
        ssize_t read_bytes = read(fdesc, page, PAGE_SIZE);
        if (read_bytes == -1) 
            db_log(PANIC, "Table file read error: %s", strerror(errno));

        append_list(pager->pages, page);
        pager->size++;
        Assert(len_list(pager->pages) == pager->size);

        switch_local();
        return page;
    }

    ListCell *lc = list_nth_cell(pager->pages, page_num);

    /* Cache dismiss, allocate memory and load file. */
    if (is_null(lfirst(lc))) {
        switch_shared();

        void *page = dalloc(PAGE_SIZE);

        lseek(fdesc, page_num * PAGE_SIZE, SEEK_SET);
        ssize_t read_bytes = read(fdesc, page, PAGE_SIZE);
        if (read_bytes == -1) 
            db_log(PANIC, "Table file read error: %s", strerror(errno));

        lfirst(lc) = page;

        switch_local();
    }

    return lfirst(lc);
}


/* Make page dirty. 
 * This function will not flush page to disk, 
 * just make page dirty. */
void make_page_dirty(char *table_name, Pager *pager, uint32_t page_num) {
    void *node = get_page(table_name, pager, page_num);
    Assert(node != NULL);
    /* Mark FLUSH_STATE flag. */
    set_node_state(node, DIRTY_STATE);
}


/* Flush Table. */
static void flush_disk(Table *table) {
    Pager *pager = table->pager;

    uint32_t i;
    for (i = 0; i < pager->size; i++) {
        void *node = get_page(table->meta_table->table_name, pager, i);
        Assert(node != NULL);

        /* Only flush FLUSH_STATE page to disk. */
        if (get_node_state(node) == DIRTY_STATE) {
            /* Reset to INUSE_STATE. */
            set_node_state(node, INUSE_STATE);

            /* Flush disk. */
            FDesc fdesc = get_file_desc(pager->table_name);
            off_t offset = lseek(fdesc, PAGE_SIZE * i, SEEK_SET);
            if (offset == -1) 
                db_log(PANIC, "Error seek set: %s. File descriptor: %d", 
                       strerror(errno), fdesc);
            
            /* Write. */
            ssize_t write_size = write(fdesc, node, PAGE_SIZE);
            if (write_size == -1) 
                db_log(PANIC, "Try to write page error: %s.", strerror(errno));        
        }
    }
}

/* Flush all to disk. */
void flush(char *table_name) {

    Table *table = open_table(table_name);
    
    /* Flush self table. */
    flush_disk(table);
    
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
