/****************************************List Modele********************************************
 * Intface of List package.
 ***********************************************************************************************
 **/

#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include "list.h"
#include "mmu.h"
#include "free.h"
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

/* Append int item to list. */
void append_list_int(List *list, int item) {
    if (list->size >= list->capacity)
        enlarge_list(list);
    list->size++;
    lfirst_int(last_cell(list)) = item;
}

/* Append bool item to list. */
void append_list_bool(List *list, bool item) {
    if (list->size >= list->capacity)
        enlarge_list(list);
    list->size++;
    lfirst_bool(last_cell(list)) = item;
}

/* Append float item to list. */
void append_list_float(List *list, float item) {
    if (list->size >= list->capacity)
        enlarge_list(list);
    list->size++;
    lfirst_float(last_cell(list)) = item;
}

/* Append float item to list. */
void append_list_double(List *list, double item) {
    if (list->size >= list->capacity)
        enlarge_list(list);
    list->size++;
    lfirst_double(last_cell(list)) = item;
}

void append_list_ptr(List *list, void *item) {
    if (list->size >= list->capacity)
        enlarge_list(list);
    list->size++;
    lfirst(last_cell(list)) = item;
}

/* Append item to list. */
void append_list(List *list, void *item) {
    switch (list->type) {
        case NODE_INT:
            append_list_int(list, *(int *)item);
            break;
        case NODE_BOOL:
            append_list_bool(list, *(bool *)item);
            break;
        case NODE_FLOAT:
            append_list_float(list, *(float *)item);
            break;
        case NODE_DOUBLE:
            append_list_double(list, *(double *)item);
            break;
        default:
            append_list_ptr(list, item);
            break;
    }
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
        switch (list->type) {
            case NODE_INT:
            case NODE_BOOL:
            case NODE_FLOAT:
            case NODE_DOUBLE:
                break;
            case NODE_LIST: {
                ListCell *lc;
                foreach (lc, list) {
                    free_list_deep(lfirst(lc));
                }
                break;
            }
            case NODE_STRING: {
                ListCell *lc;
                foreach (lc, list) {
                    db_free(lfirst(lc));
                }
                break;
            }
            case NODE_KEY_VALUE: {
                ListCell *lc;
                foreach (lc, list) {
                    free_key_value(lfirst(lc));
                }
                break;
            }
            case NODE_ROW: {
                ListCell *lc;
                foreach (lc, list) {
                    free_row(lfirst(lc));
                }
                break;
            }
            case NODE_DB_RESULT: {
                ListCell *lc;
                foreach (lc, list) {
                    free_db_result(lfirst(lc));
                }
                break;
            }
            case NODE_COLUMN_DEF_NODE: {
                ListCell *lc;
                foreach (lc, list) {
                    free_column_def_node(lfirst(lc));
                }
                break;
            }
        }

        if (list->elements != list->initial_elements)
            db_free(list->elements);

        db_free(list);
    }
}

/* List is empty. */
bool list_empty(List *list) {
    return list->size == 0;
}
