#include "free.h"
#include "misc.h"
#include <stdint.h>
#include <stdlib.h>

//Copy value
void free_value(void *value, DataType data_type) {
    if (value) {
        switch(data_type) {
            case T_STRING:
                free(value);
                break;
            default:
                break;
        }    
    }
}

//Free KeyValue
void free_key_value(KeyValue *key_value) {
    if (key_value) {
        if (key_value->key)
            free(key_value->key);
        free_value(key_value->value, key_value->data_type);
        free(key_value);
    } 
}

//Free Row.
void free_row(Row *row) {
    if (row) {
        if (row->table_name)
            free(row->table_name);
        for(uint32_t i = 0; i < row->column_len; i++) {
            free_key_value(*(row->data + i));
        }
        free(row->data);
        free(row);
    }
}

//Free SelectResult.
void free_select_result(SelectResult *select_result) {
    if (select_result) {
        if (select_result->table_name != NULL)
            free(select_result->table_name);
        for(uint32_t i = 0; i < select_result->row_size; i++) {
            Row *row = *(select_result->row + i);
            free_row(row);
        }
        free(select_result->row);
        free(select_result);
    }
}

//Free input buffer.
void free_input_buffer(InputBuffer *input_buffer) {
    if (input_buffer != NULL) {
        if (input_buffer->input != NULL)
            free(input_buffer->input);
        free(input_buffer);
    }
}

//Free meta column.
void free_meta_column(MetaColumn *meta_column) {
    if (meta_column) {
        free(meta_column);
    }
}

//Free meta table.
void free_meta_table(MetaTable *meta_table) {
    if (meta_table) {
        if (meta_table->table_name) {
            free(meta_table->table_name);
        }
    }
}

//Free column
void free_column_node(ColumnNode *column_node) {
    if (column_node) {
        if (column_node->exist_table_name) {
            if (column_node->table_name)
                free(column_node->table_name);
        }
        if (column_node->column_name)
            free(column_node->column_name);
        free(column_node);
    }

}

//Free column set node.
void free_column_set_node(ColumnSetNode *column_set_node) {
    if (column_set_node) {
        for (uint32_t i = 0; i < column_set_node->size; i++) {
            free_column_node(*(column_set_node->columns + i));
        }
        free(column_set_node->columns);
        free(column_set_node);
    }
}

//Free table
void free_table(Table *table) {
     
}

//Free cursor
void free_cursor(Cursor *cursor) {
    if (cursor) {
        // use table for cache, not free.
        free_table(cursor->table);
        free(cursor);
    }
} 

//Free value item node.
void free_value_item_node(ValueItemNode *value_item_node) {
    if (value_item_node) {
        switch(value_item_node->data_type) {
            case T_INT:
            case T_BOOL:
            case T_CHAR:
            case T_FLOAT:
            case T_DOUBLE:
            case T_TIMESTAMP:
                break;
            case T_STRING:
                {
                    if (value_item_node->s_value)
                        free(value_item_node->s_value);
                }
                break;
            default:
                fatal("Not implement yet.");
        }
        free(value_item_node);
    }
}

//Free function value node.
void free_function_value_node(FunctionValueNode *function_value_node) {
    if (function_value_node) {
        switch(function_value_node->value_type) {
           case V_INT:
           case V_ALL:
                break;
           case V_COLUMN:
                free_column_node(function_value_node->column);
                break;
        }
        free(function_value_node);
    }
}

//Free function node.
void free_function_node(FunctionNode *function_node) {
    if (function_node) {
        free_function_value_node(function_node->value);
        free(function_node);
    } 
}

//Free column def node
void free_column_def_node(ColumnDefNode *column_def_node) {
    if (column_def_node) {
        free_column_node(column_def_node->column);
        free(column_def_node);
    }
}

//Free column def set node.
void free_column_def_set_node(ColumnDefSetNode *column_def_set_node) {
    if (column_def_set_node) {
        for(uint32_t i = 0; i < column_def_set_node->size; i++) {
            free_column_def_node(*(column_def_set_node->column_defs + i));
        }
        free(column_def_set_node->column_defs);
        free(column_def_set_node);
    } 
}

//Free value item set node.
void free_value_item_set_node(ValueItemSetNode *value_item_set_node) {
    if (value_item_set_node) {
        for(uint32_t i = 0; i < value_item_set_node->num; i++) {
            free_value_item_node(*(value_item_set_node->value_item_node + i));
        }
        free(value_item_set_node->value_item_node);
        free(value_item_set_node);
    }
}



//Free primary key node.
void free_primary_key_node(PrimaryKeyNode *primary_key_node) {
    if (primary_key_node != NULL) {
        free_column_node(primary_key_node->column);
        free(primary_key_node);
    }
}

//Free select items node.
void free_select_items_node(SelectItemsNode *select_items_node) {
    if (select_items_node) {
        switch(select_items_node->type) {
            case SELECT_FUNCTION:
                free_function_node(select_items_node->function_node);
                break;
            case SELECT_COLUMNS:
                free_column_set_node(select_items_node->column_set_node);
                break;
            case SELECT_ALL:
                break;
        }
        free(select_items_node);
    }
}

//Free select node.
void free_select_node(SelectNode *select_node) {
    if (select_node) {
        free_select_items_node(select_node->select_items_node);
        if (select_node->table_name) 
            free(select_node->table_name);
        free_condition_node(select_node->condition_node);
        free(select_node);
    }
}

//Free insert node.
void free_insert_node(InsertNode *insert_node) {
    if (insert_node != NULL) {
        if (insert_node->table_name)
            free(insert_node->table_name);
        if (!insert_node->all_column)
            free_column_set_node(insert_node->columns_set_node);
        free_value_item_set_node(insert_node->value_item_set_node);
        free(insert_node);
    }
}

//Free create table node.
void free_create_table_node(CreateTableNode *create_table_node) {
    if (create_table_node != NULL) {
        if (create_table_node->table_name)
            free(create_table_node->table_name);
        free_column_def_set_node(create_table_node->column_def_set_node);
        free_primary_key_node(create_table_node->primary_key_node);
        free(create_table_node);
    }
}

//Free show tables node.
void free_show_tables_node(ShowTablesNode *show_table_node) {
    if (show_table_node)
        free(show_table_node);
}

//Free ASTNode.
void free_ast_node(ASTNode *node) {
    switch(node->statement_type) {
        case SELECT_STMT:
            free_select_node(node->select_node);
            break;
        case INSERT_STMT:
            free_insert_node(node->insert_node);
            break;
        case UPDATE_STMT:
        case DELETE_STMT:
            break;
        case CREATE_TABLE_STMT:
            break;
        case DESCRIBE_STMT:
            break;
        case SHOW_TABLES_STMT:
            free_show_tables_node(node->show_tables_node);
            break;
    }
    free(node);
}

//Free condition node.
void free_condition_node(ConditionNode *condition_node) {
    if (condition_node) {
        switch(condition_node->type) {
            case LOGIC_CONDITION:
                break;
            case EXEC_CONDITION:
                free_column_node(condition_node->column);
                free_value_item_node(condition_node->value);
                break;
        }
        free_condition_node(condition_node->left);
        free_condition_node(condition_node->right);
        free_condition_node(condition_node->next);
        free(condition_node);
    }
}


//Free query param.
void free_query_param(QueryParam *query_param) {
    if(query_param) {
        free_select_items_node(query_param->select_items);
        free_condition_node(query_param->condition_node);
        if (query_param->table_name)
            free(query_param->table_name);
        free(query_param);
    }
}

