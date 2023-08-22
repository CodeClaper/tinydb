#include <stdint.h>
#include "data.h"

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
// get keys number in the node by index
uint32_t get_internal_node_keys(void *node, uint32_t index);
// get child value in the node by index
uint32_t get_internal_node_child(void *node, uint32_t index);
// get internal node child page num
uint32_t get_internal_node_cell_child_page_num(void *node, uint32_t key, uint32_t keys_num);
// get leaf node cell key
uint32_t get_leaf_node_cell_key(void *node, uint32_t index, uint32_t row_len);
// get leaf node cell index
uint32_t get_leaf_node_cell_index(void *node, uint32_t key, uint32_t cell_num, uint32_t row_len);
// get index meta column pointer
void *get_meta_column_pointer(void *root_node, uint32_t index);
// set index meta column
void set_meta_column(void *root_node, void *destination, uint32_t index);
// get meta column size
uint32_t get_root_node_meta_column_size();
// initialize leaf node
void initial_leaf_node(void *leaf_node, bool is_root);
// insert a new leaf node
void insert_leaf_node(Cursor *cursor, Row *row);
// deserialize meta column
MetaColumn *deserialize_meta_column(void *destination);
// deserialize meta column
void *serialize_meta_column(MetaColumn *meta_column);
// serialize row data
void *serialize_row_data(Row *row, Table *table);
