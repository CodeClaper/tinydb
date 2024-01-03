#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>
#include "check.h"
#include "asserts.h"
#include "data.h"
#include "table.h"
#include "log.h"
#include "opr.h"
#include "node.h"
#include "pager.h"
#include "meta.h"
#include "index.h"
#include "misc.h"
#include "select.h"
#include "ret.h"

/* Check ident node. */
static bool check_column_node(MetaTable *meta_table, ColumnNode *column_node, DBResult *result) {
    int i;
    for (i = 0; i < meta_table->column_size; i++) {
        MetaColumn *meta_column = meta_table->meta_column[i];
        if (strcmp(meta_column->column_name, column_node->column_name) == 0)
            return true;
    }
    error_result(result, EXECUTE_UNKNOWN_COLUMN, "Unknown column '%s' in table '%s'", column_node->column_name, meta_table->table_name);
    return false;
}

/* Check if type convert pass. */
static bool if_convert_type(DataType source, DataType target, char *column_name, DBResult *result) {
    bool re;
    switch(source) {
        case T_BOOL:
            re = target == T_BOOL;
            break;
        case T_INT:
            re = target == T_INT;
            break;
        case T_LONG:
            re = target == T_INT || target == T_LONG;
            break;
        case T_FLOAT:
            re = target == T_INT || target == T_FLOAT;
            break;
        case T_DOUBLE:
            re = target == T_INT || target == T_DOUBLE;
            break;
        case T_CHAR:
            re = target == T_CHAR || target == T_STRING;
            break;
        case T_STRING:
            re = target == T_CHAR || target == T_STRING;
            break;
        case T_TIMESTAMP:
            re = target == T_TIMESTAMP || target == T_STRING;
            break;
        case T_DATE:
            re = target == T_DATE || target == T_STRING;
            break;
        case T_REFERENCE:
            re = target == T_REFERENCE;
            break;
    }
    if (!re)
       error_result(result, EXECUTE_CONVERT_DATA_TYPE_FAIL, "Data type convert fail for column '%s'.", column_name);
    return re;
}

/* Check value if valid. 
 * Because, CHAR, DATE, TIMESTAMP use '%s' format to pass value, thus check it.
 * */
static bool check_value_valid(MetaColumn *meta_column, void* value, DBResult *result) {
    if (value == NULL) {
        error_result(result, EXECUTE_CONVERT_DATA_TYPE_FAIL, "Try to convert NULL '%s' to %s fail.", data_type_name(meta_column->column_type));
        return false;
    }
    switch(meta_column->column_type) {
        case T_BOOL:
        case T_INT:
        case T_LONG:
        case T_FLOAT:
        case T_DOUBLE:
        case T_REFERENCE:
            return true;
        case T_CHAR: {
            /* For CHAR type, only allow one character. */
            size_t len = strlen((char *) value);
            if (len != 1)
                db_error("Try to convert value '%s' to CHAR type fail\n", (char *) value);
            return len == 1;
        }
        case T_STRING: {
            size_t size = strlen(value);
            if (size > meta_column->column_length)
                db_error("Exceed the limit of data length: %d > %d, for column '%s'\n", size, meta_column->column_length, meta_column->column_name);
            return size <= meta_column->column_length;
        }
        case T_TIMESTAMP: {   
            /* when data type is TIMESTAMP, user`s input is a STIRNG type. */
            regex_t reegex;
            int comp_result, exe_result;

            /* https://www.regular-expressions.info/gnu.html, and notice there`s not \\b. */
            comp_result = regcomp(&reegex, "^([0-9]{4})-(0[1-9]|1[0-2])-(0[1-9]|[12][0-9]|3[01])\\s(0[0-9]|1[0-9]|2[0-3]):([0-5][0-9]):([0-5][0-9])$", REG_EXTENDED);
            assert_true(comp_result == 0, "Regex compile fail.\n");
            exe_result = regexec(&reegex, (char *)value, 0, NULL, 0);
            regfree(&reegex);
            if (exe_result == REG_NOMATCH) 
                db_error("Try to convert value '%s' to timestamp fail\n", (char *) value);
            return exe_result == REG_NOERROR;
        }
        case T_DATE: {
            /* When data type is DATE, user`s input is a STRING type. */
            regex_t reegex;
            int comp_result, exe_result;

            /* Jump https://www.regular-expressions.info/gnu.html, and notice there`s not \\b. */
            comp_result = regcomp(&reegex, "^([0-9]{4})-(0[1-9]|1[0-2])-(0[1-9]|[12][0-9]|3[01])$", REG_EXTENDED);
            assert_true(comp_result == 0, "Regex compile fail.\n");
            exe_result = regexec(&reegex, (char *)value, 0, NULL, 0);
            regfree(&reegex);
            if (exe_result == REG_NOMATCH) 
                db_error("Try to convert value '%s' to timestamp fail\n", (char *) value);
            return exe_result == REG_NOERROR;
        }
        default:
            fatal("Not implement yet.");
    }

}

/* Check ident node. */
static bool check_value_item_node(MetaTable *meta_table, char *column_name ,ValueItemNode *value_item_node, DBResult *result) {
    for (uint32_t i = 0; i < meta_table->column_size; i++) {
        MetaColumn *meta_column = meta_table->meta_column[i];
        if (strcmp(meta_column->column_name, column_name) == 0 && if_convert_type(meta_column->column_type, value_item_node->data_type, column_name, result)) 
            return true;
    }
    error_result(result, EXECUTE_CONVERT_DATA_TYPE_FAIL, "Column '%s' data type error.", column_name);
    return false;
}

/* Check function node */
static bool check_function_node(FunctionNode *function_node, MetaTable *meta_table, DBResult *result) {
    FunctionValueNode *value_node = function_node->value;
    switch(value_node->value_type) {
        case V_INT:
        case V_ALL:
            return true;
        case V_COLUMN: {
            ColumnNode *column = value_node->column;
            return check_column_node(meta_table, column, result); 
        }
    }
}

/* Check column set node */
static bool check_column_set_node(ColumnSetNode *column_set_node, MetaTable *meta_table, DBResult *result) {
    int i;
    for (i = 0; i < column_set_node->size; i++) {
        ColumnNode *column_node = *(column_set_node->columns + i);
        if (!check_column_node(meta_table, column_node, result))
            return false;
    }
    return true;
}

/* Check select items if exist int meta column */
static bool check_select_items(SelectItemsNode *select_items_node, MetaTable *meta_table, DBResult *result) {
    switch(select_items_node->type) {
        case SELECT_ALL:
            return true;
        case SELECT_COLUMNS:
            return check_column_set_node(select_items_node->column_set_node, meta_table, result);
        case SELECT_FUNCTION:
            return check_function_node(select_items_node->function_node, meta_table, result);
    }
}

/* Check condition node. */
static bool check_condition_node(ConditionNode *condition_node, MetaTable *meta_table, DBResult *result) {
    if (condition_node == NULL)
        return true;
    switch(condition_node->type) {
        case LOGIC_CONDITION:
            return check_condition_node(condition_node->left, meta_table, result) && check_condition_node(condition_node->right, meta_table, result);
        case EXEC_CONDITION: {
            MetaColumn *meta_column = get_meta_column_by_name(meta_table, condition_node->column->column_name);
            return check_column_node(meta_table, condition_node->column, result) // check select column
                   && if_convert_type(meta_column->column_type, condition_node->value->data_type, meta_column->column_name, result) // check column type
                   && check_value_valid(meta_column, get_value_from_value_item_node(condition_node->value, meta_column->column_type), result); // check if value valid
        }
    }
}

/* check column set. */
static bool check_column_set(ColumnSetNode *column_set_node, MetaTable *meta_table, DBResult *result) {
    for (uint32_t i = 0; i < column_set_node->size; i++) {
        ColumnNode *column_node = *(column_set_node->columns + i);
        if (!check_column_node(meta_table, column_node, result))
            return false;
    } 
    return true;
}

/* Check query param. */
bool check_query_param(QueryParam *query_param, DBResult *result) {
    Table *table = open_table(query_param->table_name);
    if (table == NULL) {
        error_result(result, EXECUTE_TABLE_DROP_FAIL, "Table '%s' not exists.", query_param->table_name);
        return false;
    }
    return check_select_items(query_param->select_items, table->meta_table, result) 
             && check_condition_node(query_param->condition_node, table->meta_table, result);
}

/* Check assignment set node */
static bool check_assignment_set_node(AssignmentSetNode *assignment_set_node, Table *table, SelectResult *select_result, DBResult *result) { 
    for (uint32_t i = 0; i < assignment_set_node->num; i++) {
        AssignmentNode *assignment_node = *(assignment_set_node->assignment_node + i);
        ColumnNode *column_node = assignment_node->column;
        ValueItemNode *value_node = assignment_node->value;
        assert_not_null(column_node, "System error, there is no column node in assignment set node.\n");
        MetaColumn *meta_column = get_meta_column_by_name(table->meta_table, column_node->column_name);

        /* Check column, check type, check if value valid. */
        if (!check_column_node(table->meta_table, column_node, result) 
            || !if_convert_type(meta_column->column_type, value_node->data_type, meta_column->column_name, result) 
            || !check_value_valid(meta_column, get_value_from_value_item_node(value_node, meta_column->column_type), result))
            return false;

        /* It means to change the primary key column and may cause duplicate key. */
        if (meta_column->is_primary) {

            /* It means to change the primary key column and may cause duplicate key. 
             * Firstly, multirows absulutely case duplicate.
             * Secondly, if priamry key is assigned to the old value, there is no influnece.
             * Thirdly, if priamry key is assigned to different value, should check if key aleady exists, avoid cause duplicate.
             * */
            if (select_result->row_size > 1) {
                error_result(result, EXECUTE_DUPLICATE_KEY, "Duaplicate key not allowed.");
                return false;
            }
            if (select_result->row_size == 1) {
                void *new_key = get_value_from_value_item_node(value_node, meta_column->column_type);
                Cursor *cursor = define_cursor(table, new_key);
                uint32_t value_len = calc_table_row_length(table);
                uint32_t key_len = calc_primary_key_length(table);
                void *leaf_node = get_page(cursor->table->pager, cursor->page_num);
                void *key = get_leaf_node_cell_key(leaf_node, cursor->cell_num, key_len, value_len);
                if (equal(key, new_key, meta_column->column_type) && !cursor_is_deleted(cursor)) {
                    error_result(result, EXECUTE_DUPLICATE_KEY, "key '%s' already exists, not allow duplicate key.", get_key_str(key, meta_column->column_type));
                    return false;
                }
            }
        }
    }
    return true;
}

/* Check if table alreay exist. */
static bool check_duplicate_table(char *table_name, DBResult *result) {
    if (check_table_exist(table_name)) {
        error_result(result, EXECUTE_TABLE_CREATE_FAIL, "Table '%s' already exists.", table_name); 
        return false;
    } else 
        return true;
}

/* Check if support priamay key. 
 * Maybe it will allow to not support primary key, but now, must to do.  */
static bool check_primary_null(CreateTableNode *create_table_node, DBResult *result) {

    /* check primary key node. */
    if (create_table_node->primary_key_node)
        return true;

    /* check column def define primary. */
    int i;
    for(i = 0; i < create_table_node->column_def_set_node->size; i++) {
        if (create_table_node->column_def_set_node->column_defs[i]->is_primary)
            return true;
    }
    error_result(result, EXECUTE_FAIL, "Must support primary key.");
    return false;
}

/* Check if exists duplicate column name. */
static bool check_duplicate_column_name(ColumnDefSetNode *column_def_set_node, DBResult *result) {
    int i, j;
    for(i = 0; i < column_def_set_node->size; i++) {
        ColumnDefNode *column_def_node1 = column_def_set_node->column_defs[i];
        for(j = 0; j < column_def_set_node->size; j++) {
            ColumnDefNode *column_def_node2 = column_def_set_node->column_defs[j];
            if (i !=j && strcmp(column_def_node1->column->column_name, column_def_node2->column->column_name) == 0) {
                error_result(result, EXECUTE_DUPLICATE_COLUMN, "Not allow duplicate column name '%s' in the same table.", column_def_node1->column->column_name);
                return false;
            }
        }
    }
    return true;
}

/* Check insert node. */
bool check_insert_node(InsertNode *insert_node, DBResult *result) {

    /* Check table exist.*/
    Table *table = open_table(insert_node->table_name);
    if (table == NULL)
        return false;

    MetaTable *meta_table = table->meta_table;
    
    /* According to all column flag, determine the number of column set. */
    if (insert_node->all_column) {
        
        /* Check column number equals the insert values number. */
        if (meta_table->column_size != insert_node->value_item_set_node->num) {
            error_result(result, EXECUTE_NOT_MATCH_COLUMN, "Column count doesn't match value count: %d != %d.", meta_table->column_size, insert_node->value_item_set_node->num);
            return false;
        }

        for (uint32_t i = 0; i < meta_table->column_size; i++) {
            MetaColumn *meta_column = meta_table->meta_column[i];
            ValueItemNode *value_item_node = *(insert_node->value_item_set_node->value_item_node + i);
            /* Check data type. */
            if (!if_convert_type(meta_column->column_type, value_item_node->data_type, meta_column->column_name, result))  
                return false;
            /* Checke value valid. */
            if (!check_value_valid(meta_column, get_value_from_value_item_node(value_item_node, meta_column->column_type), result))
                return false;
        }
    } else {

        /* Check column number equals the insert values number. */
        if (insert_node->columns_set_node->size  != insert_node->value_item_set_node->num) {
            db_error("Column count doesn't match value count\n");
            return false;
        }

        for (uint32_t i = 0; i < insert_node->columns_set_node->size; i++) {
            ColumnNode *column_node = *(insert_node->columns_set_node->columns + i);
            ValueItemNode *value_item_node = *(insert_node->value_item_set_node->value_item_node + i);
            MetaColumn *meta_column = get_meta_column_by_name(meta_table, column_node->column_name);
            /* Check data type. */
            if (!if_convert_type(meta_column->column_type, value_item_node->data_type, meta_column->column_name, result)) 
                return false;
            /* Check value valid. */
            if (!check_value_valid(meta_column, get_value_from_value_item_node(value_item_node, meta_column->column_type), result)) 
                return false;
        }
    }
    return true;
}

/* Check for update node. */
bool check_update_node(UpdateNode *update_node, SelectResult *select_result, DBResult *result) {
    Table *table = open_table(update_node->table_name);
    return table != NULL 
           && check_assignment_set_node(update_node->assignment_set_node, table, select_result, result) 
           && check_condition_node(update_node->condition_node, table->meta_table, result);
}

/* Check for delete node. */
bool check_delete_node(DeleteNode *delete_node, DBResult *result) {
    Table *table = open_table(delete_node->table_name);
    return check_condition_node(delete_node->condition_node, table->meta_table, result);
}

/* Check for create table node. */
bool check_create_table_node(CreateTableNode *create_table_node, DBResult *result) {
    return check_duplicate_table(create_table_node->table_name, result)
           && check_duplicate_column_name(create_table_node->column_def_set_node, result)
           && check_primary_null(create_table_node, result);
}
