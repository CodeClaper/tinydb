/**
 * ========================== Disk Mapping B+TREE ======================================
 * The ltree module is the core mudule for TinyDB.
 * - A database file is divided into a whole number pages.
 * - A page includes meta data and cells.
 * - Meta data includes node type, is root leaf node, parent pointer and cell number.
 * - Cell is a Key-Value, key is index and value containes one row data in table.
 * - TinyDb use B-Tree as disk data structre.
 * - Each node correspond to one page.
 * - There are two types nodes, leaf node and internal node.
 * - Leaf node store real row data.
 * - Internal node store keys.
 * - Root node also as leaf node, but does not store data.
 * - Usually, root node is page 0.
 * ====================================================================================
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include "ltree.h"
#include "mmu.h"
#include "free.h"
#include "refer.h"
#include "common.h"
#include "asserts.h"
#include "const.h"
#include "pager.h"
#include "meta.h"
#include "compare.h"
#include "log.h"
#include "index.h"

/* If obsolute node. */
bool is_obsolute_node(void *node) {
    if (node == NULL) return false;
    uint8_t value  = *(uint8_t *)(node + IS_OBSOLUTE_OFFSET);
    return (bool) value;
}

/* Set obsolute flag. */
void set_obsolute_node(void *node, bool flag) {
    uint8_t value = (uint8_t) flag;
    *(uint8_t *)(node + IS_OBSOLUTE_OFFSET) = value;
}

/* Make node obsolute. */
static void make_obsolute_node(void *node) {
    memset(node, 0, PAGE_SIZE);
    set_obsolute_node(node, true);
}

/* Get next avaliable page num. 
 * If page is obsolute, recycle to use it,
 * If there is no obsolute page, return new page. */
static uint32_t next_avaliable_page_num(Pager *pager) {
    int i;
    for (i = 0; i < pager->size; i++) {
        if (is_obsolute_node(pager->pages[i])) {
            set_obsolute_node(pager->pages[i], false);
            return i;
        }
    }
    return pager->size;
}

/* Get node type */
NodeType get_node_type(void *node) {
    uint8_t value = *(uint8_t *)(node + NODE_TYPE_OFFSET);
    return (NodeType) value;
}

/* Set node type */
void set_node_type(void *node, NodeType node_type) {
    uint8_t value =(uint8_t) node_type;
    *(uint8_t *)(node + NODE_TYPE_OFFSET) = value;
}

/* If root node */
static bool is_root_node(void *node) {
    uint8_t value  = *(uint8_t *)(node + IS_ROOT_OFFSET);
    return (bool) value;
}

/* Set if root node */
void set_root_node(void *node, bool if_root_node) {
    uint8_t value = (uint8_t) if_root_node;
    *(uint8_t *)(node + IS_ROOT_OFFSET) = value;
}

/* Get parent pointer */
static uint32_t get_parent_pointer(void *node) {
    return *(uint32_t *)(node + PARENT_POINTER_OFFSET);
}

/* Set parent pointer. */
static void set_parent_pointer(void *node, uint32_t value) {
    *(uint32_t *)(node + PARENT_POINTER_OFFSET) = value;
}

/* Get root node column size. */
uint32_t get_column_size(void *node) {
    return *(uint32_t *)(node + ROOT_NODE_META_COLUMN_SIZE_OFFSET);
}

/* Set root node column size. */
void set_column_size(void *node, uint32_t value) {
    *(uint32_t *)(node + ROOT_NODE_META_COLUMN_SIZE_OFFSET) = (uint32_t)value;
}

/* Get leaf node cell number. */
uint32_t get_leaf_node_cell_num(void *node) {
    if (is_root_node(node)) {
        uint32_t column_size = get_column_size(node);
        return *(uint32_t *)(node + ROOT_NODE_META_COLUMN_SIZE_OFFSET + ROOT_NODE_META_COLUMN_SIZE_SIZE + ROOT_NODE_META_COLUMN_SIZE * column_size);
    } else {
        return *(uint32_t *)(node + CELL_NUM_OFFSET);
    }
}

/* Set leaf node cell number. */
static void set_leaf_node_cell_num(void *node, uint32_t cell_num) {
    if (is_root_node(node)) {
        uint32_t column_size = get_column_size(node);
        *(uint32_t *)(node + ROOT_NODE_META_COLUMN_SIZE_OFFSET + ROOT_NODE_META_COLUMN_SIZE_SIZE + ROOT_NODE_META_COLUMN_SIZE * column_size) = cell_num;
    } else {
        *(uint32_t *)(node + CELL_NUM_OFFSET) = cell_num;
    }
}

/* Get leaf node next leaf. */
static uint32_t get_leaf_node_next_leaf(void *node) {
    if (is_root_node(node)) {
        uint32_t column_size = get_column_size(node);
        return *(uint32_t *)(node + ROOT_NODE_META_COLUMN_SIZE_OFFSET + ROOT_NODE_META_COLUMN_SIZE_SIZE + ROOT_NODE_META_COLUMN_SIZE * column_size + CELL_NUM_SIZE);
    } else {
        return *(uint32_t *)(node + LEAF_NODE_NEXT_LEAF_OFFSET); 
    }
}

/* Set leaf node next leaf */
static void set_leaf_node_next_leaf(void *node, uint32_t value) {
    if (is_root_node(node)) {
        uint32_t column_size = get_column_size(node);
        *(uint32_t *)(node + ROOT_NODE_META_COLUMN_SIZE_OFFSET + ROOT_NODE_META_COLUMN_SIZE_SIZE + ROOT_NODE_META_COLUMN_SIZE * column_size + CELL_NUM_SIZE) = value;
    } else {
        *(uint32_t *)(node + LEAF_NODE_NEXT_LEAF_OFFSET) = value;
    }
}

/* Get leaf node cell offset. */
uint32_t get_leaf_node_cell_offset(void *node, uint32_t cell_len, uint32_t index) {
    if (is_root_node(node)) {
        uint32_t column_size = get_column_size(node);
        return (ROOT_NODE_META_COLUMN_SIZE_OFFSET + ROOT_NODE_META_COLUMN_SIZE_SIZE + ROOT_NODE_META_COLUMN_SIZE * column_size + CELL_NUM_SIZE + LEAF_NODE_NEXT_LEAF_SIZE + cell_len * index); 
    } else {
        return (LEAF_NODE_HEAD_SIZE + cell_len * index);
    }
}

/* Get leaf node cell. */
void *get_leaf_node_cell(void *node, uint32_t key_len, uint32_t value_len, uint32_t index) {
    uint32_t cell_len = key_len + value_len;
    if (is_root_node(node)) {
        uint32_t column_size = get_column_size(node);
        return (node + ROOT_NODE_META_COLUMN_SIZE_OFFSET + ROOT_NODE_META_COLUMN_SIZE_SIZE + ROOT_NODE_META_COLUMN_SIZE * column_size + CELL_NUM_SIZE + LEAF_NODE_NEXT_LEAF_SIZE + cell_len * index); 
    } else {
        return (node + LEAF_NODE_HEAD_SIZE + cell_len * index);
    }
}

/* Get leaf node cell key.  */
void *get_leaf_node_cell_key(void *node, uint32_t index, uint32_t key_len, uint32_t value_len) {
    uint32_t cell_len = key_len + value_len;
    if (is_root_node(node)) {
        uint32_t column_size = get_column_size(node);
        return (node + ROOT_NODE_META_COLUMN_SIZE_OFFSET + ROOT_NODE_META_COLUMN_SIZE_SIZE + ROOT_NODE_META_COLUMN_SIZE * column_size + CELL_NUM_SIZE + LEAF_NODE_NEXT_LEAF_SIZE + cell_len * index + value_len); 
    } else {
        return (node + LEAF_NODE_HEAD_SIZE + cell_len * index + value_len);
    }
}

/* Set leaf node cell key. */
void set_leaf_node_cell_key(void *node, uint32_t index, uint32_t key_len, uint32_t value_len, void *key) {
    uint32_t cell_len = key_len + value_len;
    if (is_root_node(node)) {
        uint32_t column_size = get_column_size(node);
        memcpy(node + ROOT_NODE_META_COLUMN_SIZE_OFFSET + ROOT_NODE_META_COLUMN_SIZE_SIZE + ROOT_NODE_META_COLUMN_SIZE * column_size +CELL_NUM_SIZE + LEAF_NODE_NEXT_LEAF_SIZE + cell_len * index + value_len, key, key_len);
    } else {
        memcpy(node + LEAF_NODE_HEAD_SIZE + cell_len * index + value_len, key, key_len);
    }
}

/* Get leaf node cell value pointer. */
void *get_leaf_node_cell_value(void *node, uint32_t key_len, uint32_t value_len, uint32_t index) {
    return get_leaf_node_cell(node, key_len, value_len, index);
}

/* Get internal node keys number. */
uint32_t get_internal_node_keys_num(void *node) {
    if (is_root_node(node)) {
        uint32_t column_size = get_column_size(node);
        return *(uint32_t *)(node + ROOT_NODE_META_COLUMN_SIZE_OFFSET + ROOT_NODE_META_COLUMN_SIZE_SIZE + ROOT_NODE_META_COLUMN_SIZE * column_size);
    } else {
        return *(uint32_t *)(node + KEYS_NUM_OFFSET);
    }
}

/* Set internal node keys number. */
void set_internal_node_keys_num(void *node, uint32_t num) {
    if (is_root_node(node)) {
        uint32_t column_size = get_column_size(node);
        *(uint32_t *)(node + ROOT_NODE_META_COLUMN_SIZE_OFFSET + ROOT_NODE_META_COLUMN_SIZE_SIZE + ROOT_NODE_META_COLUMN_SIZE * column_size) = num;
    } else {
        *(uint32_t *)(node + KEYS_NUM_OFFSET) = num;
    }
}

/* Get right child of internal node  */
uint32_t get_internal_node_right_child(void *node) {
    if (is_root_node(node)) {
        uint32_t column_size = get_column_size(node);
        return *(uint32_t *)(node + ROOT_NODE_META_COLUMN_SIZE_OFFSET + ROOT_NODE_META_COLUMN_SIZE_SIZE + ROOT_NODE_META_COLUMN_SIZE * column_size + KEYS_NUM_SIZE);
    } else {
        return *(uint32_t *)(node + RIGHT_CHILD_OFFSET);
    }
}

/* Set right child page num of internal node. */
void set_internal_node_right_child(void *node, uint32_t right_child_page_num) {
    if (is_root_node(node)) {
        uint32_t column_size = get_column_size(node);
        *(uint32_t *)(node + ROOT_NODE_META_COLUMN_SIZE_OFFSET + ROOT_NODE_META_COLUMN_SIZE_SIZE + ROOT_NODE_META_COLUMN_SIZE * column_size + KEYS_NUM_SIZE) = right_child_page_num;
    } else {
        *(uint32_t *)(node + RIGHT_CHILD_OFFSET) = right_child_page_num;
    }
}

/* Get key in the node by index. */
void *get_internal_node_key(void *node, uint32_t index, uint32_t key_len) {
    uint32_t cell_len = key_len + INTERNAL_NODE_CELL_CHILD_SIZE;
    if (is_root_node(node)) {
        uint32_t column_size = get_column_size(node);
        return (node + ROOT_NODE_META_COLUMN_SIZE_OFFSET + ROOT_NODE_META_COLUMN_SIZE_SIZE + ROOT_NODE_META_COLUMN_SIZE * column_size + KEYS_NUM_SIZE + RIGHT_CHILD_SIZE + cell_len * index + INTERNAL_NODE_CELL_CHILD_SIZE); 
    } else {
        return (node + INTERNAL_NODE_CELL_OFFSET + cell_len * index + INTERNAL_NODE_CELL_CHILD_SIZE);
    }
}

/* Set internal node key by index */
void set_internal_node_key(void *node, uint32_t index, void *key, uint32_t key_len) {
    uint32_t cell_len = key_len + INTERNAL_NODE_CELL_CHILD_SIZE;
    if (is_root_node(node)) {
        uint32_t column_size = get_column_size(node);
        memcpy(node + ROOT_NODE_META_COLUMN_SIZE_OFFSET + ROOT_NODE_META_COLUMN_SIZE_SIZE + ROOT_NODE_META_COLUMN_SIZE * column_size + KEYS_NUM_SIZE + RIGHT_CHILD_SIZE + cell_len * index + INTERNAL_NODE_CELL_CHILD_SIZE, key, key_len);
    } else {
        memcpy(node + INTERNAL_NODE_CELL_OFFSET + cell_len * index + INTERNAL_NODE_CELL_CHILD_SIZE, key, key_len);
    }
}

/* Get child value in the node by index. */
uint32_t get_internal_node_child(void *node, uint32_t index, uint32_t key_len) {
    uint32_t cell_len = key_len + INTERNAL_NODE_CELL_CHILD_SIZE;
    if (is_root_node(node)) {
        uint32_t column_size = get_column_size(node);
        return *(uint32_t *)(node + ROOT_NODE_META_COLUMN_SIZE_OFFSET + ROOT_NODE_META_COLUMN_SIZE_SIZE + ROOT_NODE_META_COLUMN_SIZE * column_size + KEYS_NUM_SIZE + RIGHT_CHILD_SIZE + cell_len * index); 
    } else {
        return *(uint32_t *)(node + INTERNAL_NODE_CELL_OFFSET + cell_len * index);
    }
}

/* Set child value in the node by index */
void set_internal_node_child(void *node, uint32_t index, uint32_t page_num, uint32_t key_len) {
    uint32_t cell_len = key_len + INTERNAL_NODE_CELL_CHILD_SIZE;
    if (is_root_node(node)) {
        uint32_t column_size = get_column_size(node);
        *(uint32_t *)(node + ROOT_NODE_META_COLUMN_SIZE_OFFSET + ROOT_NODE_META_COLUMN_SIZE_SIZE + ROOT_NODE_META_COLUMN_SIZE * column_size + KEYS_NUM_SIZE + RIGHT_CHILD_SIZE + cell_len * index) = page_num;
    } else {
        *(uint32_t *)(node + INTERNAL_NODE_CELL_OFFSET + cell_len * index) = page_num;
    }
}

/* get internal node cell */
void *get_internal_node_cell(void *node, uint32_t index, uint32_t key_len) {
    uint32_t cell_len = key_len + INTERNAL_NODE_CELL_CHILD_SIZE;
    if (is_root_node(node)) {
        uint32_t column_size = get_column_size(node);
        return (node + ROOT_NODE_META_COLUMN_SIZE_OFFSET + ROOT_NODE_META_COLUMN_SIZE_SIZE + ROOT_NODE_META_COLUMN_SIZE * column_size + KEYS_NUM_SIZE + RIGHT_CHILD_SIZE + cell_len * index); 
    } else {
        return (node + INTERNAL_NODE_CELL_OFFSET + cell_len * index);
    }
}

/* Get internal node index of key */
uint32_t get_internal_node_key_index(void *node, void *key, uint32_t keys_num, uint32_t key_len, DataType key_data_type) {

    /* Binary search */
    uint32_t min_index = 0;
    uint32_t max_index = keys_num;
    while(min_index != max_index) {
        uint32_t index = (max_index + min_index) / 2;
        void* index_key = get_internal_node_key(node, index, key_len);
        if (greater_equal(index_key, key, key_data_type)) {
            max_index = index;
        } else {
            min_index = index + 1;
        }
    }
    return min_index;
}


// get internal node child page num
uint32_t get_internal_node_cell_child_page_num(void *node, void *key, uint32_t keys_num, uint32_t key_len, DataType key_data_type) {
    // binary search
    uint32_t min_index = 0;
    uint32_t max_index = keys_num;
    while(min_index != max_index) {
        uint32_t index = (max_index + min_index) / 2;
        void *index_key = get_internal_node_key(node, index, key_len);
        if (greater_equal(index_key, key, key_data_type)) {
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
        return get_internal_node_child(node, min_index, key_len);
    } 
}

// Get leaf node cell index, 
// Maybe the key not exist in the node,then return the bigger one. 
uint32_t get_leaf_node_cell_index(void *node, void *key, uint32_t cell_num, uint32_t key_len, uint32_t value_len, DataType key_data_type) {
    // binary search
    uint32_t min_index = 0;
    uint32_t max_index = cell_num;
    while(min_index != max_index) {
        uint32_t index = (max_index + min_index) / 2;
        void *key_at_index = get_leaf_node_cell_key(node, index, key_len, value_len);
        if (greater_equal(key_at_index, key, key_data_type)) {
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

/* Get absolute max key. 
 * Absolute max means the max child key. 
 * For leaf node, the max key child is the last child; For internal node, the max child exists in the right child.
 * */
static void *get_max_key(Table *table, void *node, uint32_t key_len, uint32_t value_len) {
    switch(get_node_type(node)) {
        case INTERNAL_NODE: {
            uint32_t right_child_page_num = get_internal_node_right_child(node);
            void *right_node = get_page(table->meta_table->table_name, table->pager, right_child_page_num);
            return get_max_key(table, right_node, key_len, value_len);
        }
        case LEAF_NODE:
            return get_leaf_node_cell_key(node, get_leaf_node_cell_num(node) - 1,  key_len, value_len);
    }
}

/* Initialize leaf node. */
void initial_leaf_node(void *leaf_node, bool is_root) {
    set_node_type(leaf_node, LEAF_NODE);
    set_root_node(leaf_node, is_root);
    set_leaf_node_cell_num(leaf_node, 0);
    set_leaf_node_next_leaf(leaf_node, 0); // 'next leaf = 0' means no subling leaf node
}

/* Initialize internal node. */
void initial_internal_node(void *internal_node, bool is_root) {
    set_node_type(internal_node, INTERNAL_NODE);
    set_root_node(internal_node, is_root);
}

/* Update internal node node key. */
static void update_internal_node_key(Table *table, void *internal_node, void *old_key, void *new_key, uint32_t key_len, uint32_t value_len, DataType key_data_type) {
    uint32_t keys_num = get_internal_node_keys_num(internal_node);  
    /* Get max key and absolute max key in internal node cell. */
    void *max_key = get_internal_node_key(internal_node, keys_num - 1, key_len);
    void *absolute_max_key = get_max_key(table, internal_node, key_len, value_len);
    
    /* If old key greater than the max key, it means it exist in right child node. No need to change cells key. 
     * Otherwise, it means the key in the cells, need to be replaced with new one. */
    if (keys_num > 0 && !greater(old_key, max_key, key_data_type)) {
        uint32_t key_index = get_internal_node_key_index(internal_node, old_key, keys_num, key_len, key_data_type);
        void *key = get_internal_node_key(internal_node, key_index, key_len);

        /* Theoretically equal, just for check.*/
        if (equal(old_key, key, key_data_type)) 
            set_internal_node_key(internal_node, key_index, new_key, key_len);
        else
            db_log(PANIC, "System error in update internal node key."); 
    }
    
    /* If internal has parent node, and change its absolute max key, also need to change its parent key. */
    if (!is_root_node(internal_node) && (equal(old_key, absolute_max_key, key_data_type) || equal(new_key, absolute_max_key, key_data_type))) {
        uint32_t parent_page_num = get_parent_pointer(internal_node);
        void *parent_node = get_page(table->meta_table->table_name, table->pager, parent_page_num);
        update_internal_node_key(table, parent_node, old_key, new_key, key_len, value_len, key_data_type);
        flush_page(table->meta_table->table_name, table->pager, parent_page_num);
    }
}

/* Check if leaf node page overflow. */
static bool overflow_leaf_node(void *leaf_node, uint32_t key_len, uint32_t value_len, uint32_t cell_num) {
    uint32_t cell_len = key_len + value_len;
    if (is_root_node(leaf_node)) {
        uint32_t column_size = get_column_size(leaf_node);
        return COMMON_NODE_HEADER_SIZE + ROOT_NODE_META_COLUMN_SIZE_SIZE + ROOT_NODE_META_COLUMN_SIZE * column_size +CELL_NUM_SIZE + LEAF_NODE_NEXT_LEAF_SIZE + cell_len * (cell_num + 1) > PAGE_SIZE;
    } else {
        return LEAF_NODE_HEAD_SIZE + cell_len *(cell_num + 1) > PAGE_SIZE;
    }
}

/* Check if internal node page overflow */
static bool overflow_internal_node(void *internal_node, uint32_t keys_num, uint32_t key_len) {
    uint32_t cell_len = key_len + INTERNAL_NODE_CELL_CHILD_SIZE;
    if (is_root_node(internal_node)) {
        uint32_t column_size = get_column_size(internal_node);
        return COMMON_NODE_HEADER_SIZE + ROOT_NODE_META_COLUMN_SIZE_SIZE + ROOT_NODE_META_COLUMN_SIZE * column_size + KEYS_NUM_SIZE + RIGHT_CHILD_SIZE + cell_len * (keys_num + 1) > PAGE_SIZE;
    } else {
        return INTERNAL_NODE_HEAD_SIZE + cell_len * (keys_num + 1) > PAGE_SIZE;
    }
}

/* Redefine parent page number.
 * When a internal node page number changed, if it has children nodes, 
 * we also need to redefine parent page number in the children nodes. */
static void redefine_parent(Table *table, uint32_t page_num) {

    void *internal_node = get_page(table->meta_table->table_name, table->pager, page_num);

    uint32_t key_len, keys_num, right_child_page_num;
    key_len = calc_primary_key_length(table);
    keys_num = get_internal_node_keys_num(internal_node);

    /* Redefine each child node parent page. */
    for (int i = 0; i < keys_num; i++) {
        uint32_t child_page_num = get_internal_node_child(internal_node, i, key_len);
        void *child_node = get_page(table->meta_table->table_name, table->pager, child_page_num);
        set_parent_pointer(child_node, page_num); 
        flush_page(table->meta_table->table_name, table->pager, child_page_num);
    }

    /* Don`t forget the right child node. */
    right_child_page_num = get_internal_node_right_child(internal_node);
    void *right_node = get_page(table->meta_table->table_name, table->pager, right_child_page_num);
    set_parent_pointer(right_node, page_num);
    flush_page(table->meta_table->table_name, table->pager, right_child_page_num);
}

/* Covnert root node to leaf node */
static void copy_root_to_leaf_node(Table *table, uint32_t new_page_num, uint32_t key_len, uint32_t value_len) {

    void *root = get_page(table->meta_table->table_name, table->pager, table->root_page_num);
    void *leaf_node = get_page(table->meta_table->table_name, table->pager, new_page_num);

    char *table_name = table->meta_table->table_name;

    initial_leaf_node(leaf_node, false);
    set_leaf_node_cell_num(leaf_node, get_leaf_node_cell_num(root));
    set_leaf_node_next_leaf(leaf_node, get_leaf_node_next_leaf(root));
    uint32_t cell_num = get_leaf_node_cell_num(root); 

    int i;
    for(i = 0; i < cell_num; i++) {
        set_leaf_node_cell_key(leaf_node, i, key_len, value_len, get_leaf_node_cell_key(root, i, key_len, value_len)); 
        memcpy(get_leaf_node_cell_value(leaf_node, key_len, value_len, i), get_leaf_node_cell_value(root, key_len, value_len, i), value_len);
        /* Update refer. */
        update_refer(table_name, table->root_page_num, i, new_page_num, i);
    }

    /* Make clear outsides header. */
    uint32_t column_size = get_column_size(root);
    uint32_t ROOT_LEAF_NODE_HEADER_SIZE = COMMON_NODE_HEADER_SIZE + ROOT_NODE_META_COLUMN_SIZE_SIZE + ROOT_NODE_META_COLUMN_SIZE * column_size;
    memset(root + ROOT_LEAF_NODE_HEADER_SIZE, 0, PAGE_SIZE - ROOT_LEAF_NODE_HEADER_SIZE);
}

/* Copy root to an internal node. */
static void copy_root_to_internal_node(void *root, void *internal_node, uint32_t key_len) {

    /* Copy header. */
    initial_internal_node(internal_node, false);
    set_internal_node_keys_num(internal_node, get_internal_node_keys_num(root));
    set_internal_node_right_child(internal_node, get_internal_node_right_child(root));
    uint32_t keys_num = get_internal_node_keys_num(root);
    uint32_t cell_len = key_len + INTERNAL_NODE_CELL_CHILD_SIZE;

    /* Copy Body. */
    for (int i = 0; i < keys_num; i++) {
        memcpy(get_internal_node_cell(internal_node, i, key_len), get_internal_node_cell(root, i, key_len), cell_len);
    }
}

/* Create new root node. */
static void create_new_root_node(Table *table, uint32_t right_child_page_num, uint32_t key_len, uint32_t value_len) {

    /* Get old root node. */
    void *root = get_page(table->meta_table->table_name, table->pager, table->root_page_num);
    void *right_child = get_page(table->meta_table->table_name, table->pager, right_child_page_num);

    /* Notice that, current next unused page num is not right child page num. 
     * The pager size has increased. */
    uint32_t next_unused_page_num = next_avaliable_page_num(table->pager);

    /* Keep old root, generate a new leaf (or internal) node, 
     * and copy old root data to the new one. 
     * */
    void *left_child = get_page(table->meta_table->table_name, table->pager, next_unused_page_num);
    switch(get_node_type(root)) {
        case LEAF_NODE:
            copy_root_to_leaf_node(table, next_unused_page_num, key_len, value_len);
            break;
        case INTERNAL_NODE:
            copy_root_to_internal_node(root, left_child, key_len);
            redefine_parent(table, next_unused_page_num);
            break;
    }

    set_parent_pointer(left_child, table->root_page_num);
    set_parent_pointer(right_child, table->root_page_num);

    /* Root node now is internal node. */
    set_node_type(root, INTERNAL_NODE);
    set_internal_node_keys_num(root, 1);

    /* Register the new (leaf) leaf node to root. */
    void *max_key = get_max_key(table, left_child, key_len, value_len);
    set_internal_node_key(root, 0, max_key, key_len);
    set_internal_node_child(root, 0, next_unused_page_num, key_len);
    set_internal_node_right_child(root, right_child_page_num);

    flush_page(table->meta_table->table_name, table->pager, next_unused_page_num);
    flush_page(table->meta_table->table_name, table->pager, right_child_page_num);
    flush_page(table->meta_table->table_name, table->pager, table->root_page_num);
}

/* When internal node is full, there is need to generate a new internal node. 
 * And half hight cells in the old internal node will be moved into the new one. */
static void insert_and_split_internal_node(Table *table, uint32_t old_internal_page_num, uint32_t new_child_page_num) {

    uint32_t keys_num, next_unused_page_num, key_len, value_len, cell_len;
    
    /* Get old internal node. */
    void *old_internal_node = get_page(table->meta_table->table_name, table->pager, old_internal_page_num);

    /* Get keys number, key length, value length. cell_len */
    keys_num = get_internal_node_keys_num(old_internal_node);
    value_len = calc_table_row_length(table);
    key_len = calc_primary_key_length(table);
    cell_len = key_len + INTERNAL_NODE_CELL_CHILD_SIZE;

    MetaColumn *primary_key_meta_column = get_primary_key_meta_column(table->meta_table);
    
    /* Get new internal node. */
    next_unused_page_num = next_avaliable_page_num(table->pager);
    void *new_internal_node = get_page(table->meta_table->table_name, table->pager, next_unused_page_num);
    initial_internal_node(new_internal_node, false);
    set_parent_pointer(new_internal_node, get_parent_pointer(old_internal_node));
    set_internal_node_keys_num(new_internal_node, 0);
    set_internal_node_right_child(new_internal_node, 0);
    
    /* Get the new child node. */
    void *new_child_node = get_page(table->meta_table->table_name, table->pager, new_child_page_num);
    /* Get the new child node max key and position in parent node. */
    void *new_child_max_key = get_max_key(table, new_child_node, key_len, value_len);
    uint32_t new_child_max_key_index = get_internal_node_key_index(old_internal_node, new_child_max_key, keys_num, key_len, primary_key_meta_column->column_type);

    /* Maybe the new child is greater than max key, need to compare. */
    uint32_t old_right_page_num = get_internal_node_right_child(old_internal_node);
    void *right_node = get_page(table->meta_table->table_name, table->pager, old_right_page_num);
    void *right_node_max_key = get_max_key(table, right_node, key_len, value_len);
    if (greater(new_child_max_key, right_node_max_key, primary_key_meta_column->column_type)) {
        /* If yes, replace the new child with the origin old right child. */ 
        set_internal_node_right_child(old_internal_node, new_child_page_num);
        if (!is_root_node(old_internal_node)) {
            uint32_t parent_page = get_parent_pointer(old_internal_node);
            void *parent_node = get_page(table->meta_table->table_name, table->pager, parent_page);
            update_internal_node_key(table, parent_node, right_node_max_key, new_child_max_key, key_len, value_len, primary_key_meta_column->column_type);
            flush_page(table->meta_table->table_name, table->pager, parent_page);
        }
        new_child_max_key = right_node_max_key;
        new_child_max_key_index = keys_num; 
        new_child_page_num = old_right_page_num;
    }

    /* Get internal node absolute max key.*/
    void *old_max_key = get_max_key(table, old_internal_node, key_len, value_len);

    uint32_t RIGHT_SPLIT_COUNT = (keys_num + 1) / 2;
    uint32_t LEFT_SPLIT_COUNT = (keys_num + 1) - RIGHT_SPLIT_COUNT;

    int i;
    for(i = keys_num; i >= 0; i--) {
        /* Define which node. */ 
        void *destination_node = i >= LEFT_SPLIT_COUNT ? new_internal_node : old_internal_node;
        
        /* New position. */
        uint32_t index = i % LEFT_SPLIT_COUNT;

        if (i == new_child_max_key_index) {
            set_internal_node_key(destination_node, index, new_child_max_key, key_len); 
            set_internal_node_child(destination_node, index, new_child_page_num, key_len);
        } else if (i > new_child_max_key_index) {
            /* Right cells make cell space. */
            memcpy(get_internal_node_cell(destination_node, index, key_len), get_internal_node_cell(old_internal_node, i - 1, key_len), cell_len);
        } else {
            memcpy(get_internal_node_cell(destination_node, index, key_len), get_internal_node_cell(old_internal_node, i, key_len), cell_len);
        }
    }

    /* For new internal node, it uses old internall node right node as right node. */
    set_internal_node_keys_num(new_internal_node, RIGHT_SPLIT_COUNT);
    set_internal_node_right_child(new_internal_node, get_internal_node_right_child(old_internal_node));

    /* Rest parent for new internal node.*/
    redefine_parent(table, next_unused_page_num);

    /* For old internal node, it uses its last cell as it right child. */
    set_internal_node_keys_num(old_internal_node, LEFT_SPLIT_COUNT);
    set_internal_node_right_child(old_internal_node, get_internal_node_child(old_internal_node, LEFT_SPLIT_COUNT - 1, key_len));
    set_internal_node_keys_num(old_internal_node, LEFT_SPLIT_COUNT - 1);

    redefine_parent(table, old_internal_page_num);

    /* If old internal is root, need to create new root. */
    if (is_root_node(old_internal_node)) {
        create_new_root_node(table, next_unused_page_num, key_len, value_len);
    } else {
        /* Otherwise, it`s a normal internal node. 
         * Maybe the max key change, need update max key in parent internal node. */
        uint32_t parent_page_num = get_parent_pointer(old_internal_node);
        void *parent = get_page(table->meta_table->table_name, table->pager, parent_page_num);
        void *new_max_key = get_max_key(table, old_internal_node, key_len, value_len);
        update_internal_node_key(table, parent, old_max_key, new_max_key, key_len, value_len, primary_key_meta_column->column_type);

        /* And insert a new cell about the new leaf node to the parent internal node. */
        insert_internal_node_cell(table, parent_page_num, next_unused_page_num);
        flush_page(table->meta_table->table_name, table->pager, old_internal_page_num);
        flush_page(table->meta_table->table_name, table->pager, next_unused_page_num);
        flush_page(table->meta_table->table_name, table->pager, parent_page_num);
    }
}

/* Insert new internal node cell. */
void insert_internal_node_cell(Table *table, uint32_t page_num, uint32_t new_child_page_num) {
    
    /* Get current internal node. */
    void *internal_node = get_page(table->meta_table->table_name, table->pager, page_num);
    /* Get the new child node. */
    void *new_child_node = get_page(table->meta_table->table_name, table->pager, new_child_page_num);

    /* Get key, vlaue length. */
    uint32_t value_len = calc_table_row_length(table);
    uint32_t key_len = calc_primary_key_length(table);

    /* Get primary key column meta info. */
    MetaColumn *primary_key_meta_column = get_primary_key_meta_column(table->meta_table);
    uint32_t keys_num = get_internal_node_keys_num(internal_node);
    if (overflow_internal_node(internal_node, keys_num, key_len)) {
        insert_and_split_internal_node(table, page_num, new_child_page_num);
    } else {
        /* Get new child node max key and position in parent node. */
        void *new_child_max_key = get_max_key(table, new_child_node, key_len, value_len);

        /* Get right child node and right child node max key. */
        uint32_t right_child_page_num = get_internal_node_right_child(internal_node);
        void *right_child = get_page(table->meta_table->table_name, table->pager, right_child_page_num);
        void *right_child_max_key = get_max_key(table, right_child, key_len, value_len);

        /* Right child always is the node which has the maximum key. */
        if (greater_equal(new_child_max_key, right_child_max_key, primary_key_meta_column->column_type)) {
            /* Replace old right child */
            set_internal_node_child(internal_node, keys_num, right_child_page_num, key_len);
            set_internal_node_key(internal_node, keys_num, right_child_max_key, key_len);
            if (!is_root_node(internal_node)) {
                uint32_t parent_page_num = get_parent_pointer(internal_node);
                void *parent_node = get_page(table->meta_table->table_name, table->pager, parent_page_num);
                update_internal_node_key(table, parent_node, right_child_max_key, new_child_max_key, key_len, value_len, primary_key_meta_column->column_type);
                flush_page(table->meta_table->table_name, table->pager, parent_page_num);
            }
            set_internal_node_right_child(internal_node, new_child_page_num);
        } else {
            /* If not exist in the right child node, then exist in the cells. */ 
            uint32_t new_child_max_key_index = get_internal_node_key_index(internal_node, new_child_max_key, keys_num, key_len, primary_key_meta_column->column_type);
            /* Move the right cells and make space for the new one. */
            for(int i = keys_num; i > new_child_max_key_index; i--) {
                uint32_t cell_len = key_len + INTERNAL_NODE_CELL_CHILD_SIZE;
                memcpy(get_internal_node_cell(internal_node, i, key_len), get_internal_node_cell(internal_node, i - 1, key_len), cell_len); 
            } 
            set_internal_node_key(internal_node, new_child_max_key_index, new_child_max_key, key_len);
            set_internal_node_child(internal_node,  new_child_max_key_index, new_child_page_num, key_len);
        }
        /* Increase keys number. */
        set_internal_node_keys_num(internal_node, keys_num + 1);
        /* Flush disk. */
        flush_page(table->meta_table->table_name, table->pager, page_num);
    }
}


/* When page full, it will generate a new leaf node. 
 * And half high cell in the old leaf will be moved to new leaf node. */
static void insert_and_split_leaf_node(Cursor *cursor, Row *row) {

    /* Get cell key, value and cell lenght. */
    uint32_t key_len, value_len, cell_length;
    key_len = calc_primary_key_length(cursor->table);
    value_len = calc_table_row_length(cursor->table);
    cell_length = key_len + value_len;

    char *table_name = cursor->table->meta_table->table_name;

    /* Get table primary key meta info. */
    MetaColumn *primary_key_meta_column = get_primary_key_meta_column(cursor->table->meta_table);

    /* Get the old leaf node. */
    void *old_node = get_page(table_name, cursor->table->pager, cursor->page_num);

    /* Get the old leaf node cell count.*/
    uint32_t cell_num = get_leaf_node_cell_num(old_node);

    /* Get the old leaf node max key. */
    void *old_max_key = get_max_key(cursor->table, old_node, key_len, value_len);

    /* Page num start with zero, so the page size is the next page num. */
    uint32_t next_unused_page_num = next_avaliable_page_num(cursor->table->pager);

    /* Get new leaf node, if not exists, pager will generate a new one. */
    void *new_node = get_page(table_name, cursor->table->pager, next_unused_page_num);
    initial_leaf_node(new_node, false);

    /* Both of old leaf node and new leaf node have same parent internal node. */
    set_parent_pointer(new_node, get_parent_pointer(old_node));
    set_leaf_node_next_leaf(new_node, get_leaf_node_next_leaf(old_node));
    set_leaf_node_next_leaf(old_node, next_unused_page_num);

    /* All existing keys plus new key should should be divided 
     * evenly between old (left) and new (right) nodes.
     * Starting from the right, move each key to correct position. */
    uint32_t RIGHT_SPLIT_COUNT = (cell_num + 1) / 2;
    uint32_t LEFT_SPLIT_COUNT = (cell_num + 1) - RIGHT_SPLIT_COUNT;

    int i; 
    for (i = cell_num; i >= 0; i--) {
        /* If index greater than LEAF_SPLIT_COUNT, destination is new old, othersize, stay in the old node. */
        void *destination_node = i >= LEFT_SPLIT_COUNT ? new_node : old_node;
        uint32_t destination_page = i  >= LEFT_SPLIT_COUNT ? next_unused_page_num : cursor->page_num;

        /* New position. */
        uint32_t index_at_node = i % LEFT_SPLIT_COUNT;
        void *destination = get_leaf_node_cell(destination_node, key_len, value_len, index_at_node);

        /* The cursor rigth cells should move one cell to the right to make space for the cursor, include the cell having the old same num as cursor.
         * The cursor leaf cells do`t need to make space.
         * Because i start with cell number, and decrease. so right cells firstly move and make space. */
        if (i == cursor->cell_num) {
            /* Deposit cursor. */
            void *serial_data = serialize_row_data(row, cursor->table);
            memcpy(destination, serial_data, value_len);
            set_leaf_node_cell_key(destination_node, index_at_node, key_len, value_len, row->key);
            db_free(serial_data);
        } else if (i > cursor->cell_num) {
            /* Define new position, and right cells make cell space. */
            memcpy(destination, get_leaf_node_cell(old_node, key_len, value_len, i - 1), cell_length);
            /* Update refer. */
            update_refer(table_name, cursor->page_num, i - 1, destination_page, index_at_node);
        } else {
            /* Define new position. */
            memcpy(destination, get_leaf_node_cell(old_node, key_len, value_len, i), cell_length);
            /* Update refer. */
            update_refer(table_name, cursor->page_num, i, destination_page, index_at_node);
        }
    }

    /* Set cell num */
    set_leaf_node_cell_num(old_node, LEFT_SPLIT_COUNT);
    set_leaf_node_cell_num(new_node, RIGHT_SPLIT_COUNT);
    set_leaf_node_next_leaf(old_node, next_unused_page_num);

    /* If the old node is root, need to creat new root node. */
    if (is_root_node(old_node)) 
        create_new_root_node(cursor->table, next_unused_page_num, key_len, value_len); 
    else {
        /* Otherwise, it`s a normal leaf node. 
         * Maybe the max key change, need update max key in parent internal node. */
        uint32_t parent_page_num = get_parent_pointer(old_node);
        void *parent = get_page(table_name, cursor->table->pager, parent_page_num);
        void *new_max_key = get_max_key(cursor->table, old_node, key_len, value_len);
        update_internal_node_key(cursor->table, parent, old_max_key, new_max_key, key_len, value_len, primary_key_meta_column->column_type);
        
        /* And insert a new cell about the new leaf node to the parent internal node. */
        insert_internal_node_cell(cursor->table, parent_page_num, next_unused_page_num);
        flush_page(table_name, cursor->table->pager, cursor->page_num);
        flush_page(table_name, cursor->table->pager, next_unused_page_num);
        flush_page(table_name, cursor->table->pager, parent_page_num);
    }
}

/* Insert a new cell in leaf node */
void insert_leaf_node_cell(Cursor *cursor, Row *row) {

    char *table_name = cursor->table->meta_table->table_name;
    void *node = get_page(table_name, cursor->table->pager, cursor->page_num); 
    
    /* Get data. */ 
    uint32_t cell_num, value_len, key_len, cell_length;
    cell_num = get_leaf_node_cell_num(node);
    value_len = calc_table_row_length(cursor->table);
    key_len = calc_primary_key_length(cursor->table);
    cell_length = value_len + key_len;


    if (overflow_leaf_node(node, key_len, value_len, cell_num)) 
        insert_and_split_leaf_node(cursor, row);
    else {
        if (cursor->cell_num < cell_num) {
            /* Make room for new cell. */
            int i;
            for (i = cell_num; i > cursor->cell_num; i--) {
                /* Movement. */
                memcpy(get_leaf_node_cell(node, key_len, value_len, i), get_leaf_node_cell(node, key_len, value_len, i - 1), cell_length);
                /* Update refer. */
                update_refer(table_name, cursor->page_num, i - 1, cursor->page_num, i);
            }
        }
        
        /* Insert the new row. */
        set_leaf_node_cell_key(node, cursor->cell_num, key_len, value_len, row->key);
        void *destination = serialize_row_data(row, cursor->table);
        memcpy(get_leaf_node_cell_value(node, key_len, value_len, cursor->cell_num), destination, value_len);
        
        /* Check if the max key in leaf node has changed, that may impact the parent internal node. */
        if (!is_root_node(node) && cursor->cell_num == cell_num) {
            uint32_t parent_page_num = get_parent_pointer(node);
            void *parent_node = get_page(table_name, cursor->table->pager, parent_page_num);
            void *old_max_key = get_leaf_node_cell_key(node, cell_num - 1, key_len, value_len);
            MetaColumn *primary_key_meta_column = get_primary_key_meta_column(cursor->table->meta_table);
           
            /* Logic check.*/
            assert_true(greater_equal(row->key, old_max_key, primary_key_meta_column->column_type), "Logic Error occurs in <insert_leaf_node_cell>");

            update_internal_node_key(cursor->table, parent_node, old_max_key, row->key, key_len, value_len, primary_key_meta_column->column_type);
            flush_page(table_name, cursor->table->pager, parent_page_num);
        }
        
        /* Cell number increases. */
        set_leaf_node_cell_num(node, ++cell_num);
        
        /* Flush into disk. */
        flush_page(table_name, cursor->table->pager, cursor->page_num);
    }
}

/* If row is deleted*/
bool cursor_is_deleted(Cursor *cursor) {

    uint32_t key_len, value_len;

    Table *table = cursor->table;
    key_len = calc_primary_key_length(table); 
    value_len = calc_table_row_length(table); 

    void *leaf_node = get_page(table->meta_table->table_name, table->pager, cursor->page_num);
    
    void *destination = get_leaf_node_cell_value(leaf_node, key_len, value_len, cursor->cell_num);
 
    int i, offset =0;
    for(i = 0; i < table->meta_table->all_column_size; i++) {
        MetaColumn *meta_column = table->meta_table->meta_column[i];
        if (meta_column->sys_reserved && strcmp(meta_column->column_name, EXPIRED_XID_COLUMN_NAME) == 0) {
            int64_t expired_xid = *(int64_t *)(destination + offset);
            return expired_xid != 0;
        }
        offset += meta_column->column_length;
    }
    return false;
}

/* Update row system reserved columns. */
void update_row_data(Row *row, Cursor *cursor) {

    uint32_t key_len, value_len;

    Table *table = cursor->table;
    key_len = calc_primary_key_length(table); 
    value_len = calc_table_row_length(table); 
    
    /* Get leaf node. */
    void *leaf_node = get_page(table->meta_table->table_name, table->pager, cursor->page_num);

    /* Serialize row. */
    void *destination = serialize_row_data(row, cursor->table);

    /* Overcover leaf node. */
    memcpy(get_leaf_node_cell_value(leaf_node, key_len, value_len, cursor->cell_num), destination, value_len);

    flush_page(table->meta_table->table_name, table->pager, cursor->page_num);
}


/* Get replace child node. */
static void *get_replaced_child_node(Table *table, void *node) {

    if (get_node_type(node) == INTERNAL_NODE) {
        uint32_t keys_num = get_internal_node_keys_num(node);
        uint32_t right_child_page_num = get_internal_node_right_child(node);

        /* Only when have one child, fall back*/
        void *child_node;
        if (keys_num == 1 && right_child_page_num == 0) {
            uint32_t key_len = calc_primary_key_length(table);
            uint32_t child_page_num = get_internal_node_child(node, 0, key_len);
            child_node = get_page(table->meta_table->table_name, table->pager, child_page_num);
            return get_replaced_child_node(table, child_node);
        } else if (keys_num == 0 && right_child_page_num != 0) {
            child_node = get_page(table->meta_table->table_name, table->pager, right_child_page_num);
            return get_replaced_child_node(table, child_node);
        }
    }
    return node;
}

/* When root is empty to do. */
static void empty_root_node(Table *table) {
    void *root = get_page(table->meta_table->table_name, table->pager, table->root_page_num);
    assert_true(get_node_type(root) == INTERNAL_NODE, "Sysmtem error, when empty root node, it must be internal type.");
    set_node_type(root, LEAF_NODE);
    set_leaf_node_cell_num(root, 0);
    set_leaf_node_next_leaf(root, 0);
}

/* Delete internal node. */
void delete_internal_node_cell(Table *table, uint32_t page_num, void *key, DataType key_data_type) {

    /* Get internal node. */
    void *internal_node = get_page(table->meta_table->table_name, table->pager, page_num);

    /* Get key number, key length, cell lenght and position of key. */
    uint32_t key_num, key_len, cell_len, value_len, key_index;
    key_num = get_internal_node_keys_num(internal_node);
    key_len = calc_primary_key_length(table);
    cell_len = key_len + INTERNAL_NODE_CELL_CHILD_SIZE;
    value_len = calc_table_row_length(table);
    key_index = get_internal_node_key_index(internal_node, key, key_num, key_len, key_data_type);

    /* Get max key in internal node cell. */
    void *max_key = key_num == 0 ? NULL : get_internal_node_key(internal_node, key_num - 1, key_len);

    /* If the key greater than max key, it means it is in right child node. */
    if (greater(key, max_key, key_data_type)) {
        /* If key number is one, no need to keep right node, delete it. 
         * If key number is zero, only left right node. After deleting it, check if root, empty root node or delete parent node cell.
         * If key number more than one, replace max key cell as right child node.
         * */
        if (key_num == 1) 
            set_internal_node_right_child(internal_node, 0);
        else if (key_num == 0) {
            set_internal_node_right_child(internal_node, 0);
            if (is_root_node(internal_node))
                empty_root_node(table);
            else {
                uint32_t parent_page_num = get_parent_pointer(internal_node);
                delete_internal_node_cell(table, parent_page_num, key, key_data_type);
            }
        } else {
            void *old_max_key = get_max_key(table, internal_node, key_len, value_len);
            void *new_max_key = get_internal_node_key(internal_node, key_num - 1, key_len);
            uint32_t max_key_page_num = get_internal_node_child(internal_node, key_num - 1, key_len);
            set_internal_node_right_child(internal_node, max_key_page_num);
            memset(get_internal_node_cell(internal_node, key_num - 1, key_len), 0, cell_len);
            /* Decrease cell number. */
            set_internal_node_keys_num(internal_node, --key_num);
            /* Update key.*/
            update_internal_node_key(table, internal_node, old_max_key, new_max_key, key_len, value_len, key_data_type);
        }
    } else {
        /* Check if deleting the last cell.
         * If last internal cell, it will impact its parent internal node (if exists). */
        if (key_index == key_num - 1) {

            /* Check if current internal node is root, absolutely, root node has no parent node. */
            if (!is_root_node(internal_node)) {
                uint32_t parent_page = get_parent_pointer(internal_node);
                void *parent_internal_node = get_page(table->meta_table->table_name, table->pager, parent_page);

                /* Check if the last one cell in ther internal node. 
                 * If no, we need to replace key with previous key.
                 * If yes, more complex, we need to check if right child node exists, 
                 * If not, need to delete the cell in parent internal node. */
                if (key_num != 1) {
                    /*void *previous_key = get_internal_node_key(internal_node, key_index - 1, key_len);*/
                    /*update_internal_node_key(table, parent_internal_node, key, previous_key, key_len, value_len, key_data_type);*/
                    /*flush_page(table->pager, parent_page);*/
                } else {
                    /* It means there is no right child node. We need to delete the cell in parent internal node. */
                    uint32_t right_child_page_num = get_internal_node_right_child(internal_node);
                    if (right_child_page_num == 0) 
                        delete_internal_node_cell(table, parent_page, key, key_data_type);
                }
            } else {
                if (key_num == 1) {
                    /* If root node, firstly check if exist right child node. 
                     * If not is was empty root, deal with empty root. */
                    uint32_t right_child_page_num = get_internal_node_right_child(internal_node);
                    if (right_child_page_num == 0) 
                        empty_root_node(table);
                }
            }
            
            /* Make last one NULL. */
            memset(get_internal_node_cell(internal_node, key_index, key_len), 0, cell_len);
            /* Decrease cell number. */
            set_internal_node_keys_num(internal_node, --key_num);
        } else {

            /* Move right cell forward to cover the obsolute cell sapce. 
             * If the last cell, set NULL. */
            for (uint32_t i = key_index; i < key_num; i++) {
                if (i != key_num - 1) 
                    memcpy(get_internal_node_cell(internal_node, i, key_len), get_internal_node_cell(internal_node, i + 1, key_len), cell_len);
                else 
                    memset(get_internal_node_cell(internal_node, i, key_len), 0, cell_len);
            }
            /* Decrease cell number. */
            set_internal_node_keys_num(internal_node, --key_num);
        }
    }
    
    /* If there is no cells, no right child and not a root node, ok, make it obsolute. */
    if (!is_root_node(internal_node) && key_num == 0 && get_internal_node_right_child(internal_node) == 0)
        make_obsolute_node(internal_node);

    flush_page(table->meta_table->table_name, table->pager, page_num);
}

/* Delete leaf node. */
void delete_leaf_node_cell(Cursor *cursor, void *key) {

    char *table_name = cursor->table->meta_table->table_name;

    /* Get leaf node and cell number. */
    void *leaf_node = get_page(table_name, cursor->table->pager, cursor->page_num);
    uint32_t cell_num = get_leaf_node_cell_num(leaf_node);

    /* Get key lenght, value length and cell lenght. */
    uint32_t key_len = calc_primary_key_length(cursor->table);
    uint32_t value_len = calc_table_row_length(cursor->table);
    uint32_t cell_length = value_len + key_len;
    void *obs_key = get_leaf_node_cell_key(leaf_node, cursor->cell_num, key_len, value_len);
    
    MetaColumn *primary_key_meta_column = get_primary_key_meta_column(cursor->table->meta_table);

    /* Theoretically, key and obs_key should be equal. */
    assert_true(equal(obs_key, key, primary_key_meta_column->column_type), "System error, should delete key '%s' but delete key '%s' in fact. ", (char *)key, (char *)obs_key);


    /* Need to check if the last cell in the leaf node. */
    if (cursor->cell_num == cell_num - 1) {

        /* The last cell has the max key, so if it`s parent node is internal node, need to repalce key. */
        if (!is_root_node(leaf_node)) {
            uint32_t parent_page = get_parent_pointer(leaf_node);
            void *parent_node = get_page(table_name, cursor->table->pager, parent_page);

            /* If cell num is zero, it means it`s the only one in the leaf node, 
             * after delete it we also need to delete the cell in internal node. 
             * If not zero, it means these are sibling cells, just replace it with its previous cell. */
            if (cursor->cell_num == 0)
                delete_internal_node_cell(cursor->table, parent_page, obs_key, primary_key_meta_column->column_type);
            else {
                void *obs_previous_key = get_leaf_node_cell_key(leaf_node, cursor->cell_num - 1, key_len, value_len);
                update_internal_node_key(cursor->table, parent_node, obs_key, obs_previous_key, key_len, value_len, primary_key_meta_column->column_type);
                flush_page(table_name, cursor->table->pager, parent_page);
            }
        }

        /* If old cell is the last one, just make it null. */
        memset(get_leaf_node_cell(leaf_node, key_len, value_len, cell_num - 1), 0, cell_length);

        /* Update refer null. */
        update_refer(table_name, cursor->page_num, cell_num - 1, -1, -1);
    } else {

        /* Move right cell forward to cover the obsolute cell sapce. */
        for (uint32_t i = cursor->cell_num; i < cell_num; i++) {
            if (i == cell_num - 1) 
                memset(get_leaf_node_cell(leaf_node, key_len, value_len, i), 0, cell_length);
            else {
                memcpy(get_leaf_node_cell(leaf_node, key_len, value_len, i), get_leaf_node_cell(leaf_node, key_len, value_len, i + 1), cell_length);
                /* Update postion-changed row refer. */
                update_refer(table_name, cursor->page_num, i + 1, cursor->page_num, i);
            }
        }
        /* Update deleted row refer. */
        update_refer(table_name, cursor->page_num, cursor->cell_num, -1, -1);
    }

    /* Decrease cell number. */
    set_leaf_node_cell_num(leaf_node, --cell_num);

    /* If there is no cells and not root node, make it obsolute. */
    if (!is_root_node(leaf_node) && cell_num == 0)
        make_obsolute_node(leaf_node);

    flush_page(table_name, cursor->table->pager, cursor->page_num);
}

/* Root fall back. */
void root_fall_back_root_node(Table *table) {
    uint32_t key_len, value_len, cell_len;

    /* Get key length, value length, cell length. */
    key_len = calc_primary_key_length(table); 
    value_len = calc_table_row_length(table); 
    cell_len = key_len + INTERNAL_NODE_CELL_CHILD_SIZE;

    void *root = get_page(table->meta_table->table_name, table->pager, table->root_page_num);

    /* Only deal with internal node. Leaf not root does not need to fall back. */
    if (get_node_type(root) == INTERNAL_NODE) {
        void *replace_node = get_replaced_child_node(table, root);
        if (root == replace_node) return;
        switch(get_node_type(replace_node)) {
            case LEAF_NODE: {
                set_node_type(root, LEAF_NODE);
                uint32_t cells_num = get_leaf_node_cell_num(replace_node); 
                /* May be overflow. wait for resolution. */
                assert_false(overflow_leaf_node(root, key_len, value_len, cells_num), "Leaf node overflow when root fall back.\n");
                for (uint32_t i = 0; i < cells_num; i++) {
                    set_leaf_node_cell_key(root, i, key_len, value_len, get_leaf_node_cell_key(replace_node, i, key_len, value_len)); 
                    memcpy(get_leaf_node_cell_value(root, key_len, value_len, i), get_leaf_node_cell_value(replace_node, key_len , value_len, i), value_len);
                }
                set_leaf_node_cell_num(root, cells_num);
                break;
            }
            case INTERNAL_NODE: {
                set_node_type(root, INTERNAL_NODE);
                uint32_t keys_num = get_internal_node_keys_num(replace_node);
                /* May be overflow. wait for resolution. */
                assert_false(overflow_internal_node(root, keys_num, key_len), "Internal node overflow when root fall back.\n");
                for (uint32_t i = 0; i < keys_num; i++) {
                    memcpy(get_internal_node_cell(root, i, key_len), get_internal_node_cell(replace_node, i, key_len), cell_len);
                    uint32_t child_node_num = get_internal_node_child(replace_node, i, key_len);
                    void *child_node = get_page(table->meta_table->table_name, table->pager, child_node_num);
                    set_parent_pointer(child_node, table->root_page_num);
                }
                set_internal_node_keys_num(root, keys_num);
                uint32_t right_child_page_num = get_internal_node_right_child(replace_node);
                set_internal_node_right_child(root, right_child_page_num);
                void *right_child = get_page(table->meta_table->table_name, table->pager, right_child_page_num);
                set_parent_pointer(right_child, table->root_page_num);
            }
        }
    }
} 

/* Deserialize meta column */
MetaColumn *deserialize_meta_column(void *destination) {
    MetaColumn *meta_column = db_malloc(sizeof(MetaColumn), SDT_META_COLUMN);
    strcpy(meta_column->column_name, destination); 
    meta_column->column_type = (DataType)*(uint32_t *)(destination + ROOT_NODE_META_COLUMN_NAME_SIZE);
    meta_column->column_length = *(uint32_t *)(destination + ROOT_NODE_META_COLUMN_NAME_SIZE + ROOT_NODE_META_COLUMN_TYPE_SIZE);
    meta_column->is_primary = (bool)*(uint8_t *)(destination + ROOT_NODE_META_COLUMN_NAME_SIZE + ROOT_NODE_META_COLUMN_TYPE_SIZE + ROOT_NODE_META_COLUMN_LENGTH_SIZE);
    if (meta_column->column_type == T_REFERENCE)
        strcpy(meta_column->table_name, destination + ROOT_NODE_META_COLUMN_NAME_SIZE + ROOT_NODE_META_COLUMN_TYPE_SIZE + ROOT_NODE_META_COLUMN_LENGTH_SIZE + ROOT_NODE_IS_PRIMARY_SIZE);
    meta_column->sys_reserved = (bool)*(uint8_t *)(destination + ROOT_NODE_META_COLUMN_NAME_SIZE + ROOT_NODE_META_COLUMN_TYPE_SIZE + ROOT_NODE_META_COLUMN_LENGTH_SIZE + ROOT_NODE_IS_PRIMARY_SIZE + ROOT_NODE_META_COLUMN_TABLE_NAME_SIZE);
    return meta_column;
}

/* Deserialize meta column */
void *serialize_meta_column(MetaColumn *meta_column) {
    void *destination= db_malloc(ROOT_NODE_META_COLUMN_SIZE, SDT_VOID);
    strcpy(destination, meta_column->column_name);
    *(uint32_t *)(destination + ROOT_NODE_META_COLUMN_NAME_SIZE) = (uint32_t) meta_column->column_type;
    *(uint32_t *)(destination + ROOT_NODE_META_COLUMN_NAME_SIZE + ROOT_NODE_META_COLUMN_TYPE_SIZE) = (uint32_t) meta_column->column_length;
    *(uint8_t *)(destination + ROOT_NODE_META_COLUMN_NAME_SIZE + ROOT_NODE_META_COLUMN_TYPE_SIZE + ROOT_NODE_META_COLUMN_LENGTH_SIZE) = meta_column->is_primary;  
    if (meta_column->column_type == T_REFERENCE)
        strcpy(destination + ROOT_NODE_META_COLUMN_NAME_SIZE + ROOT_NODE_META_COLUMN_TYPE_SIZE + ROOT_NODE_META_COLUMN_LENGTH_SIZE + ROOT_NODE_IS_PRIMARY_SIZE, meta_column->table_name);
    *(uint8_t *)(destination + ROOT_NODE_META_COLUMN_NAME_SIZE + ROOT_NODE_META_COLUMN_TYPE_SIZE + ROOT_NODE_META_COLUMN_LENGTH_SIZE + ROOT_NODE_IS_PRIMARY_SIZE + ROOT_NODE_META_COLUMN_TABLE_NAME_SIZE) = meta_column->sys_reserved;  
    return destination;
}

/* Get row value. */
static void *get_row_value(Row *row, MetaColumn *meta_column) {
    char *column_name = meta_column->column_name;
    for(uint32_t i = 0; i < row->column_len; i++) {
        if (strcmp(column_name, row->data[i]->key) == 0)
           return row->data[i]->value;
    }
    db_log(PANIC, "Inner error, unknown column ", column_name);
    return NULL;
}

/* Serialize row data */
void *serialize_row_data(Row *row, Table *table) {
    uint32_t row_length = calc_table_row_length(table);
    void *destination = db_malloc(row_length, SDT_VOID);
    MetaTable *meta_table = table->meta_table;
    uint32_t offset = 0;
    for(int32_t i = 0; i < meta_table->all_column_size; i++) {
        MetaColumn *meta_column = meta_table->meta_column[i]; 
        void *value = get_row_value(row, meta_column);
        memcpy(destination + offset, value, meta_column->column_length);
        offset += meta_column->column_length;
    }
    return destination;
}
