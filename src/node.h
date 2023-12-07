#include "data.h"
#include <stdint.h>

// get node type
NodeType get_node_type(void *node);

// set node type
void set_node_type(void *node, NodeType node_type);

// set if root node
void set_root_node(void *node, bool if_root_node);

// get root node column size
uint32_t get_column_size(void *node);

// set root node column size
void set_column_size(void *node, uint32_t value);

// get leaf node cell number
uint32_t get_leaf_node_cell_num(void *node);

// get internal node keys number
uint32_t get_internal_node_keys_num(void *node);

// get right child of internal node 
uint32_t get_internal_node_right_child(void *node);

// get keys number in the node by index
void* get_internal_node_keys(void *node, uint32_t index, uint32_t key_len);

// get child value in the node by index
uint32_t get_internal_node_child(void *node, uint32_t index, uint32_t key_len);

// get internal node child page num
uint32_t get_internal_node_cell_child_page_num(void *node, void *key, uint32_t keys_num, uint32_t key_len, DataType primary_key_data_type);

// get leaf node cell key
void *get_leaf_node_cell_key(void *node, uint32_t index, uint32_t key_len,uint32_t value_len);

// get leaf node cell value pointer
void *get_leaf_node_cell_value(void *node, uint32_t key_len, uint32_t value_len, uint32_t index);

// get leaf node cell index
uint32_t get_leaf_node_cell_index(void *node, void *key, uint32_t cell_num, uint32_t key_len, uint32_t value_len, DataType key_data_type);

// get index meta column pointer
void *get_meta_column_pointer(void *root_node, uint32_t index);

// set index meta column
void set_meta_column(void *root_node, void *destination, uint32_t index);

// get meta column size
uint32_t get_root_node_meta_column_size();

// initialize leaf node
void initial_leaf_node(void *leaf_node, bool is_root);

/* Insert a new leaf node cell. */
void insert_leaf_node_cell(Cursor *cursor, Row *row);

/* Delete leaf node. */
void delete_leaf_node_cell(Cursor *obs_cursor);

// deserialize meta column
MetaColumn *deserialize_meta_column(void *destination);

// deserialize meta column
void *serialize_meta_column(MetaColumn *meta_column);

// serialize row data
void *serialize_row_data(Row *row, Table *table);

