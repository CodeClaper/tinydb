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
#include "misc.h"
#include "utils.h"
#include "mmu.h"
#include "free.h"
#include "copy.h"
#include "session.h"
#include "asserts.h"
#include "ret.h"
#include "timer.h"

#define KB_THRESHOLD 1024
#define MB_THRESHOLD 1024 * KB_THRESHOLD
#define GB_THRESHOLD 1024 * MB_THRESHOLD

/*Gen table map list.*/
static MapList *gen_table_map_list() {
    DIR *dir;
    struct dirent *entry;
    MapList *map_list = db_malloc2(sizeof(MapList), "MapList");
    map_list->size = 0;
    map_list->data = db_malloc2(0, "MapList.data");
    if ((dir = opendir(conf->data_dir)) ==NULL) 
        fatals("System error, not found directory: ", conf->data_dir); 
    else {
        while((entry = readdir(dir)) != NULL) {
            if (entry->d_type == 8 && endwith(entry->d_name, ".dbt")) {

                /* map */
                Map *map = db_malloc2(sizeof(Map), "Map");
                map->size = 3;
                map->body = db_malloc2(sizeof(KeyValue *) * map->size, "Map.body");

                struct stat info;
                char full_path[BUFF_SIZE];
                sprintf(full_path,"%s%s", conf->data_dir, entry->d_name);
                assert_true(stat(full_path, &info) == 0, "Try to get file '%s' info fail.", full_path);

                /* name */
                KeyValue *key_value_name = db_malloc2(sizeof(KeyValue), "KeyValue");
                key_value_name->key = strdup("table_name");
                key_value_name->value = replace(entry->d_name, ".dbt", "");
                key_value_name->data_type = T_STRING;
                map->body[0] = key_value_name;

                /* size */
                KeyValue *key_value_size = db_malloc2(sizeof(KeyValue), "KeyValue");
                key_value_size->key = strdup("table_size");
                key_value_size->value = copy_value(&info.st_size, T_INT, NULL);
                key_value_size->data_type = T_INT;
                map->body[1] = key_value_size;

                /* create_time */
                KeyValue *key_value_created = db_malloc2(sizeof(KeyValue), "KeyValue");
                key_value_created->key = strdup("create_time");
                key_value_created->value = format_time("%Y-%m-%d", info.st_ctim.tv_sec);
                key_value_created->data_type = T_STRING;
                map->body[2] = key_value_created;

                map_list->size++;
                map_list->data = db_realloc(map_list->data, sizeof(Map *) * map_list->size);
                map_list->data[map_list->size - 1] = map;
            }
        }
        closedir(dir);
    }
    return map_list;
}

/* Generate memory info. */
static MapList *gen_memory_map_list() {

    /* map_list */
    MapList *map_list = db_malloc2(sizeof(MapList), "MapList");
    map_list->size = 1;
    map_list->data = db_malloc2(sizeof(Map *) * map_list->size, "MapList.data");

    /* map */
    Map *map = db_malloc2(sizeof(Map), "Map");
    map->size = 3;
    map->body = db_malloc2(sizeof(KeyValue *) * map->size, "Map.body");
    
    /* used_memory. */
    KeyValue *key_value_mem = db_malloc2(sizeof(KeyValue), "KeyValue");
    uint32_t mmsize = db_memesize();
    key_value_mem->key = strdup("used_memory");
    key_value_mem->value = copy_value(&mmsize, T_INT, NULL);
    key_value_mem->data_type = T_INT;
    map->body[0] = key_value_mem;

    KeyValue *key_value_cap = db_malloc2(sizeof(KeyValue), "KeyValue");
    uint32_t cap = mtable_capacity();
    key_value_cap->key = strdup("mtable_capacity");
    key_value_cap->value = copy_value(&cap, T_INT, NULL);
    key_value_cap->data_type = T_INT;
    map->body[1] = key_value_cap;

    KeyValue *key_value_num = db_malloc2(sizeof(KeyValue), "KeyValue");
    uint32_t num = mentry_num();
    key_value_num->key = strdup("mentry_num");
    key_value_num->value = copy_value(&num, T_INT, NULL);
    key_value_num->data_type = T_INT;
    map->body[2] = key_value_num;

    map_list->data[0] = map;

    return map_list;
}

/* Execute show statement. */
void exec_show_statement(ShowNode *show_node, DBResult *result) {
    switch(show_node->type) {
        case SHOW_TABLES: {
            MapList *map_list = gen_table_map_list();
            success_result(result, "Show tables executed successfully."); 
            result->data = map_list;
            break;
        }
        case SHOW_MEMORY: {
            MapList *map_list = gen_memory_map_list();
            success_result(result, "Show memory executed successfully."); 
            result->data = map_list;
            break;
        }
    }
}

