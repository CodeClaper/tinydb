#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "free.h"
#include "mmu.h"
#include "refer.h"
#include "asserts.h"
#include "table.h"
#include "index.h"
#include "xlog.h"
#include "log.h"
#include "list.h"

/* Free value */
void free_value(void *value, DataType data_type) {
    if (value) {
        switch (data_type) {
            case T_REFERENCE:
                free_refer((Refer *)value);
                break;
            case T_ROW:
                free_row((Row *)value);
                break;
            default:
                db_free(value);
                break;
        }
    }
}

/* Free KeyValue */
void free_key_value(KeyValue *key_value) {
    if (key_value) {
        if (key_value->key)
            db_free(key_value->key);
        if (key_value->table_name)
            db_free(key_value->table_name);
        if (key_value->is_array)
            free_array_value(key_value->value);
        else
            free_value(key_value->value, key_value->data_type);
        db_free(key_value);
    } 
}

/* Free Block. */
void free_block(void *value) {
    if (value)
        db_free(value);
}

/* Free DataTyepNode. */
void free_data_type_node(DataTypeNode *data_type_node) {
    if (data_type_node) {
        if (data_type_node->table_name)
            db_free(data_type_node->table_name);
        db_free(data_type_node);
    }
}

/* Free Refer. */
void free_refer(Refer *refer) {
    if (refer) {
        db_free(refer);
    }
}

/* Free ReferUpdateEntity. */
void free_refer_update_entity(ReferUpdateEntity *refer_update_entity) {
    if (refer_update_entity) {
        free_refer(refer_update_entity->old_refer);
        free_refer(refer_update_entity->new_refer);
        db_free(refer_update_entity);
    }
}

/* Free Row. */
void free_row(Row *row) {
    if (row) {
        /* free key. */
        if (row->key)
            db_free(row->key);
        /* free row data. */
        if (row->data) 
            free_list_deep(row->data);
        /* table name. */
        if (row->table_name)
            db_free(row->table_name);

        db_free(row);
    }
}

/* Free SelectResult. */
void free_select_result(SelectResult *select_result) {
    if (select_result) {
        /* free table name. */
        if (select_result->table_name)
            db_free(select_result->table_name);

        if (select_result->range_variable) 
            db_free(select_result->range_variable);

        if (select_result->rows) 
            /* free rows. */
            free_list_deep(select_result->rows);

        if (select_result->derived)
            free_select_result(select_result->derived);

        db_free(select_result);
    }
}

/* Free meta column. */
void free_meta_column(MetaColumn *meta_column) {
    if (meta_column) 
        db_free(meta_column);
}

/* Free meta table. */
void free_meta_table(MetaTable *meta_table) {
    if (meta_table) {
        if (meta_table->table_name) {
            db_free(meta_table->table_name);
        }
        uint32_t i;
        for (i = 0; i < meta_table->all_column_size; i++) {
            free_meta_column(meta_table->meta_column[i]);
        }
        db_free(meta_table->meta_column);
        db_free(meta_table);
    }
}

/* Free column */
void free_column_node(ColumnNode *column_node) {
    if (column_node) {

        /* Free subColumn. */
        if (column_node->has_sub_column && column_node->sub_column)
            free_column_node(column_node->sub_column);

        /* Free subScalarExpNode. */
        if (column_node->has_sub_column && column_node->scalar_exp_list)
            free_list_deep(column_node->scalar_exp_list);

        if (column_node->column_name)
            db_free(column_node->column_name);

        if (column_node->range_variable)
            db_free(column_node->range_variable);

        db_free(column_node);
    }

}

/* Free Pager. */
void free_pager(Pager *pager) {
    if (pager) {
        uint32_t i;
        for (i = 0; i < pager->size; i++) {
            db_free(pager->pages[i]);
        }
        db_free(pager);
    }
}

/* Free table */
void free_table(Table *table) {
    if (table) {
        free_pager(table->pager);
        free_meta_table(table->meta_table);
        db_free(table);
    }
}

/* Free TableBufferEntry. */
void free_table_buffer_entry(TableBufferEntry *entry) {
    if (entry) {
        free_table(entry->table);
        db_free(entry);
    }
}

/* Free cursor. */
void free_cursor(Cursor *cursor) {
    if (cursor) {
        /* Notice: Table is used for cache, not free here. */
        /*free_table(cursor->table);*/
        db_free(cursor);
    }
} 

/* Free AtomNode. */
void free_atom_node(AtomNode *atom_node) {
    if (atom_node) {
        switch (atom_node->type) {
            case A_STRING:
                db_free(atom_node->value.strval);
                break;
            case A_REFERENCE:
                free_refer_value(atom_node->value.referval);
                break;
            default:
                break;
        }
        db_free(atom_node);
    }
}

/* Free value item node. */
void free_value_item_node(ValueItemNode *value_item_node) {
    if (value_item_node) {
        switch (value_item_node->type) {
            case V_ATOM:
                free_atom_node(value_item_node->value.atom);
                break;
            case V_ARRAY:
                free_list_deep(value_item_node->value.value_list);
                break;
            case V_NULL:
                break;
            default:
                UNEXPECTED_VALUE(value_item_node->type);
                break;
        }
        db_free(value_item_node);
    }
}

/* Free function value node. */
void free_function_value_node(FunctionValueNode *function_value_node) {
    if (function_value_node) {
        switch(function_value_node->value_type) {
           case V_INT:
           case V_ALL:
                break;
           case V_COLUMN:
                free_column_node(function_value_node->column);
                break;
           default:
                UNEXPECTED_VALUE(function_value_node->value_type);
                break;
        }
        db_free(function_value_node);
    }
}

/* Free function node. */
void free_function_node(FunctionNode *function_node) {
    if (function_node) {
        free_function_value_node(function_node->value);
        db_free(function_node);
    } 
}

/* Free ColumnDefOptNode. */
void free_column_def_opt_node(ColumnDefOptNode *column_def_opt) {
    if (column_def_opt) {
        free_value_item_node(column_def_opt->value);
        free_condition_node(column_def_opt->condition);
        if (column_def_opt->refer_table)
            db_free(column_def_opt->refer_table);
        if (column_def_opt->comment)
            db_free(column_def_opt->comment);
        db_free(column_def_opt);
    }
}

/* Free column def node. */
void free_column_def_node(ColumnDefNode *column_def_node) {
    if (column_def_node) {
        free_column_def_name(column_def_node->column);
        free_data_type_node(column_def_node->data_type);
        free_list_deep(column_def_node->column_def_opt_list);
        db_free(column_def_node);
    }
}


/* Free QuerySpecNode. */
void free_query_spec_node(QuerySpecNode *query_spec_node) {
    if (query_spec_node) {
        free_selection_node(query_spec_node->selection);
        free_table_exp_node(query_spec_node->table_exp);  
        db_free(query_spec_node);
    }
}

/* Free ValuesOrQuerySpecNode. */
void free_values_or_query_spec_node(ValuesOrQuerySpecNode *value_or_query_spec_node) {
    if (value_or_query_spec_node) {
        switch (value_or_query_spec_node->type) {
            case VQ_VALUES:
                free_list_deep(value_or_query_spec_node->values);
                break;
            case VQ_QUERY_SPEC:
                free_query_spec_node(value_or_query_spec_node->query_spec);
                break;
            default:
                UNEXPECTED_VALUE(value_or_query_spec_node->type);
                break;
        }
        db_free(value_or_query_spec_node);
    }
}

/* Free primary key node. */
void free_primary_key_node(PrimaryKeyNode *primary_key_node) {
    if (primary_key_node != NULL) {
        free_column_node(primary_key_node->column);
        db_free(primary_key_node);
    }
}

/* Free select items node. */
void free_select_items_node(SelectItemsNode *select_items_node) {
    if (select_items_node) {
        switch(select_items_node->type) {
            case SELECT_FUNCTION:
                free_function_node(select_items_node->function_node);
                break;
            case SELECT_COLUMNS:
                free_list_deep(select_items_node->column_list);
                break;
            case SELECT_ALL:
                break;
            default:
                UNEXPECTED_VALUE(select_items_node->type);
                break;
        }
        db_free(select_items_node);
    }
}

/* Free assignment node. */
void free_assignment_node(AssignmentNode *assignment_node) {
    if (assignment_node) {
        free_column_node(assignment_node->column);
        free_value_item_node(assignment_node->value);
        db_free(assignment_node);
    }
}

/* Free ComparisonNode. */
void free_comparison_node(ComparisonNode *comparison_node) {
    if (comparison_node) {
        free_column_node(comparison_node->column);
        free_scalar_exp_node(comparison_node->value);
        db_free(comparison_node);
    }
}

/* Free InNode. */
void free_in_node(InNode *in_node) {
    if (in_node) {
        free_column_node(in_node->column);
        free_list_deep(in_node->value_list);
    }
}

/* Free LikeNode. */
void free_like_node(LikeNode *like_node) {
    if (like_node) {
        free_column_node(like_node->column);
        free_value_item_node(like_node->value);
    }
}


/* Free PredicateNode. */
void free_predicate_node(PredicateNode *predicate_node) {
    if (predicate_node) {
        switch (predicate_node->type) {
            case PRE_COMPARISON:
                free_comparison_node(predicate_node->comparison);
                break;
            case PRE_IN:
                free_in_node(predicate_node->in);
                break;
            case PRE_LIKE:
                free_like_node(predicate_node->like);
                break;
            default:
                UNEXPECTED_VALUE(predicate_node->type);
                break;
        }
        db_free(predicate_node);
    }
}

/* Free condition node. */
void free_condition_node(ConditionNode *condition_node) {
    if (condition_node) {
        switch(condition_node->conn_type) {
            case C_OR:
            case C_AND:
                free_condition_node(condition_node->left);
                free_condition_node(condition_node->right);
                break;
            case C_NONE:
                free_predicate_node(condition_node->predicate);
                break;
            default:
                UNEXPECTED_VALUE(condition_node->conn_type);
                break;
        }
        db_free(condition_node);
    }
}

/* Free LimitNode. */
void free_limit_node(LimitNode *limit_node) {
    if (limit_node) {
        db_free(limit_node);
    }
}

/* Free ReferValue. */
void free_refer_value(ReferValue *refer_value) {
    if (refer_value) {
        switch (refer_value->type) {
            case DIRECTLY:
                free_list_deep(refer_value->nest_value_list);
                break;
            case INDIRECTLY:
                free_condition_node(refer_value->condition);
                break;
        }
    }
}

/* Free ArrayValue. */
void free_array_value(ArrayValue *array_value) {
    if (array_value) {
        if (array_value->list) {
            free_list_deep(array_value->list);
        }
        db_free(array_value);
    }
}

/* Free ScalarExpNode. */
void free_scalar_exp_node(ScalarExpNode *scalar_exp_node) {
    if (scalar_exp_node) {
        switch (scalar_exp_node->type) {
            case SCALAR_COLUMN:
                free_column_node(scalar_exp_node->column);
                break;
            case SCALAR_FUNCTION:
                free_function_node(scalar_exp_node->function);
                break;
            case SCALAR_CALCULATE:
                free_scalar_exp_node(scalar_exp_node->calculate->left);
                free_scalar_exp_node(scalar_exp_node->calculate->right);
                break;
            case SCALAR_VALUE:
                free_value_item_node(scalar_exp_node->value);
                break;
        }
        free_value(scalar_exp_node->alias, T_STRING);
        db_free(scalar_exp_node);
    }
}

/* Free ColumnDefName. */
void free_column_def_name(ColumnDefName *column_def_name) {
    if (column_def_name) {
        if (column_def_name->column)
            db_free(column_def_name->column);
        db_free(column_def_name);
    }
}

/* Free TableContraintDefNode. */
void free_table_contraint_def_node(TableContraintDefNode *table_contraint) {
    if (table_contraint) {
        if (table_contraint->table)
            db_free(table_contraint->table);
        free_condition_node(table_contraint->condition);
        free_list_deep(table_contraint->column_commalist);
        db_free(table_contraint);
    }
}

/* Free BaseTableElementNode */
void free_base_table_element_node(BaseTableElementNode *base_table_element) {
    if (base_table_element) {
        switch (base_table_element->type) {
            case TELE_COLUMN_DEF:
                free_column_def_node(base_table_element->column_def);
                break;
            case TELE_TABLE_CONTRAINT_DEF:
                free_table_contraint_def_node(base_table_element->table_contraint_def);
                break;
            default:
                db_log(ERROR, "Unknown base type element type.");
                break;
        }
        db_free(base_table_element);
    }
}

/* Free TableRefNode. */
void free_table_ref_node(TableRefNode *table_ref_node) {
    if (table_ref_node) {
        if (table_ref_node->table) 
            db_free(table_ref_node->table);
        if (table_ref_node->range_variable)
            db_free(table_ref_node->range_variable);
        db_free(table_ref_node);
    }
}

/* Free AddColumnDef. */
void free_add_column_def(AddColumnDef *add_column_def) {
    if (add_column_def) {
        free_column_def_node(add_column_def->column_def);
    }
}

/* Free DropColumnDef. */
void free_drop_column_def(DropColumnDef *drop_column_def) {
    if (drop_column_def) {
        if (drop_column_def->column_name)
            db_free(drop_column_def->column_name);
    }
}

/* Free ChangeColumnDef. */
void free_change_column_def(ChangeColumnDef *change_column_def) {
    if (change_column_def) {
        if (change_column_def->old_column_name)
            db_free(change_column_def->old_column_name);
        free_column_def_node(change_column_def->new_column_def);
    }
}

/* Free AlterTableAction. */
void free_alter_table_action(AlterTableAction *action) {
    if (action) {
        switch (action->type) {
            case ALTER_TO_ADD_COLUMN:
                free_add_column_def(action->action.add_column);
                break;
            case ALTER_TO_DROP_COLUMN:
                free_drop_column_def(action->action.drop_column);
                break;
            case ALTER_TO_CHANGE_COLUMN:
                free_change_column_def(action->action.change_column);
                break;
        }
    }
}

/* Free FromClauseNode. */
void free_from_clause_node(FromClauseNode *from_clause_node) {
    if (from_clause_node) {
        free_list_deep(from_clause_node->from);
        db_free(from_clause_node);
    }
}

/* Free WhereClauseNode. */
void free_where_clause_node(WhereClauseNode *where_clause_node) {
    if (where_clause_node) {
        free_condition_node(where_clause_node->condition);
        db_free(where_clause_node);
    }
}

/* Free TableExpNode. */
void free_table_exp_node(TableExpNode *table_exp_node) {
    if (table_exp_node) {
        free_from_clause_node(table_exp_node->from_clause);
        free_where_clause_node(table_exp_node->where_clause);
        db_free(table_exp_node);
    }
}

/* Free SelectionNode. */
void free_selection_node(SelectionNode *selection_node) {
    if (selection_node) {
        if (!selection_node->all_column)
            free_list_deep(selection_node->scalar_exp_list);
        db_free(selection_node);
    }
}


/* Free SelectNode. */
void free_select_node(SelectNode *select_node) {
    if (select_node) {
        free_selection_node(select_node->selection);
        free_table_exp_node(select_node->table_exp);
        db_free(select_node);
    }
}

/* Free InsertNode. */
void free_insert_node(InsertNode *insert_node) {
    if (insert_node != NULL) {
        if (insert_node->table_name)
            db_free(insert_node->table_name);
        if (!insert_node->all_column)
            free_list_deep(insert_node->column_list);
        free_values_or_query_spec_node(insert_node->values_or_query_spec);
        db_free(insert_node);
    }
}

/* Free UpdateNode. */
void free_update_node(UpdateNode *update_node) {
    if (update_node) {
        if (update_node->table_name)
            db_free(update_node->table_name);
        free_list_deep(update_node->assignment_list);
        free_where_clause_node(update_node->where_clause);
        db_free(update_node);
    } 
}

/* Free delete node. */
void free_delete_node(DeleteNode *delete_node) {
    if (delete_node) {
        if (delete_node->table_name)
            db_free(delete_node->table_name);
        free_condition_node(delete_node->condition_node);
        db_free(delete_node);
    } 
}

/* Free create table node. */
void free_create_table_node(CreateTableNode *create_table_node) {
    if (create_table_node != NULL) {
        if (create_table_node->table_name)
            db_free(create_table_node->table_name);
        free_list_deep(create_table_node->base_table_element_commalist);
        db_free(create_table_node);
    }
}

/* Free DropTableNode. */
void free_drop_table_node(DropTableNode *drop_table_node) {
    if (drop_table_node) {
        if (drop_table_node->table_name)
            db_free(drop_table_node->table_name);
        db_free(drop_table_node);
    }
}

/* Free DescribeNode. */
void free_describe_node(DescribeNode *describe_node) {
    if (describe_node) {
        if (describe_node->table_name)
            db_free(describe_node->table_name);
        db_free(describe_node);
    }
}

/* Free show tables node. */
void free_show_tables_node(ShowNode *show_node) {
    if (show_node)
        db_free(show_node);
}

/* Free AlterTableNode. */
void free_alter_table_node(AlterTableNode *alter_table_node) {
    if (alter_table_node) {
        if (alter_table_node->table_name)
            db_free(alter_table_node->table_name);
        free_alter_table_action(alter_table_node->action);
    }
}

/* Free ASTNode. */
void free_statement(Statement *statement) {
    switch (statement->statement_type) {
        case BEGIN_TRANSACTION_STMT:
        case COMMIT_TRANSACTION_STMT:
        case ROLLBACK_TRANSACTION_STMT:
            break;
        case SELECT_STMT:
            free_select_node(statement->select_node);
            break;
        case INSERT_STMT:
            free_insert_node(statement->insert_node);
            break;
        case UPDATE_STMT:
            free_update_node(statement->update_node);
            break;
        case DELETE_STMT:
            free_delete_node(statement->delete_node);
            break;
        case CREATE_TABLE_STMT:
            free_create_table_node(statement->create_table_node);
            break;
        case DROP_TABLE_STMT:
            free_drop_table_node(statement->drop_table_node);
            break;
        case DESCRIBE_STMT:
            free_describe_node(statement->describe_node);
            break;
        case SHOW_STMT:
            free_show_tables_node(statement->show_node);
            break;
        case ALTER_TABLE_STMT:
            free_alter_table_node(statement->alter_table_node);
            break;
        default:
            UNEXPECTED_VALUE(statement->statement_type);
            break;
    }
    db_free(statement);
}

/* Free LockHandle. */
void free_lock_handle(LockHandle *lock_handle) {
    if (lock_handle) {
        free_refer(lock_handle->refer);
        free_lock_handle(lock_handle->next);
        db_free(lock_handle);
    }
}

/* Free TransactionHandle. */
void free_transaction_handle(TransactionHandle *trans_handle) {
    if (trans_handle) {
        free_transaction_handle(trans_handle->next);
        db_free(trans_handle);
    }
}

/* Free DBResult. */
void free_db_result(DBResult *result) {
    if (result) {
        if (result->table)
            db_free(result->table);
        if (result->message)
            db_free(result->message);
        switch(result->stmt_type) {
            case SELECT_STMT:
                free_select_result(result->data);
                break;
            case SHOW_STMT:
            case DESCRIBE_STMT:
                free_list_deep(result->data);
                break;
            default:
                break;
        }
        db_free(result);
    }
}

/* Free LogEntry.*/
void free_log_entry(LogEntry *log_entry) {
    if (log_entry) {
        if (log_entry->message)
            db_free(log_entry->message);
        db_free(log_entry);
    }
}

/* Free XLogEntry. */
void free_xlog_entry(XLogEntry *xlog_entry) {
    if (xlog_entry) {
        free_refer(xlog_entry->refer);
        free_xlog_entry(xlog_entry->next);
        db_free(xlog_entry);
    }
}
