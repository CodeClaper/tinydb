/****************************************List Modele********************************************
 * Intface of List package.
 ***********************************************************************************************
 **/

#include <stdint.h>
#include <string.h>
#include "list.h"
#include "data.h"
#include "mmu.h"
#include "asserts.h"

/* Create List and initialization. 
 * Return the created list.
 * */
List *create_list(NodeTag type) {
    List *list = instance(List);
    list->type = type;
    list->size = 0;
    list->capacity = INIT_LIST_CELL_SIZE;
    list->elements = list->initial_elements;
    return list;
}

/* Enlarge the list and expand the capacity. 
 * List will growth capacity with the power of 2. 
 * */
static void enlarge_list(List *list) {
    list->capacity = list->capacity * 2;
    
    if (list->elements == list->initial_elements) {
        list->elements = db_malloc(sizeof(ListCell) * list->capacity, "pointer");
        memcpy(list->elements, list->initial_elements, sizeof(ListCell) * list->size);
    } else {
        list->elements = db_realloc(list->elements, sizeof(ListCell) * list->capacity);
    }
}

static inline ListCell *last_cell(List *list) {
    Assert(list != NIL);
    return &list->elements[list->size - 1];
}

/* Append item to list. 
 * Return current number of items in list.
 * */
List *append_list(List *list, void *item) {
    if (list->size >= list->capacity)
        enlarge_list(list);
    list->size++;
    lfirst(last_cell(list)) = item;
    return list;
}

/* Locate the n'th cell (counting from 0) of the list.
 * It is an assertion failure if there is no such cell.
 * */
ListCell *list_nth_cell(List *list, int nth) {
    Assert(list != NIL);
    Assert(nth >= 0 && nth < list->size);

    return &list->elements[nth];
}


/* Free all cells and objects that are 
 * point-to by cells in list DOES NOT be freed*/
void free_list(List *list) {
    
    if (list != NIL) {

        if (list->elements != list->initial_elements)
            db_free(list->elements);

        db_free(list);
    }
}

/* Free all cells and any object that are 
 * point-to by cells in list will be freed*/
void free_list_deep(List *list) {
    
    if (list != NIL) {
        int32_t i;
        for (i = 0; i < list->size; i++) {
            db_free(lfirst(&list->elements[i]));
        }

        if (list->elements != list->initial_elements)
            db_free(list->elements);

        db_free(list);
    }
}

