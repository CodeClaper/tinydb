/*
 * ============================= The pager manger ================================
 * The pager manager supports manipulating disk data ways.
 * Page is the basic unit of which data is store/read/written to disk and memory.
 * PAGE_SIZE is the size of a page and data length of each IO operation.
 * ===============================================================================
 */
#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include "pager.h"
#include "cache.h"
#include "mmu.h"
#include "log.h"

/* Get file descriptor. */
static int get_file_descriptor(char *file_path) {
    int file_descriptor = open(file_path, O_RDWR, S_IRUSR | S_IWUSR);
    if (file_descriptor == -1) 
        db_log(PANIC, "Open table file %d fail.", file_path);

    return file_descriptor;
}

/* For mult-processor model, it will need reload the table file descriptor. */
void reload_file_descriptor(Pager *pager) {
    Assert(pager->table_file_path);
    int file_descriptor = get_file_descriptor(pager->table_file_path);
    pager->file_descriptor = file_descriptor;
}


/* Open the pager. */
Pager *open_pager(char *table_file_path) {
    Pager *pager = instance(Pager);

    int file_descriptor = get_file_descriptor(table_file_path);

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
        if (read_bytes == -1) {
            db_log(PANIC, "Table file read error and errno: %d", errno);
        }
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


/* Flush page to disk. */
void flush_page(char *table_name, Pager *pager, uint32_t page_num) {
    if (pager->pages[page_num] == NULL) {
        db_log(PANIC, "Tried to flush null to disk page.");
        return;
    } 

    /* Before flushing disk, synchronous page memory data. 
     * If synchronous page memory fail, not to flush disk. */
    if(!sync_page(table_name, page_num, pager->pages[page_num]))
        return;

    db_log(DEBUGER, "Pid %d is acquire file descriptor %d", 
           getpid(), 
           pager->file_descriptor);

    /* Flush disk. */
    off_t offset = lseek(pager->file_descriptor, PAGE_SIZE * page_num, SEEK_SET);
    if (offset == -1) 
        db_log(PANIC, "Error seeking: %s.", strerror(errno));
    
    /* Write. */
    ssize_t write_size = write(pager->file_descriptor, pager->pages[page_num], PAGE_SIZE);
    if (write_size == -1) 
        db_log(PANIC, "Try to write page error and errno", errno);        
}

/* Flush all to disk. */
void flush(Pager pager) {}
