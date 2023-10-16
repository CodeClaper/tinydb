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

//Free int value node.
void free_int_value_node(IntValueNode *int_value_node) {
    if (int_value_node)
        free(int_value_node);
}

//Free bool value node.
void free_bool_value_node(BoolValueNode *bool_value_node) {
    if (bool_value_node)
        free(bool_value_node);
}

//Free string value node.
void free_string_value_node(StringValueNode *string_value_node) {
    if (string_value_node) {
        if (string_value_node->s_value)
            free(string_value_node->s_value);
        free(string_value_node);
    }
}

//Free ident node.
void free_ident_node(IdentNode *ident_node) {
    if (ident_node) {
        if(ident_node->name)
            free(ident_node->name);
        free(ident_node);
    }
}


//Free value item node.
void free_value_item_node(ValueItemNode *value_item_node) {
    if (value_item_node) {
        switch(value_item_node->data_type) {
            case T_INT:
                free_int_value_node(value_item_node->i_value);
                break;
            case T_STRING:
                free_string_value_node(value_item_node->s_value);
                break;
            case T_BOOL:
                free_bool_value_node(value_item_node->b_value);
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
                free_int_value_node(function_value_node->i_value);
                break;
           case V_IDENT:
                free_ident_node(function_value_node->id_value);
                break;
           case V_ALL:
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

//Free Opr Node.
void free_opr_node(OprNode *opr_node) {
    if (opr_node)
        free(opr_node);
}

//Free conn node.
void free_conn_node(ConnNode *conn_node) {
    if (conn_node)
        free(conn_node);
}


//Free data type node
void free_data_type_node(DataTypeNode *data_type_node) {
    if (data_type_node != NULL)
        free(data_type_node);
}

//Free column def node
void free_column_def_node(ColumnDefNode *column_def_node) {
    if (column_def_node != NULL) {
        free_ident_node(column_def_node->column_name);
        free_data_type_node(column_def_node->column_type);
        free(column_def_node);
    }
}

//Free column def set node.
void free_column_def_set_node(ColumnDefSetNode *column_def_set_node) {
    if (column_def_set_node != NULL) {
        for(uint32_t i = 0; i < column_def_set_node->column_size; i++) {
            free_column_def_node(*(column_def_set_node->column_def + i));
        }
        free(column_def_set_node->column_def);
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


//Free ident set node.
void free_ident_set_node(IdentSetNode *ident_set_node) {
    if (ident_set_node) {
        for(uint32_t i = 0; i < ident_set_node->num; i++) {
            free_ident_node(*(ident_set_node->ident_node + i));
        }
        free(ident_set_node->ident_node);
        free(ident_set_node);
    }
}


//Free primary key node.
void free_primary_key_node(PrimaryKeyNode *primary_key_node) {
    if (primary_key_node != NULL) {
        free_ident_node(primary_key_node->primary_key_column);
        free(primary_key_node);
    }
}

//Free column set node.
void free_column_set_node(ColumnSetNode *column_set_node) {
    if (column_set_node != NULL) {
        free_ident_set_node(column_set_node->ident_set_node);
        free(column_set_node);
    }
}

//Free select items node.
void free_select_items_node(SelectItemsNode *select_items_node) {
    if (select_items_node) {
        if (select_items_node->is_function_node)
            free_function_node(select_items_node->function_node);
        else
            free_ident_set_node(select_items_node->ident_set_node);
        free(select_items_node);
    }
}

//Free from item node.
void free_from_item_node(FromItemNode *from_item_node) {
    if (from_item_node) {
        free_ident_node(from_item_node->table);
        free(from_item_node);
    }
}

//Free select node.
void free_select_node(SelectNode *select_node) {
    if (select_node) {
        free_select_items_node(select_node->select_items_node);
        free_from_item_node(select_node->from_item_node);
        free_condition_node(select_node->condition_node);
        free(select_node);
    }
}

//Free insert node.
void free_insert_node(InsertNode *insert_node) {
    if (insert_node != NULL) {
        free_from_item_node(insert_node->from_item_node);
        if (!insert_node->if_ignore_columns)
            free_column_set_node(insert_node->columns_set_node);
        free_value_item_set_node(insert_node->value_item_set_node);
        free(insert_node);
    }
}

//Free create table node.
void free_create_table_node(CreateTableNode *create_table_node) {
    if (create_table_node != NULL) {
        free_ident_node(create_table_node->table_name);
        free_column_def_set_node(create_table_node->column_def_set_node);
        free_primary_key_node(create_table_node->primary_key_node);
        free(create_table_node);
    }
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
            break;
    }
    free(node);
}

//Free condition node.
void free_condition_node(ConditionNode *condition_node) {
    if (condition_node) {
        switch(condition_node->type) {
            case LOGIC_CONDITION:
                free_conn_node(condition_node->conn_node);
                break;
            case EXEC_CONDITION:
                free_ident_node(condition_node->column);
                free_opr_node(condition_node->opr_node);
                free_value_item_node(condition_node->compare);
                free_conn_node(condition_node->conn_node);
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
        for (uint32_t i = 0; i < query_param->column_size; i++) {
            free_meta_column(*(query_param->meta_columns + i));
        }
        free(query_param->meta_columns);
        free_condition_node(query_param->condition_node);
        free_function_node(query_param->function_node);
        free(query_param);
    }
}

