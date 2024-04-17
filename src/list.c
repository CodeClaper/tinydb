#include <string.h>
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
 * Note: it will not free the items which left to free by origin.
 */
void destroy_list(List *list) {
    if (list) {
        db_free(list->set);
        db_free(list);
    }
}
