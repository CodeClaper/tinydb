#include <stdint.h>
#include "asserts.h"

#ifndef LIST_H
#define LIST_H

#define INIT_LIST_CELL_SIZE 8
#define NIL (List *)(NULL)

typedef enum NodeTag {
    NODE_INT,
    NODE_BOOL,
    NODE_FLOAT,
    NODE_DOUBLE,
    NODE_STRING,
    NODE_LIST,
    NODE_KEY_VALUE,
    NODE_ROW,
    NODE_REFER,
    NODE_DB_RESULT,
    NODE_COLUMN_DEF_NODE
} NodeTag;

typedef struct ListState {
    uint32_t i;
} ListState;

/* Cell in List.*/
typedef union ListCell {
    void *ptr_value;
    int int_value;
    bool bool_value;
    float float_value;
    double double_value;
} ListCell;

/* List */
typedef struct List {
    NodeTag type;
    uint32_t size;
    uint32_t capacity;
    ListCell *elements;
    ListCell initial_elements[INIT_LIST_CELL_SIZE];
} List;


#define lfirst(l) ((l)->ptr_value)
#define lfirst_int(l) ((l)->int_value)
#define lfirst_bool(l) ((l)->bool_value)
#define lfirst_float(l) ((l)->float_value)
#define lfirst_double(l) ((l)->double_value)

/* Notice: there use __i rather than i as iterators, 
 * user habitually input i at the loop body that can cause mess. */
#define foreach(lc, list) \
        for (uint32_t __i = 0; __i < list->size ? (lc = &list->elements[__i], true) : (lc = NULL, false); __i++)


/* Last list cell. */
static inline ListCell *first_cell(List *list) {
    Assert(list != NIL);
    return &list->elements[0];
}

/* Last list cell. */
static inline ListCell *last_cell(List *list) {
    Assert(list != NIL);
    return &list->elements[list->size - 1];
}

/* Length of list. */
static inline uint32_t len_list(List *list) {
    Assert(list != NIL);
    return list->size;
}

/* Create List and initialization. 
 * Return the created list.
 * */
List *create_list(NodeTag type);

/* Append item to list. */
void append_list(List *list, void *item);

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

/* List is empty. */
bool list_empty(List *list);

#endif
