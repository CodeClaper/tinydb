#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include "common.h"
#include "misc.h"
#include "const.h"
#include "node.h"
#include "pager.h"
#include "meta.h"

// get node type
NodeType get_node_type(void *node) {
    uint8_t value = *(uint8_t *)(node + NODE_TYPE_OFFSET);
    return (NodeType) value;
}

// set node type
void set_node_type(void *node, NodeType node_type) {
    uint8_t value =(uint8_t) node_type;
    *(uint8_t *)(node + NODE_TYPE_OFFSET) = value;
}

// if root node
static bool is_root_node(void *node) {
    uint8_t value  = *(uint8_t *)(node + IS_ROOT_OFFSET);
    return (NodeType) value;
}

// set if root node
void set_root_node(void *node, bool if_root_node) {
    uint8_t value = (uint8_t) if_root_node;
    *(uint8_t *)(node + IS_ROOT_OFFSET) = value;
}

// get parent pointer
static uint32_t get_parent_pointer(void *node) {
    return *(uint32_t *)(node + PARENT_POINTER_OFFSET);
}

// set parent pointer
static void set_parent_pointer(void *node, uint32_t value) {
    *(uint32_t *)(node + PARENT_POINTER_OFFSET) = value;
}

// get root node column size
uint32_t get_column_size(void *node) {
    return *(uint32_t *)(node + ROOT_NODE_META_COLUMN_SIZE_OFFSET);
}

// set root node column size
void set_column_size(void *node, uint32_t value) {
    *(uint32_t *)(node + ROOT_NODE_META_COLUMN_SIZE_OFFSET) = (uint32_t)value;
}

// get leaf node cell number
uint32_t get_leaf_node_cell_num(void *node) {
    if (is_root_node(node)) {
        uint32_t column_size = get_column_size(node);
        return *(uint32_t *)(node + ROOT_NODE_META_COLUMN_SIZE_OFFSET + ROOT_NODE_META_COLUMN_SIZE_SIZE + ROOT_NODE_META_COLUMN_SIZE * column_size);
    } else {
        return *(uint32_t *)(node + CELL_NUM_OFFSET);
    }
}

// set leaf node cell number
static void set_leaf_node_cell_num(void *node, uint32_t cell_num) {
    if (is_root_node(node)) {
        uint32_t column_size = get_column_size(node);
        *(uint32_t *)(node + ROOT_NODE_META_COLUMN_SIZE_OFFSET + ROOT_NODE_META_COLUMN_SIZE_SIZE + ROOT_NODE_META_COLUMN_SIZE * column_size) = cell_num;
    } else {
        *(uint32_t *)(node + CELL_NUM_OFFSET) = cell_num;
    }
}


// get leaf node next leaf
static uint32_t get_leaf_node_next_leaf(void *node) {
    if (is_root_node(node)) {
        uint32_t column_size = get_column_size(node);
        return *(uint32_t *)(node + ROOT_NODE_META_COLUMN_SIZE_OFFSET + ROOT_NODE_META_COLUMN_SIZE_SIZE + ROOT_NODE_META_COLUMN_SIZE * column_size + CELL_NUM_SIZE);
    } else {
        return *(uint32_t *)(node + LEAF_NODE_NEXT_LEAF_OFFSET); 
    }
}

// set leaf node next leaf
static void set_leaf_node_next_leaf(void *node, uint32_t value) {
    if (is_root_node(node)) {
        uint32_t column_size = get_column_size(node);
        *(uint32_t *)(node + ROOT_NODE_META_COLUMN_SIZE_OFFSET + ROOT_NODE_META_COLUMN_SIZE_SIZE + ROOT_NODE_META_COLUMN_SIZE * column_size + CELL_NUM_SIZE) = value;
    } else {
        *(uint32_t *)(node + LEAF_NODE_NEXT_LEAF_OFFSET) = value;
    }
}


void *get_leaf_node_cell(void *node, uint32_t row_len, uint32_t index) {
    uint32_t cell_len = row_len + LEAF_NODE_CELL_KEY_SIZE;
    if (is_root_node(node)) {
        uint32_t column_size = get_column_size(node);
        return (node + ROOT_NODE_META_COLUMN_SIZE_OFFSET + ROOT_NODE_META_COLUMN_SIZE_SIZE + ROOT_NODE_META_COLUMN_SIZE * column_size + CELL_NUM_SIZE + LEAF_NODE_NEXT_LEAF_SIZE + cell_len * index); 
    } else {
        return (node + LEAF_NODE_HEAD_SIZE + cell_len * index);
    }
}

// get leaf node cell key 
uint32_t get_leaf_node_cell_key(void *node, uint32_t index, uint32_t row_len) {
    uint32_t cell_len = row_len + LEAF_NODE_CELL_KEY_SIZE;
    if (is_root_node(node)) {
        uint32_t column_size = get_column_size(node);
        return *(uint32_t *)(node + ROOT_NODE_META_COLUMN_SIZE_OFFSET + ROOT_NODE_META_COLUMN_SIZE_SIZE + ROOT_NODE_META_COLUMN_SIZE * column_size + CELL_NUM_SIZE + LEAF_NODE_NEXT_LEAF_SIZE + cell_len * index + row_len); 
    } else {
        return *(uint32_t *)(node + LEAF_NODE_HEAD_SIZE + cell_len * index + row_len);
    }
}

// set leaf node cell key
void set_leaf_node_cell_key(void *node, uint32_t index, uint32_t row_len, uint32_t key) {
    uint32_t cell_len = row_len + LEAF_NODE_CELL_KEY_SIZE;
    if (is_root_node(node)) {
        uint32_t column_size = get_column_size(node);
        *(uint32_t *)(node + ROOT_NODE_META_COLUMN_SIZE_OFFSET + ROOT_NODE_META_COLUMN_SIZE_SIZE + ROOT_NODE_META_COLUMN_SIZE * column_size +CELL_NUM_SIZE + LEAF_NODE_NEXT_LEAF_SIZE + cell_len * index + row_len) = key;
    } else {
        *(uint32_t *)(node + LEAF_NODE_HEAD_SIZE + cell_len * index + row_len) = key;
    }
}

// get leaf node cell value pointer
void *get_leaf_node_cell_value(void *node, uint32_t row_len, uint32_t index) {
    return get_leaf_node_cell(node, row_len, index);
}

// get internal node keys number
uint32_t get_internal_node_keys_num(void *node) {
    if (is_root_node(node)) {
        uint32_t column_size = get_column_size(node);
        return *(uint32_t *)(node + ROOT_NODE_META_COLUMN_SIZE_OFFSET + ROOT_NODE_META_COLUMN_SIZE_SIZE + ROOT_NODE_META_COLUMN_SIZE * column_size);
    } else {
        return *(uint32_t *)(node + KEYS_NUM_OFFSET);
    }
}

void set_internal_node_keys_num(void *node, uint32_t num) {
    if (is_root_node(node)) {
        uint32_t column_size = get_column_size(node);
        *(uint32_t *)(node + ROOT_NODE_META_COLUMN_SIZE_OFFSET + ROOT_NODE_META_COLUMN_SIZE_SIZE + ROOT_NODE_META_COLUMN_SIZE * column_size) = num;
    } else {
        *(uint32_t *)(node + KEYS_NUM_OFFSET) = num;
    }
}

// get right child of internal node 
uint32_t get_internal_node_right_child(void *node) {
    if (is_root_node(node)) {
        uint32_t column_size = get_column_size(node);
        return *(uint32_t *)(node + ROOT_NODE_META_COLUMN_SIZE_OFFSET + ROOT_NODE_META_COLUMN_SIZE_SIZE + ROOT_NODE_META_COLUMN_SIZE * column_size + KEYS_NUM_SIZE);
    } else {
        return *(uint32_t *)(node + RIGHT_CHILD_OFFSET);
    }
}

// set right child page num of internal node.
void set_internal_node_right_child(void *node, uint32_t right_child_page_num) {
    if (is_root_node(node)) {
        uint32_t column_size = get_column_size(node);
        *(uint32_t *)(node + ROOT_NODE_META_COLUMN_SIZE_OFFSET + ROOT_NODE_META_COLUMN_SIZE_SIZE + ROOT_NODE_META_COLUMN_SIZE * column_size + KEYS_NUM_SIZE) = right_child_page_num;
    } else {
        *(uint32_t *)(node + RIGHT_CHILD_OFFSET) = right_child_page_num;
    }
}

// get keys number in the node by index
uint32_t get_internal_node_keys(void *node, uint32_t index) {
    if (is_root_node(node)) {
        uint32_t column_size = get_column_size(node);
        return *(uint32_t *)(node + ROOT_NODE_META_COLUMN_SIZE_OFFSET + ROOT_NODE_META_COLUMN_SIZE_SIZE + ROOT_NODE_META_COLUMN_SIZE * column_size + KEYS_NUM_SIZE + RIGHT_CHILD_SIZE + INTERNAL_NODE_CELL_SIZE * index + INTERNAL_NODE_CELL_CHILD_SIZE); 
    } else {
        return *(uint32_t *)(node + INTERNAL_NODE_CELL_OFFSET + INTERNAL_NODE_CELL_SIZE * index + INTERNAL_NODE_CELL_CHILD_SIZE);
    }
}

// set internal node keys num
void set_internal_node_keys(void *node, uint32_t index, uint32_t keys_num) {
    if (is_root_node(node)) {
        uint32_t column_size = get_column_size(node);
        *(uint32_t *)(node + ROOT_NODE_META_COLUMN_SIZE_OFFSET + ROOT_NODE_META_COLUMN_SIZE_SIZE + ROOT_NODE_META_COLUMN_SIZE * column_size + KEYS_NUM_SIZE + RIGHT_CHILD_SIZE + INTERNAL_NODE_CELL_SIZE * index + INTERNAL_NODE_CELL_CHILD_SIZE) = keys_num;

    } else {
        *(uint32_t *)(node + INTERNAL_NODE_CELL_OFFSET + INTERNAL_NODE_CELL_SIZE * index + INTERNAL_NODE_CELL_CHILD_SIZE) = keys_num;
    }
}

// get child value in the node by index
uint32_t get_internal_node_child(void *node, uint32_t index) {
    if (is_root_node(node)) {
        uint32_t column_size = get_column_size(node);
        return *(uint32_t *)(node + ROOT_NODE_META_COLUMN_SIZE_OFFSET + ROOT_NODE_META_COLUMN_SIZE_SIZE + ROOT_NODE_META_COLUMN_SIZE * column_size + KEYS_NUM_SIZE + RIGHT_CHILD_SIZE + INTERNAL_NODE_CELL_SIZE * index); 
    } else {
        return *(uint32_t *)(node + INTERNAL_NODE_CELL_OFFSET + INTERNAL_NODE_CELL_SIZE * index);
    }
}

// set child value in the node by index
void set_internal_node_child(void *node, uint32_t index, uint32_t page_num) {
    if (is_root_node(node)) {
        uint32_t column_size = get_column_size(node);
        *(uint32_t *)(node + ROOT_NODE_META_COLUMN_SIZE_OFFSET + ROOT_NODE_META_COLUMN_SIZE_SIZE + ROOT_NODE_META_COLUMN_SIZE * column_size + KEYS_NUM_SIZE + RIGHT_CHILD_SIZE + INTERNAL_NODE_CELL_SIZE * index) = page_num;
    } else {
        *(uint32_t *)(node + INTERNAL_NODE_CELL_OFFSET + INTERNAL_NODE_CELL_SIZE * index) = page_num;
    }
}

// get internal node cell
void *get_internal_node_cell(void *node, uint32_t index) {
    if (is_root_node(node)) {
        uint32_t column_size = get_column_size(node);
        return (node + ROOT_NODE_META_COLUMN_SIZE_OFFSET + ROOT_NODE_META_COLUMN_SIZE_SIZE + ROOT_NODE_META_COLUMN_SIZE * column_size + KEYS_NUM_SIZE + RIGHT_CHILD_SIZE + INTERNAL_NODE_CELL_SIZE * index); 
    } else {
        return (node + INTERNAL_NODE_CELL_OFFSET + INTERNAL_NODE_CELL_SIZE * index);
    }
}

// get internal node index of key
uint32_t get_internal_node_key_index(void *node, uint32_t key, uint32_t keys_num) {
    // binary search
    uint32_t min_index = 0;
    uint32_t max_index = keys_num;
    while(min_index != max_index) {
        uint32_t index = (max_index + min_index) / 2;
        uint32_t index_key = get_internal_node_keys(node, index);
        if (index_key >= key) {
            max_index = index;
        } else {
            min_index = index + 1;
        }
    }
    return min_index;
}


// get internal node child page num
uint32_t get_internal_node_cell_child_page_num(void *node, uint32_t key, uint32_t keys_num) {
    // binary search
    uint32_t min_index = 0;
    uint32_t max_index = keys_num;
    while(min_index != max_index) {
        uint32_t index = (max_index + min_index) / 2;
        uint32_t index_key = get_internal_node_keys(node, index);
        if (index_key >= key) {
            max_index = index;
        } else {
            min_index = index + 1;
        }
    }
    if (min_index > keys_num) {
        printf("Tried to access child_num %d > num_keys %d\n", min_index, keys_num);
        exit(EXIT_FAILURE);
    } else if (min_index == keys_num) {
        return get_internal_node_right_child(node);
    } else {
        return get_internal_node_child(node, min_index);
    } 
}

// Get leaf node cell index, 
// Maybe the key not exist in the node,then return the bigger one. 
uint32_t get_leaf_node_cell_index(void *node, uint32_t key, uint32_t cell_num, uint32_t row_len) {
    // binary search
    uint32_t min_index = 0;
    uint32_t max_index = cell_num;
    while(min_index != max_index) {
        uint32_t index = (max_index + min_index) / 2;
        uint32_t key_at_index = get_leaf_node_cell_key(node, index, row_len);
        if (key_at_index >= key) {
            max_index = index;
        } else {
            min_index = index + 1; 
        }
    }
    return min_index;
}

// get index meta column pointer
void *get_meta_column_pointer(void *root_node, uint32_t index) {
    return root_node + ROOT_NODE_META_COLUMN_OFFSET + ROOT_NODE_META_COLUMN_SIZE * index;
}

uint32_t get_root_node_meta_column_size() {
    return ROOT_NODE_META_COLUMN_SIZE;
}

// set index meta column
void set_meta_column(void *root_node, void *destination, uint32_t index) {
   memcpy(root_node + ROOT_NODE_META_COLUMN_OFFSET + ROOT_NODE_META_COLUMN_SIZE * index, destination, ROOT_NODE_META_COLUMN_SIZE);
}

// get the max key in internal node or leaf node.
uint32_t get_max_key(void * node, uint32_t row_len) {
    switch(get_node_type(node)) {
        case INTERNAL_NODE:
           return get_internal_node_keys(node,  get_internal_node_keys_num(node) - 1);
        case LEAF_NODE:
            return get_leaf_node_cell_key(node, get_leaf_node_cell_num(node) - 1, row_len);
    }
}

// initialize leaf node
void initial_leaf_node(void *leaf_node, bool is_root) {
    set_node_type(leaf_node, LEAF_NODE);
    set_root_node(leaf_node, is_root);
    set_leaf_node_cell_num(leaf_node, 0);
    set_leaf_node_next_leaf(leaf_node, 0); // 'next leaf = 0' means no subling leaf node
}

// initialize internal node
void initial_internal_node(void *internal_node, bool is_root) {
    set_node_type(internal_node, INTERNAL_NODE);
    set_root_node(internal_node, is_root);
}

// update internal node node key
static void update_internal_node_key(void *leaf_node, uint32_t old_key, uint32_t new_key) {
    uint32_t keys_num = get_internal_node_keys_num(leaf_node);  
    uint32_t key_index = get_internal_node_key_index(leaf_node,  old_key, keys_num);
    set_internal_node_keys(leaf_node, key_index, new_key);
}

// check if leaf node page overflow
static bool overflow_leaf_node(void *leaf_node, uint32_t row_length, uint32_t cell_num) {
    uint32_t cell_len = row_length + LEAF_NODE_CELL_KEY_SIZE;
    if (is_root_node(leaf_node)) {
        uint32_t column_size = get_column_size(leaf_node);
        return COMMON_NODE_HEADER_SIZE + ROOT_NODE_META_COLUMN_SIZE_SIZE + ROOT_NODE_META_COLUMN_SIZE * column_size +CELL_NUM_SIZE + LEAF_NODE_NEXT_LEAF_SIZE + cell_len * (cell_num + 1) > PAGE_SIZE;
    } else {
        return LEAF_NODE_HEAD_SIZE + cell_len *(cell_num + 1) > PAGE_SIZE;
    }
}

// check if internal node page overflow
static bool overflow_internal_node(void *internal_node, uint32_t cell_num) {
    if (is_root_node(internal_node)) {
        uint32_t column_size = get_column_size(internal_node);
        return COMMON_NODE_HEADER_SIZE + ROOT_NODE_META_COLUMN_SIZE_SIZE + ROOT_NODE_META_COLUMN_SIZE * column_size + KEYS_NUM_SIZE + RIGHT_CHILD_SIZE + INTERNAL_NODE_CELL_SIZE * (cell_num + 1) > PAGE_SIZE;
    } else {
        return INTERNAL_NODE_HEAD_SIZE + INTERNAL_NODE_CELL_SIZE + (cell_num + 1) > PAGE_SIZE;
    }
}

// covnert root node to leaf node
static void copy_root_to_leaf_node(void *root, void* leaf_node, uint32_t row_len) {
    initial_leaf_node(leaf_node, false);
    set_leaf_node_cell_num(leaf_node, get_leaf_node_cell_num(root));
    set_leaf_node_next_leaf(leaf_node, get_leaf_node_next_leaf(root));
    uint32_t cell_num = get_leaf_node_cell_num(root); 
    for(uint32_t i = 0; i< cell_num; i++) {
        set_leaf_node_cell_key(leaf_node, i, row_len, get_leaf_node_cell_key(root, i, row_len)); 
        memcpy(get_leaf_node_cell_value(leaf_node, row_len, i), get_leaf_node_cell_value(root, row_len, i), row_len);
    }
    uint32_t column_size = get_column_size(root);
    uint32_t ROOT_LEAF_NODE_HEADER_SIZE = COMMON_NODE_HEADER_SIZE + ROOT_NODE_META_COLUMN_SIZE_SIZE + ROOT_NODE_META_COLUMN_SIZE * column_size;
    memset(root + ROOT_LEAF_NODE_HEADER_SIZE, 0, PAGE_SIZE - ROOT_LEAF_NODE_HEADER_SIZE);
}

// create new root node
static void create_new_root_node(Table *table, uint32_t right_child_page_num, uint32_t row_len) {
    void *root = get_page(table->pager, table->root_page_num);
    void *right_child = get_page(table->pager, right_child_page_num);
    uint32_t next_unused_page_num = table->pager->num_page;
    void *left_child = get_page(table->pager, next_unused_page_num);
    copy_root_to_leaf_node(root, left_child, row_len);
    set_parent_pointer(left_child, table->root_page_num);
    set_parent_pointer(right_child, table->root_page_num);
    set_node_type(root, INTERNAL_NODE);
    set_internal_node_keys_num(root, 1);
    uint32_t max_key = get_max_key(left_child, row_len);
    set_internal_node_keys(root, 0, max_key);
    set_internal_node_child(root, 0, next_unused_page_num);
    set_internal_node_right_child(root, right_child_page_num);

    flush_page(table->pager, next_unused_page_num);
    flush_page(table->pager, right_child_page_num);
    flush_page(table->pager, table->root_page_num);
}

// insert new internla node
static void insert_internal_node(Table *table, void *internal_node , uint32_t new_child_page_num) {
    uint32_t row_length = calc_table_row_length(table);
    void *new_child = get_page(table->pager, new_child_page_num);
    uint32_t keys_num = get_internal_node_keys_num(internal_node);
    if (overflow_internal_node(internal_node, keys_num)) {
        fprintf(stderr, "not implement now.\n");
        exit(EXIT_FAILURE);
    } else {
        uint32_t new_child_max_key = get_max_key(new_child, row_length);
        uint32_t new_child_max_key_index = get_internal_node_key_index(internal_node, new_child_max_key, keys_num);
        uint32_t right_child_page_num = get_internal_node_right_child(internal_node);
        void *right_child = get_page(table->pager, right_child_page_num);
        uint32_t right_child_max_key = get_max_key(right_child, row_length);
        if (new_child_max_key > right_child_page_num) {
            // replace right child
            set_internal_node_child(internal_node, keys_num, right_child_page_num);
            set_internal_node_keys(internal_node, keys_num, right_child_max_key);
            set_internal_node_right_child(internal_node, new_child_page_num);
        } else {
            for(int i = keys_num; i > new_child_max_key_index; i--) {
                memcpy(get_internal_node_cell(internal_node, i), get_internal_node_cell(internal_node, i - 1), INTERNAL_NODE_CELL_SIZE); 
            } 
            set_internal_node_keys(internal_node, new_child_max_key_index, new_child_max_key);
            set_internal_node_child(internal_node,  new_child_max_key_index, new_child_page_num);
        }
        set_internal_node_keys_num(internal_node, keys_num + 1);
    }
}


// when page if full, split and add leaf node into another page
static void insert_and_split_leaf_node(Cursor *cursor, Row *row) {
    uint32_t row_length = calc_table_row_length(cursor->table);
    uint32_t cell_length = row_length + LEAF_NODE_CELL_KEY_SIZE;
    void *old_node = get_page(cursor->table->pager, cursor->page_num);
    uint32_t cell_num = get_leaf_node_cell_num(old_node);
    uint32_t old_max_key = get_max_key(old_node, row_length);
    uint32_t next_unused_page_num = cursor->table->pager->num_page;
    void *new_node = get_page(cursor->table->pager, next_unused_page_num);
    initial_leaf_node(new_node, false);
    set_parent_pointer(new_node, get_parent_pointer(old_node));
    set_leaf_node_next_leaf(new_node, get_leaf_node_next_leaf(old_node));
    set_leaf_node_next_leaf(old_node, next_unused_page_num);
    uint32_t RIGHT_SPLIT_COUNT = (cell_num + 1) / 2;
    uint32_t LEFT_SPLIT_COUNT = (cell_num + 1) - RIGHT_SPLIT_COUNT;

    /*
    All existing keys plus new key should should be divided
    evenly between old (left) and new (right) nodes.
    Starting from the right, move each key to correct position.
    */
    // notice, when i can be 0, can`t use uintXX_t as index data type
    // because uintXX_t can be 0, but can`t be negative number, always >= 0, and can`t stop the loop
    for (int32_t i = cell_num; i >= 0; i--) {
        void *destination_node;
        if (i >= LEFT_SPLIT_COUNT) {
            destination_node = new_node;
        } else {
            destination_node = old_node;
        }
        uint32_t index_in_node = i % LEFT_SPLIT_COUNT;
        void *destination = get_leaf_node_cell(destination_node, row_length, index_in_node);
#ifdef DEBUG
        printf("loop: %d\n", i);
#endif
        if (i == cursor->cell_num) {
            void *serial_data = serialize_row_data(row, cursor->table);
            memcpy(destination, serial_data, row_length);
            free(serial_data);
            set_leaf_node_cell_key(destination_node, index_in_node, row_length, row->key);
        } else if ( i > cursor->cell_num) {
            // make cell space
            memcpy(destination, get_leaf_node_cell(old_node, row_length, i - 1), cell_length);
        } else {
            memcpy(destination, get_leaf_node_cell(old_node, row_length, i), cell_length);
        }
    }
    // set cell num
    set_leaf_node_cell_num(old_node, LEFT_SPLIT_COUNT);
    set_leaf_node_cell_num(new_node, RIGHT_SPLIT_COUNT);
    set_leaf_node_next_leaf(old_node, next_unused_page_num);

    if (is_root_node(old_node)) {
        create_new_root_node(cursor->table, next_unused_page_num, row_length); 
    } else {
        uint32_t parent_page_num = get_parent_pointer(old_node);
        void *parent = get_page(cursor->table->pager, parent_page_num);
        uint32_t new_max_key = get_max_key(old_node, row_length);
        update_internal_node_key(parent, old_max_key, new_max_key);
        insert_internal_node(cursor->table, parent, next_unused_page_num);
        flush_page(cursor->table->pager, cursor->page_num);
        flush_page(cursor->table->pager, next_unused_page_num);
        flush_page(cursor->table->pager, parent_page_num);
    }
}

// insert a new leaf node
void insert_leaf_node(Cursor *cursor, Row *row) {
    void *node = get_page(cursor->table->pager, cursor->page_num); 
    uint32_t cell_num = get_leaf_node_cell_num(node);
    uint32_t row_length = calc_table_row_length(cursor->table);
    uint32_t cell_length = row_length + LEAF_NODE_CELL_KEY_SIZE;
    if (overflow_leaf_node(node, row_length, cell_num)) {
        insert_and_split_leaf_node(cursor, row);
    } else {
        if (cursor->cell_num < cell_num) {
            // make room for new cell
            for (int i = cell_num; i > cursor->cell_num; i--) {
                memcpy(get_leaf_node_cell(node, row_length, i), get_leaf_node_cell(node, row_length, i-1), cell_length);
            }
        }
        set_leaf_node_cell_key(node, cursor->cell_num, row_length, row->key);
        void *destination = serialize_row_data(row, cursor->table);
        memcpy(get_leaf_node_cell_value(node, row_length, cursor->cell_num), destination, row_length);
        set_leaf_node_cell_num(node, ++cell_num);
        flush_page(cursor->table->pager, cursor->page_num); // flush into disk.
    }
}

// deserialize meta column
MetaColumn *deserialize_meta_column(void *destination) {
    MetaColumn *meta_column = malloc(sizeof(MetaColumn));
    if (meta_column == NULL)
        MALLOC_ERROR;
    memset(meta_column, 0, sizeof(MetaColumn));
    strcpy(meta_column->column_name, destination); 
    meta_column->column_type = (DataType)*(uint32_t *)(destination + ROOT_NODE_META_COLUMN_NAME_SIZE);
    meta_column->column_length = *(uint32_t *)(destination + ROOT_NODE_META_COLUMN_NAME_SIZE + ROOT_NODE_META_COLUMN_TYPE_SIZE);
    meta_column->is_primary = (bool)*(uint8_t *)(destination + ROOT_NODE_META_COLUMN_NAME_SIZE + ROOT_NODE_META_COLUMN_TYPE_SIZE + ROOT_NODE_META_COLUMN_LENGTH_SIZE);
    return meta_column;
}

// deserialize meta column
void *serialize_meta_column(MetaColumn *meta_column) {
    void *destination= malloc(ROOT_NODE_META_COLUMN_SIZE);
    if (meta_column == NULL)
        MALLOC_ERROR;
    memset(destination, 0, ROOT_NODE_META_COLUMN_SIZE);
    strcpy(destination, meta_column->column_name);
    *(uint32_t *)(destination + ROOT_NODE_META_COLUMN_NAME_SIZE) = (uint32_t) meta_column->column_type;
    *(uint32_t *)(destination + ROOT_NODE_META_COLUMN_NAME_SIZE + ROOT_NODE_META_COLUMN_TYPE_SIZE) = (uint32_t) meta_column->column_length;
    *(uint8_t *)(destination + ROOT_NODE_META_COLUMN_NAME_SIZE + ROOT_NODE_META_COLUMN_TYPE_SIZE + ROOT_NODE_META_COLUMN_LENGTH_SIZE) =meta_column->is_primary;  
    return destination;
}

static void *get_column_value(Row *row, MetaColumn *meta_column) {
    char *column_name = meta_column->column_name;
    for(uint32_t i = 0; i < row->column_len; i++) {
        if (strcmp(column_name, row->data[i]->key) == 0) {
           return row->data[i]->value;
        }
    }
    fatals("Inner error, unknown column ", column_name);
    return NULL;
}

// serialize row data
void *serialize_row_data(Row *row, Table *table) {
    uint32_t row_length = calc_table_row_length(table);
    void *destination = malloc(row_length);
    if (destination == NULL)
        MALLOC_ERROR;
    memset(destination, 0, row_length);
    MetaTable *meta_table = table->meta_table;
    uint32_t offset = 0;
    for(uint32_t i = 0; i < meta_table->column_size; i++) {
        MetaColumn *meta_column = meta_table->meta_column[i]; 
        void *value = get_column_value(row, meta_column);
        memcpy(destination + offset, value, meta_column->column_length);
        offset += meta_column->column_length;
    }
    return destination;
}
