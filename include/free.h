#include "data.h"

/* Copy value */
void free_value(void *value, DataType data_type);

/* Free KeyValue */
void free_key_value(KeyValue *key_value);

/* Free Block. */
void free_block(void *value);

/* Free row. */
void free_row(Row *row);

/* Free select result. */
void free_select_result(SelectResult *select_result);

/* Free meta column. */
void free_meta_column(MetaColumn *meta_column);

/* Free meta table. */
void free_meta_table(MetaTable *meta_table);

/* Free Pager. */
void free_pager(Pager *pager);

/* Free table. */
void free_table(Table *table);

/* Free TableBufferEntry. */
void free_table_buffer_entry(TableBufferEntry *entry);

/* Free cursor. */
void free_cursor(Cursor *cursor);

/* Free Refer. */
void free_refer(Refer *refer);

/* Free ReferValue. */
void free_refer_value(ReferValue *refer_value);

/* Free ReferUpdateEntity. */
void free_refer_update_entity(ReferUpdateEntity *refer_update_entity);

/* Free value item node. */
void free_value_item_node(ValueItemNode *value_item_node);

/* Free function value node. */
void free_function_value_node(FunctionValueNode *function_value_node);

/* Free function node. */
void free_function_node(FunctionNode *function_node);

/* Free ScalarExpNode. */
void free_scalar_exp_node(ScalarExpNode *scalar_exp_node);

/* Free ScalarExpSetNode. */
void free_scalar_exp_set_node(ScalarExpSetNode *scalar_exp_set_node);

/* Copy ScalarExpSetNode. */
ScalarExpSetNode *copy_scalar_exp_set_node(ScalarExpSetNode *scalar_exp_set_node);

/* Free column set node. */
void free_column_set_node(ColumnSetNode *column_set_node);

/* Free column def node. */
void free_column_def_node(ColumnDefNode *column_def_node);

/* Free column def set node. */
void free_column_def_set_node(ColumnDefSetNode *column_def_set_node);

/* Free value item set node. */
void free_value_item_set_node(ValueItemSetNode *value_item_set_node);

/* Free primary key node. */
void free_primary_key_node(PrimaryKeyNode *primary_key_node);

/* Free select items node. */
void free_select_items_node(SelectItemsNode *select_items_node);

/* Free condition node. */
void free_condition_node(ConditionNode *condition_node);

/* Free SelectionNode. */
void free_selection_node(SelectionNode *selection_node);

/* Free select node. */
void free_select_node(SelectNode *select_node);

/* Free insert node. */
void free_insert_node(InsertNode *insert_node);

/* Free create table node. */
void free_create_table_node(CreateTableNode *create_table_node);

/* Free statment */
void free_statment(Statement *stmt);

/* Free statements. */
void free_statements(Statements *statements);

/* Free query param. */
void free_query_param(QueryParam *query_param);

/* Free table list */
void free_table_list(TableList *table_list);

/* Free TransactionHandle. */
void free_transaction_handle(TransactionHandle *trans_handle);

/* Free LockHandle. */
void free_lock_handle(LockHandle *lock_state);

/* Free Map. */
void free_map(Map *map);

/* Free MapList. */
void free_map_list(MapList *map_list);

/* Free DBResult. */
void free_db_result(DBResult *result);

/* Free DBResultSet. */ 
void free_db_result_set(DBResultSet *result_set);

/* Free LogEntry.*/
void free_log_entry(LogEntry *log_entry);

/* Free XLogEntry. */
void free_xlog_entry(XLogEntry *xlog_entry);
