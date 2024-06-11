#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "show.h"
#include "mmu.h"
#include "common.h"
#include "utils.h"
#include "mmu.h"
#include "free.h"
#include "copy.h"
#include "list.h"
#include "session.h"
#include "asserts.h"
#include "jsonwriter.h"
#include "log.h"
#include "type.h"
#include "timer.h"

#define KB_THRESHOLD 1024
#define MB_THRESHOLD 1024 * KB_THRESHOLD
#define GB_THRESHOLD 1024 * MB_THRESHOLD

/*Gen table map list.*/
static List *gen_table_map_list() {
    List *list = create_list(NODE_LIST);

    DIR *dir;
    struct dirent *entry;
    if ((dir = opendir(conf->data_dir)) ==NULL) 
        db_log(PANIC, "System error, not found directory: ", conf->data_dir); 
    else {
        while((entry = readdir(dir)) != NULL) {
            if (entry->d_type == 8 && endwith(entry->d_name, ".dbt")) {
                /* map */
                List *child_list = create_list(NODE_KEY_VALUE);

                struct stat info;
                char full_path[BUFF_SIZE];
                sprintf(full_path,"%s%s", conf->data_dir, entry->d_name);
                assert_true(stat(full_path, &info) == 0, "Try to get file '%s' info fail.", full_path);

                /* name */
                append_list(child_list, new_key_value(db_strdup("table_name"), 
                                                replace_once(entry->d_name, ".dbt", ""), 
                                                T_STRING));

                /* size */
                append_list(child_list, new_key_value(db_strdup("table_size"), 
                                                copy_value(&info.st_size, T_INT), 
                                                T_INT));

                /* blk_size */
                append_list(child_list, new_key_value(db_strdup("blk_size"),
                                                copy_value(&info.st_blksize, T_INT), 
                                                T_INT));

                /* create_time */
                append_list(child_list, new_key_value(db_strdup("create_time"),
                                                format_time("%Y-%m-%d", info.st_ctim.tv_sec), 
                                                T_STRING));

                append_list(list, child_list);
            }
        }
        closedir(dir);
    }
    return list;
}

/* Generate memory info. */
static List *gen_memory_map_list() {

    List *list = create_list(NODE_KEY_VALUE);

    /* Used memory. */
    size_t mmsize = db_memesize();
    append_list(list, new_key_value(db_strdup("used_memory"), 
                                    copy_value(&mmsize, T_LONG), 
                                    T_LONG));

    /* Mtable capacity. */
    uint32_t cap = mtable_capacity();
    append_list(list, new_key_value(db_strdup("mtable_capacity"), 
                                    copy_value(&cap, T_INT), 
                                    T_INT));

    /* MEntry number. */
    uint32_t num = mentry_num();
    append_list(list, new_key_value(db_strdup("mtable_capacity"), 
                                    copy_value(&num, T_INT), 
                                    T_INT));

    return list;
}

/* Execute show statement. */
void exec_show_statement(ShowNode *show_node, DBResult *result) {
    switch(show_node->type) {
        case SHOW_TABLES: {
            List *map_list = gen_table_map_list();
            result->success = true;
            result->data = map_list;
            result->message = db_strdup("Show tables executed successfully.");
            db_log(SUCCESS, "Show tables executed successfully."); 
            break;
        }
        case SHOW_MEMORY: {
            List *map_list = gen_memory_map_list();
            result->success = true;
            result->data = map_list;
            result->message = db_strdup("Show memory executed successfully.");
            db_log(SUCCESS, "Show memory executed successfully."); 
            break;
        }
    }
}

