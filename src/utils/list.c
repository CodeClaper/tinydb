/* =======================================List Modele============================================
 * List module supports api portals for multiple values.
 * We don`t limit data type of set, the set is set of pointer. 
 * so the destroy function will not free them.
 * ==============================================================================================
 * */

#include <string.h>
#include <time.h>
#include "data.h"
#include "mmu.h"

/* Create List and initialization. 
 * Return the created list.
 * */
List *create_list() {
    List *list = instance(List);
    list->size = 0;
    list->set = db_malloc(0, "pointer");
    return list;
}

/* Append item to list. 
 * Return current number of items in list.
 * */
int append_list(List *list, void *item) {
    list->set = db_realloc(list->set, sizeof(void *) * (list->size + 1));
    list->set[list->size++] = item;
    return list->size;
}

/* Append item to list at index. 
 * Return the index of the new item in list.
 * Return -1 if fail.
 * */
int append_at(List *list, void *item, int index) {
    if (index > list->size || index < 0)
        return -1;
    list->set = db_realloc(list->set, sizeof(void *) * (list->size++));
    int i;
    for (i = list->size; i > index; i--) {
        memcpy(list->set + i, list->set + i - 1, sizeof(void *));
    }
    list->set[index] = item;
    return index;
}

/* Destroy list. 
 * Note: it will not free set items which are left to be freed by origin.
 */
void destroy_list(List *list) {
    if (list) {
        db_free(list->set);
        db_free(list);
    }
}

/*Deplicate list.
 *Note: it will not duplicate set items.
 * */
List *duplicate_list(List *list) {
    if (!list)
        return NULL;
    List *list_dup = instance(List);
    list_dup->size = list->size;
    list_dup->set = db_malloc(sizeof(void *) * list_dup->size, "pointer");
    memcpy(list_dup->set, list->set, sizeof(void *) * list_dup->size);
    return list_dup;
}
