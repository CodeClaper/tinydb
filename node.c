#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
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
        *(uint32_t *)(node + ROOT_NODE_META_COLUMN_SIZE_OFFSET + ROOT_NODE_META_COLUMN_SIZE_SIZE + ROOT_NODE_META_COLUMN_SIZE * column_size) = column_size;
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
        return (node + ROOT_NODE_META_COLUMN_SIZE_OFFSET + ROOT_NODE_META_COLUMN_SIZE_SIZE + ROOT_NODE_META_COLUMN_SIZE * column_size  + cell_len * index); 
    } else {
        return (node + LEAF_NODE_HEAD_SIZE + cell_len * index);
    }
}

// get leaf node cell key 
uint32_t get_leaf_node_cell_key(void *node, uint32_t index, uint32_t row_len) {
    uint32_t cell_len = row_len + LEAF_NODE_CELL_KEY_SIZE;
    if (is_root_node(node)) {
        uint32_t column_size = get_column_size(node);
        return *(uint32_t *)(node + ROOT_NODE_META_COLUMN_SIZE_OFFSET + ROOT_NODE_META_COLUMN_SIZE_SIZE + ROOT_NODE_META_COLUMN_SIZE * column_size  + cell_len * index + row_len); 
    } else {
        return *(uint32_t *)(node + LEAF_NODE_HEAD_SIZE + cell_len * index + row_len);
    }
}

// set leaf node cell key
void set_leaf_node_cell_key(void *node, uint32_t index, uint32_t row_len, uint32_t key) {
    uint32_t cell_len = row_len + LEAF_NODE_CELL_KEY_SIZE;
    if (is_root_node(node)) {
        uint32_t column_size = get_column_size(node);
        *(uint32_t *)(node + ROOT_NODE_META_COLUMN_SIZE_OFFSET + ROOT_NODE_META_COLUMN_SIZE_SIZE + ROOT_NODE_META_COLUMN_SIZE * column_size  + cell_len * index + row_len) = key;
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

// get keys number in the node by index
uint32_t get_internal_node_keys(void *node, uint32_t index) {
    if (is_root_node(node)) {
        uint32_t column_size = get_column_size(node);
        return *(uint32_t *)(node + ROOT_NODE_META_COLUMN_SIZE_OFFSET + ROOT_NODE_META_COLUMN_SIZE_SIZE + ROOT_NODE_META_COLUMN_SIZE * column_size + INTERNAL_NODE_CELL_SIZE * index + INTERNAL_NODE_CELL_CHILD_SIZE); 
    } else {
        return *(uint32_t *)(node + INTERNAL_NODE_CELL_OFFSET + INTERNAL_NODE_CELL_SIZE * index + INTERNAL_NODE_CELL_CHILD_SIZE);
    }
}

// get child value in the node by index
uint32_t get_internal_node_child(void *node, uint32_t index) {
    if (is_root_node(node)) {
        uint32_t column_size = get_column_size(node);
        return *(uint32_t *)(node + ROOT_NODE_META_COLUMN_SIZE_OFFSET + ROOT_NODE_META_COLUMN_SIZE_SIZE + ROOT_NODE_META_COLUMN_SIZE * column_size + INTERNAL_NODE_CELL_SIZE * index); 
    } else {
        return *(uint32_t *)(node + INTERNAL_NODE_CELL_OFFSET + INTERNAL_NODE_CELL_SIZE * index);
    }
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
    return get_internal_node_child(node, min_index);
}

// Get leaf node cell index, 
// Maybe the key not exist in the node,then return the bigger one. 
uint32_t get_leaf_node_cell_index(void *node, uint32_t key, uint32_t cell_num, uint32_t row_len) {
    // binary search
    uint32_t min_index = 0;
    uint32_t max_index = cell_num;
    while(min_index != max_index) {
        uint32_t index = (max_index + min_index) / 2;
        uint32_t index_key = get_leaf_node_cell_key(node, key, row_len);
        if (index_key >= key) {
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

// initialize leaf node
void initial_leaf_node(void *leaf_node, bool is_root) {
    set_node_type(leaf_node, LEAF_NODE);
    set_root_node(leaf_node, is_root);
    set_leaf_node_cell_num(leaf_node, 0);
    set_leaf_node_next_leaf(leaf_node, 0); // 'next leaf = 0' means no subling leaf node
}

// insert a new leaf node
void insert_leaf_node(Cursor *cursor, Row *row) {
    void *node = get_page(cursor->table->pager, cursor->page_num); 
    uint32_t cell_num = get_leaf_node_cell_num(node);
    uint32_t row_length = calc_table_row_length(cursor->table);
    uint32_t cell_length = row_length + LEAF_NODE_CELL_KEY_SIZE;
    if (LEAF_NODE_HEAD_SIZE + (LEAF_NODE_CELL_KEY_SIZE + row_length) *(cell_num + 1) > PAGE_SIZE) {

    } else {
        if (cursor->cell_num < cell_num) {
            // make room for new cell
            for (uint32_t i = cell_num; i > cursor->cell_num; i--) {
                memcpy(get_leaf_node_cell(node, row_length, i), get_leaf_node_cell(node, row_length, i), cell_length);
            }
        }
        set_leaf_node_cell_key(node, cursor->cell_num, row_length, row->key);
        void *destination = serialize_row_data(row, cursor->table);
        memcpy(get_leaf_node_cell_value(node, row_length, cursor->cell_num), destination, row_length);
    }
}

// deserialize meta column
MetaColumn *deserialize_meta_column(void *destination) {
    MetaColumn *meta_column = malloc(sizeof(MetaColumn));
    if (meta_column == NULL)
        MALLOC_ERROR;
    memset(meta_column, 0, sizeof(MetaColumn));
    strcpy(meta_column->column_name, destination); 
    meta_column->column_type = (ColumnType)*(uint32_t *)(destination + ROOT_NODE_META_COLUMN_NAME_SIZE);
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
    for(uint32_t i = 0; i < row->data_len; i++) {
        if (strcmp(column_name, row->data[i]->key) == 0) {
           return row->data[i]->value;
        }
    }
    fatal("Inner error, value in row can`t match.");
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
