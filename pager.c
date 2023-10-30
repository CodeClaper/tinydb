#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include "pager.h"
#include "mem.h"
#include "misc.h"

//Open Pager
Pager *open_pager(char *table_file_path){
    Pager *pager = db_malloc(sizeof(Pager));
    int file_descriptor = open(table_file_path, O_RDWR, S_IRUSR | S_IWUSR);
    if (file_descriptor == -1) {
        fprintf(stderr, "Open table file fail.\n");
        exit(EXIT_FAILURE);
    }
    off_t file_length = lseek(file_descriptor, 0, SEEK_END);
    pager->file_descriptor = file_descriptor;
    pager->file_length = file_length;
    pager->num_page = (file_length / PAGE_SIZE);

    if (file_length % PAGE_SIZE != 0) {
        fatal("Db file is not a whole number pages");
    }
    for(uint32_t i = 0; i < MAX_TABLE_PAGE ; i++) {
        pager->pages[i] = NULL;
    }
    return pager;
}

// Get page of a pager by page number.
void *get_page(Pager *pager, int page_num) {
    if (page_num >= MAX_TABLE_PAGE) {
        fprintf(stderr, "Try to fetch page number out of bounds: %d >= %d", page_num, MAX_TABLE_PAGE);
        exit(1);
    }
    if (pager->pages[page_num] == NULL) {
        //Cache dismiss, allocate memory and load file.
        void *page = db_malloc(PAGE_SIZE);
        lseek(pager->file_descriptor, page_num * PAGE_SIZE, SEEK_SET);
        ssize_t read_bytes = read(pager->file_descriptor, page, PAGE_SIZE);
        if (read_bytes == -1) {
            fatald("Table file read error and errno", errno);
        }
        pager->pages[page_num] = page;
    }
    if (page_num >= pager->num_page) {
        pager->num_page++;
    }
    return pager->pages[page_num];
}


// flush page to disk
void flush_page(Pager *pager, uint32_t page_num) {
    if (pager->pages[page_num] == NULL) {
        fatal("Tried to flush null page to disk");
    } 
    off_t offset = lseek(pager->file_descriptor, PAGE_SIZE * page_num, SEEK_SET);
    if (offset == -1) {
        printf("Error seeking: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    ssize_t write_size = write(pager->file_descriptor, pager->pages[page_num], PAGE_SIZE);
    if (write_size == -1) {
        fatald("Try to write page error and errno", errno);        
    }
}
