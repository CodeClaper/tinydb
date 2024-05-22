#include "data.h"
#include <stdint.h>

#define INIT_LIST_CELL_SIZE 8
#define NIL (List *)(NULL)
#define lfirst(l) ((l)->ptr)

#define foreach(lc, list) \
        for (uint32_t i = 0; i < list->size ? (lc = &list->elements[i], true) : (lc = NULL, false); i++)

typedef enum NodeTag {
    NODE_INT,
    NODE_BOOL,
    NODE_FLOAT,
    NODE_DOUBLE,
    NODE_STRING,
    NODE_COLUMN_DEF_NODE
} NodeTag;

/* Cell in List.*/
typedef struct ListCell {
    void *ptr;
} ListCell;

/* List */
typedef struct List {
    NodeTag type;
    uint32_t size;
    uint32_t capacity;
    ListCell *elements;
    ListCell initial_elements[INIT_LIST_CELL_SIZE];
} List;


/* Create List and initialization. 
 * Return the created list.
 * */
List *create_list(NodeTag type);

/* Append item to list. 
 * Return list after appending.
 * */
List *append_list(List *list, void *item);

/* Locate the n'th cell (counting from 0) of the list.
 * It is an assertion failure if there is no such cell.
 * */
ListCell *list_nth_cell(List *list, int nth);


/* Free all cells and objects those are 
 * point-to by cells in list DOES NOT be freed*/
void free_list(List *list);


/* Free all cells and any object that are 
 * point-to by cells in list will be freed*/
void free_list_deep(List *list);

