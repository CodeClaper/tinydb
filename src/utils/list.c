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
#include "data.h"
#include "copy.h"

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

/* Check if the int item is the member of list. */
bool list_member_int(List *list, int item) {
    ListCell *lc;
    foreach (lc, list) {
        if (lfirst_int(lc) == item) 
            return true;
    }
    return false;
}

/* Check if the bool item is the member of list. */
bool list_member_bool(List *list, bool item) {
    ListCell *lc;
    foreach (lc, list) {
        if (lfirst_bool(lc) == item) 
            return true;
    }
    return false;
}

/* Check if the float item is the member of list. */
bool list_member_float(List *list, float item) {
    ListCell *lc;
    foreach (lc, list) {
        if (lfirst_float(lc) == item) 
            return true;
    }
    return false;
}

/* Check if the double item is the member of list. */
bool list_member_double(List *list, double item) {
    ListCell *lc;
    foreach (lc, list) {
        if (lfirst_double(lc) == item) 
            return true;
    }
    return false;
}

/* Check if the pointer is the member of list. */
bool list_member_ptr(List *list, void *ptr) {
    ListCell *lc;
    foreach (lc, list) {
        if (lfirst(lc) == ptr) 
            return true;
    }
    return false;
}

/* Check if the item is the memeber of list. */
bool list_member(List *list, void *item) {
    switch (list->type) {
        case NODE_INT:
            return list_member_int(list, *(int *)item);
        case NODE_BOOL:
            return list_member_bool(list, *(bool *)item);
        case NODE_FLOAT:
            return list_member_float(list, *(float *)item);
        case NODE_DOUBLE:
            return list_member_double(list, *(double *)item);
        default:
            return list_member_ptr(list, item);
    }
}


/* Delete nth cell in List. */
void list_delete_nth_cell(List *list, int n) {
    Assert(n >= 0 && n < list->size);
    memcpy(list->elements + n, list->elements + n + 1, 
           sizeof(ListCell) * (list->size - n - 1));
}

/* Delete ListCell in List. */
void list_delete_cell(List *list, ListCell *lc) {
    list_delete_nth_cell(list, lc - list->elements);
}

/* Delete int item in List. 
 * Skip if not found in list.
 * */
void list_delete_int(List *list, int item) {
    ListCell *lc;
    foreach (lc, list) {
        if (lfirst_int(lc) == item) {
            list_delete_cell(list, lc);
        }
    }
}

/* Delete bool item in List. 
 * Skip if not found in list.
 * */
void list_delete_bool(List *list, bool item) {
    ListCell *lc;
    foreach (lc, list) {
        if (lfirst_bool(lc) == item) {
            list_delete_cell(list, lc);
        }
    }
}

/* Delete float item in List. 
 * Skip if not found in list.
 * */
void list_delete_float(List *list, float item) {

    ListCell *lc;
    foreach (lc, list) {
        if (lfirst_float(lc) == item) {
            list_delete_cell(list, lc);
        }
    }
}


/* Delete double item in List. 
 * Skip if not found in list.
 * */
void list_delete_double(List *list, double item) {

    ListCell *lc;
    foreach (lc, list) {
        if (lfirst_double(lc) == item) {
            list_delete_cell(list, lc);
        }
    }
}

/* Delete pointer item in List. 
 * Skip if not found in list.
 * */
void list_delete_ptr(List *list, void *item) {

    ListCell *lc;
    foreach (lc, list) {
        if (lfirst(lc) == item) {
            list_delete_cell(list, lc);
        }
    }
}

/* Delete item in List. 
 * Skip if not found in list.
 * Note: if item is a pointer, 
 * this function will not automatically free the memory.
 * */
void list_delete(List *list, void *item) {
    
    switch (list->type) {
        case NODE_INT:
            list_delete_int(list, *(int *)item);
            break;
        case NODE_BOOL:
            list_delete_bool(list, *(bool *)item);
            break;
        case NODE_FLOAT:
            list_delete_float(list, *(float *)item);
            break;
        case NODE_DOUBLE:
            list_delete_double(list, *(double *)item);
            break;
        default:
            list_delete_ptr(list, item);
            break;
    }
}


/* List copy shallow. 
 * Notice: the replica list must be free`d by free_list if necessary.
 * */
List *list_copy(List *old_list) {
    if (old_list == NIL)
        return NIL;

    List *new_list = create_list(old_list->type);
    new_list->size = old_list->size;
    new_list->capacity = old_list->capacity;
    memcpy(new_list->initial_elements, old_list->initial_elements, sizeof(ListCell) * INIT_LIST_CELL_SIZE);
    
    if (old_list->elements == old_list->initial_elements) {
        new_list->elements = new_list->initial_elements;
    } else {
        new_list->elements = db_malloc(sizeof(ListCell) * new_list->capacity, "pointer");
        memcpy(new_list->elements, old_list->elements, sizeof(ListCell) * new_list->size);
    }
    return new_list;
}

/* List copy deep. 
 * Notice: the replica list must be free`d by free_list_deep if necessary.
 * */
List *list_copy_deep(List *old_list) {
    if (old_list == NIL)
        return NIL;

    List *new_list = create_list(old_list->type);

    switch (new_list->type) {
        case NODE_INT: {
            ListCell *lc;
            foreach (lc, old_list) {
                append_list_int(new_list, lfirst_int(lc));
            }
            break;
        }
        case NODE_BOOL: {
            ListCell *lc;
            foreach (lc, old_list) {
                append_list_bool(new_list, lfirst_bool(lc));
            }
            break;
        }
        case NODE_FLOAT: {
            ListCell *lc;
            foreach (lc, old_list) {
                append_list_float(new_list, lfirst_float(lc));
            }
            break;
        }
        case NODE_DOUBLE: {
            ListCell *lc;
            foreach (lc, old_list) {
                append_list_double(new_list, lfirst_double(lc));
            }
            break;
        }
        case NODE_STRING: {
            ListCell *lc;
            foreach (lc, old_list) {
                char *replica = db_strdup(lfirst(lc));
                append_list(new_list, replica);
            }
            break;
        }
        case NODE_SCALAR_EXP: {
            ListCell *lc;
            foreach (lc, old_list) {
                ScalarExpNode *replica = copy_scalar_exp_node(lfirst(lc));
                append_list_ptr(new_list, replica);
            }
            break;
        }
        case NODE_VALUE_ITEM: {
            ListCell *lc;
            foreach (lc, old_list) {
                ValueItemNode *replica = copy_value_item_node(lfirst(lc));
                append_list_ptr(new_list, replica);
            }
            break;
        }
        case NODE_TABLE_REFER: {
            ListCell *lc;
            foreach (lc, old_list) {
                TableRefNode *replica = copy_table_ref_node(lfirst(lc));
                append_list(new_list, replica);
            }
            break;
        }
        default:
            UNEXPECTED_VALUE("Not support this node to copy.");
    }
    return new_list;
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
            case NODE_VOID: {
                ListCell *lc;
                foreach (lc, list) {
                    db_free(lfirst(lc));
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
            case NODE_REFER: {
                ListCell *lc;
                foreach (lc, list) {
                    free_refer(lfirst(lc));
                }
                break;
            }
            case NODE_COLUMN: {
                ListCell *lc;
                foreach (lc, list) {
                    free_column_node(lfirst(lc));
                }
                break;
            }
            case NODE_STATEMENT: {
                ListCell *lc;
                foreach (lc, list) {
                    free_statement(lfirst(lc));
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
            case NODE_COLUMN_DEF: {
                ListCell *lc;
                foreach (lc, list) {
                    free_column_def_node(lfirst(lc));
                }
                break;
            }
            case NODE_COLUMN_DEF_OPT: {
                ListCell *lc;
                foreach (lc, list) {
                    free_column_def_opt_node(lfirst(lc));
                }
                break;
            }
            case NODE_COLUMN_DEF_NAME: {
                ListCell *lc;
                foreach (lc, list) {
                    free_column_def_name(lfirst(lc));
                }
                break;
            }
            case NODE_SCALAR_EXP: {
                ListCell *lc;
                foreach (lc, list) {
                    free_scalar_exp_node(lfirst(lc));
                }
                break;
            }
            case NODE_VALUE_ITEM: {
                ListCell *lc;
                foreach (lc, list) {
                    free_value_item_node(lfirst(lc));
                }
                break;
            }
            case NODE_BASE_TABLE_ELEMENT: {
                ListCell *lc;
                foreach (lc, list) {
                    free_base_table_element_node(lfirst(lc));
                }
                break;
            }
            case NODE_TABLE_REFER: {
                ListCell *lc;
                foreach (lc, list) {
                    free_table_ref_node(lfirst(lc));
                }
                break;
            }
            case NODE_ASSIGNMENT: {
                ListCell *lc;
                foreach (lc, list) {
                    free_assignment_node(lfirst(lc));
                }
                break;
            }
        }

        if (list->elements != list->initial_elements)
            db_free(list->elements);

        db_free(list);
    }
}

