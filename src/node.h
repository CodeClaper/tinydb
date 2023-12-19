#include "data.h"
#include <stdint.h>

/* If obsolute node. */
bool is_obsolute_node(void *node);

/* Set obsolute flag. */
void set_obsolute_node(void *node, bool flag);

/* Get node type. */
NodeType get_node_type(void *node);

/* Set node type. */
void set_node_type(void *node, NodeType node_type);

/* Set if root node. */
void set_root_node(void *node, bool if_root_node);

/* Get root node column size. */
uint32_t get_column_size(void *node);

/* Set root node column size. */
void set_column_size(void *node, uint32_t value);

/* Get leaf node cell number. */
uint32_t get_leaf_node_cell_num(void *node);

/* Get internal node keys number. */
uint32_t get_internal_node_keys_num(void *node);

/* Get right child of internal node. */
uint32_t get_internal_node_right_child(void *node);

/* Get keys number in the node by index. */
void* get_internal_node_key(void *node, uint32_t index, uint32_t key_len);

/* Get child value in the node by index. */
uint32_t get_internal_node_child(void *node, uint32_t index, uint32_t key_len);

/* Get internal node child page num. */
uint32_t get_internal_node_cell_child_page_num(void *node, void *key, uint32_t keys_num, uint32_t key_len, DataType primary_key_data_type);

/* Get leaf node cell key. */
void *get_leaf_node_cell_key(void *node, uint32_t index, uint32_t key_len,uint32_t value_len);

/* Get leaf node cell value pointer. */
void *get_leaf_node_cell_value(void *node, uint32_t key_len, uint32_t value_len, uint32_t index);

/* Get leaf node cell index. */
uint32_t get_leaf_node_cell_index(void *node, void *key, uint32_t cell_num, uint32_t key_len, uint32_t value_len, DataType key_data_type);

/* Get index meta column pointer. */
void *get_meta_column_pointer(void *root_node, uint32_t index);

/* Set index meta column. */
void set_meta_column(void *root_node, void *destination, uint32_t index);

/* Get meta column size. */
uint32_t get_root_node_meta_column_size();

/* Initialize leaf node. */
void initial_leaf_node(void *leaf_node, bool is_root);

/* Insert new internal node cell. */
void insert_internal_node_cell(Table *table, uint32_t page_num, uint32_t new_child_page_num);

/* Insert a new leaf node cell. */
void insert_leaf_node_cell(Cursor *cursor, Row *row);

/* Delete leaf node. */
void delete_leaf_node_cell(Cursor *obs_cursor, void *key);

/* Root fall back. */
void root_fall_back_root_node(Table *table);

/* Deserialize meta column. */
MetaColumn *deserialize_meta_column(void *destination);

/* Deserialize meta column. */
void *serialize_meta_column(MetaColumn *meta_column);

/* Serialize row data. */
void *serialize_row_data(Row *row, Table *table);

