#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <regex.h>
#include "check.h"
#include "utils.h"
#include "mmu.h"
#include "asserts.h"
#include "compare.h"
#include "data.h"
#include "table.h"
#include "log.h"
#include "free.h"
#include "ltree.h"
#include "trans.h"
#include "pager.h"
#include "meta.h"
#include "index.h"
#include "select.h"
#include "refer.h"

/* Check ValueItemSetNode. */
static bool check_value_item_set_node(MetaTable *meta_table, char *column_name, ValueItemSetNode *value_item_set_node);

/* Check ScalarExpNode. */
static bool check_scalar_exp(ScalarExpNode *scalar_exp, AliasMap alias_map);

/* Get ConditionNode from WhereClauseNode. */
static ConditionNode *get_condition_from_where_clause(WhereClauseNode *where_clause) {
    if (!where_clause)
        return NULL;
    return where_clause->condition;
}

/* Get value from ValueItemNode. 
 * Notice, CHAR, DATE, TIMESTAMP use '%s' format to pass value. */
static void *get_value_from_value_item(ValueItemNode *value_item) {
    switch (value_item->data_type) {
        case T_BOOL:
            return &value_item->value.b_value;
        case T_CHAR:
            return value_item->value.s_value;
        case T_INT:
            return &value_item->value.i_value;
        case T_LONG:
            return &value_item->value.i_value;
        case T_FLOAT:
            return &value_item->value.f_value;
        case T_DOUBLE:
            return &value_item->value.d_value;
        case T_STRING:
            return value_item->value.s_value;
        case T_DATE:
            return value_item->value.s_value;
        case T_TIMESTAMP:
            return value_item->value.s_value;
        case T_REFERENCE:
            return value_item->value.r_value;
        default:
            db_log(ERROR, "Not support data type");
    }
}

/* Check ident node. */
static bool check_column_node(ColumnNode *column_node, MetaTable *meta_table) {
    uint32_t i;
    for (i = 0; i < meta_table->column_size; i++) {
        MetaColumn *meta_column = meta_table->meta_column[i];
        if (streq(meta_column->column_name, column_node->column_name)) {
            if (column_node->has_sub_column == false)
                return true;
            else if (meta_column->column_type == T_REFERENCE && column_node->has_sub_column) {
                Table *table = open_table(meta_column->table_name);
                if (column_node->sub_column)
                    return check_column_node(column_node->sub_column, table->meta_table);
                else if (column_node->scalar_exp_set) {
                    for (uint32_t j = 0; j < column_node->scalar_exp_set->size; j++) {
                        ScalarExpNode *scalar_exp = column_node->scalar_exp_set->data[j];
                        switch (scalar_exp->type) {
                            case SCALAR_COLUMN:{
                                check_column_node(scalar_exp->column, table->meta_table);
                                break;
                            }
                            case SCALAR_FUNCTION:
                                db_log(ERROR, "Not allowed use funtion in nested column. ");
                                break;
                            case SCALAR_CALCULATE:
                            case SCALAR_VALUE:
                                break;
                            default:
                                db_log(PANIC, "Unknown Scalar Express type.");
                        }
                    }
                    return true;
                }
            }
        }
    }
    
    /* Reach here, means column is unknown. */
    if (column_node->range_variable) 
        db_log(ERROR, "Unknown column '%s.%s', ", column_node->range_variable, column_node->column_name);
    else 
        db_log(ERROR, "Unknown column '%s', ", column_node->column_name);

    return false;
}

/* Confirm MetaTable via ColumnNode. */
static MetaTable *confirm_meta_table_via_column(ColumnNode *column, AliasMap alias_map) {

    MetaTable *current_meta_table = NULL;
    int times = 0;

    uint32_t i, j;
    for (i = 0; i < alias_map.size; i++) {
        AliasEntry alias_entry = alias_map.map[i];
        Table *table = open_table(alias_entry.name);
        MetaTable *meta_table = table->meta_table;

        if (column->range_variable && (streq(column->range_variable, alias_entry.name) || streq(column->range_variable, alias_entry.alias))) {
            current_meta_table = meta_table;
        }

        if (column->range_variable == NULL) {
            for (j = 0; j < meta_table->column_size; j++) {
                MetaColumn *meta_column = meta_table->meta_column[j];
                if (streq(meta_column->column_name, column->column_name)) {
                    current_meta_table = meta_table;
                    times++;
                }            
            }
        }
    }

    if (current_meta_table == NULL) {
        if (column->range_variable)
            db_log(ERROR, "Unknown column name '%s.%s'. ", column->range_variable, column->column_name);
        else
            db_log(ERROR, "Unknown column name '%s'. ", column->column_name);

        return current_meta_table;
    }

    if (times > 1) {
        db_log(ERROR, "Column name '%s' is ambiguous.", column->column_name);
        return current_meta_table;
    }

    return current_meta_table;

}

/* Check if type convert pass. */
static bool if_convert_type(DataType source, DataType target, char *column_name, char *table_name) {
    bool flag;
    switch(source) {
        case T_BOOL:
            flag = target == T_BOOL;
            break;
        case T_INT:
            flag = target == T_INT;
            break;
        case T_LONG:
            flag = target == T_INT || target == T_LONG;
            break;
        case T_FLOAT:
            flag = target == T_INT || target == T_FLOAT;
            break;
        case T_DOUBLE:
            flag = target == T_INT || target == T_DOUBLE;
            break;
        case T_CHAR:
            flag = target == T_CHAR || target == T_STRING;
            break;
        case T_STRING:
            flag = target == T_CHAR || target == T_STRING;
            break;
        case T_TIMESTAMP:
            flag = target == T_TIMESTAMP || target == T_STRING;
            break;
        case T_DATE:
            flag = target == T_DATE || target == T_STRING;
            break;
        case T_REFERENCE:
            /* For Reference, it`s complicate, user can pass a refer or subrow column, 
             * to be simple, just make flag true. */
            flag = true;
            break;
    }
    if (!flag)
       db_log(ERROR, "Can`t convert data type [%s] to [%s] for column '%s' in table '%s'", DATA_TYPE_NAMES[target], DATA_TYPE_NAMES[source], column_name, table_name);
    return flag;
}

/* Check value if valid. 
 * Because, CHAR, DATE, TIMESTAMP use '%s' format to pass value, thus check it. */
static bool check_value_valid(MetaColumn *meta_column, ValueItemNode *value_item) {
    void *value = get_value_from_value_item(value_item);
    switch(meta_column->column_type) {
        case T_BOOL:
        case T_INT:
        case T_LONG:
        case T_FLOAT:
        case T_DOUBLE:
        case T_REFERENCE: 
            return true;
        case T_CHAR: {
            if (value == NULL)
                return false;
            /* For CHAR type, only allow one character. */
            size_t len = strlen((char *) value);
            if (len != 1)
                db_log(ERROR, "Try to convert value '%s' to CHAR type fail", (char *) value);
            return len == 1;
        }
        case T_STRING: {
            if (value == NULL)
                return false;
            size_t size = strlen(value);
            if (size > meta_column->column_length)
                db_log(ERROR, "Exceed the limit of data length: %d > %d, for column '%s'. ", size, meta_column->column_length - 1, meta_column->column_name);
            return size <= meta_column->column_length;
        }
        case T_TIMESTAMP: {   
            if (value == NULL)
                return false;
            /* when data type is TIMESTAMP, user`s input is a STIRNG type. */
            regex_t reegex;
            int comp_result, exe_result;

            /* https://www.regular-expressions.info/gnu.html, and notice there`s not \\b. */
            comp_result = regcomp(&reegex, "^([0-9]{4})-(0[1-9]|1[0-2])-(0[1-9]|[12][0-9]|3[01])\\s(0[0-9]|1[0-9]|2[0-3]):([0-5][0-9]):([0-5][0-9])$", REG_EXTENDED);
            assert_true(comp_result == 0, "Regex compile fail.\n");
            exe_result = regexec(&reegex, (char *)value, 0, NULL, 0);
            regfree(&reegex);

            if (exe_result == REG_NOMATCH) 
                db_log(ERROR, "Try to convert value '%s' to timestamp value fail.", (char *) value);

            return exe_result == REG_NOERROR;
        }
        case T_DATE: {
            if (value == NULL)
                return false;
            /* When data type is DATE, user`s input is a STRING type. */
            regex_t reegex;
            int comp_result, exe_result;

            /* Jump https://www.regular-expressions.info/gnu.html, and notice there`s not \\b. */
            comp_result = regcomp(&reegex, "^([0-9]{4})-(0[1-9]|1[0-2])-(0[1-9]|[12][0-9]|3[01])$", REG_EXTENDED);
            assert_true(comp_result == 0, "Regex compile fail.\n");
            exe_result = regexec(&reegex, (char *)value, 0, NULL, 0);
            regfree(&reegex);

            if (exe_result == REG_NOMATCH) 
                db_log(ERROR, "Try to convert value '%s' to date value fail. ", (char *) value);

            return exe_result == REG_NOERROR;
        }
        default:
            db_log(PANIC, "Not implement yet.");
    }

}

/* Check ValueItemNode. */
static bool check_value_item_node(MetaTable *meta_table, char *column_name, ValueItemNode *value_item_node) {
    uint32_t i;
    for (i = 0; i < meta_table->column_size; i++) {
        MetaColumn *meta_column = meta_table->meta_column[i];
        if (strcmp(meta_column->column_name, column_name) == 0 
            && if_convert_type(meta_column->column_type, value_item_node->data_type, column_name, meta_table->table_name)
            && check_value_valid(meta_column, value_item_node))
            return true;
    }
    db_log(ERROR, "Column '%s' data type error.", column_name);
    return false;
}

/* Check ValueItemSetNode. */
static bool check_value_item_set_node(MetaTable *meta_table, char *column_name, ValueItemSetNode *value_item_set_node) {
    uint32_t i;
    for (i = 0; i < value_item_set_node->num; i++) {
        ValueItemNode *value_item_node = value_item_set_node->value_item_node[i];
        if (!check_value_item_node(meta_table, column_name, value_item_node))
            return false;
    }
    return true;
}

/* Check function node */
static bool check_function_node(FunctionNode *function, AliasMap alias_map) {
    FunctionValueNode *value_node = function->value;
    switch(value_node->value_type) {
        case V_INT:
        case V_ALL:
            return true;
        case V_COLUMN: {
            ColumnNode *column = value_node->column;
            MetaTable *meta_table = confirm_meta_table_via_column(column, alias_map);
            return check_column_node(column, meta_table); 
        }
    }
}

/* Check CalculateNode. */
static bool check_calculate_node(CalculateNode *calculate_node, AliasMap alias_map) {
    return check_scalar_exp(calculate_node->left, alias_map) 
        && check_scalar_exp(calculate_node->right, alias_map);
}

/* Check ScalarExpNode if column. */
static bool check_scalar_exp(ScalarExpNode *scalar_exp, AliasMap alias_map) {
    switch (scalar_exp->type) {
        case SCALAR_COLUMN:{
            ColumnNode *column = scalar_exp->column;
            MetaTable *meta_table = confirm_meta_table_via_column(column, alias_map);
            return check_column_node(scalar_exp->column, meta_table);
        }
        case SCALAR_FUNCTION:
            return check_function_node(scalar_exp->function, alias_map);
        case SCALAR_CALCULATE:
            return check_calculate_node(scalar_exp->calculate, alias_map);
        case SCALAR_VALUE:
            return true;
        default:
            db_log(PANIC, "Unknown Scalar Express type.");
    }
}

/* Check ScalarExpSetNode. */
static bool check_scalar_exp_set(ScalarExpSetNode *scalar_exp_set, AliasMap alias_map) {
    uint32_t i;
    for (i = 0; i < scalar_exp_set->size; i++) {
        ScalarExpNode *scalar_exp = scalar_exp_set->data[i];
        if (!check_scalar_exp(scalar_exp, alias_map))
            return false;
    }

    return true;
}

/* Check select items if exist int meta column */
static bool check_selection(SelectionNode *selection_node, AliasMap alias_map) {
    return selection_node->all_column 
           ? true 
           : check_scalar_exp_set(selection_node->scalar_exp_set, alias_map);
}

/* Check opr if allowd. */
static bool check_opr(CompareType compare_type, DataType data_type) {
    switch (compare_type) {
        case O_EQ:
        case O_NE:
            return true;
        case O_GE:
        case O_GT:
        case O_LT:
        case O_LE: {
            if (data_type == T_REFERENCE) {
                db_log(ERROR, "Reference data type only allowed operated equal or not equal.");
                return false;
            }
            return true;
        }
        default:
            db_log(PANIC, "Unknown opration type.");
    }
}

/* Check ComparisonNode value.*/
static bool check_comparison_value(ScalarExpNode *comparion_value, MetaTable *meta_table, MetaColumn *meta_column) {
    switch (comparion_value->type) {
        case SCALAR_VALUE:
            return if_convert_type(meta_column->column_type, comparion_value->value->data_type, meta_column->column_name, meta_table->table_name) // check column type
                   && check_value_valid(meta_column, comparion_value->value); // check if value valid
        case SCALAR_COLUMN:
        case SCALAR_FUNCTION:
        case SCALAR_CALCULATE:
            return true;
    }
}

/* Check ComparisonNode.*/
static bool check_comparison_node(ComparisonNode *comparison, AliasMap alias_map) {
    ColumnNode *column = comparison->column;

    /* Confirm MetaTable. */
    MetaTable *current_meta_table = confirm_meta_table_via_column(column, alias_map);
    MetaColumn *meta_column = get_meta_column_by_name(current_meta_table, column->column_name);

    return check_column_node(comparison->column, current_meta_table) // check select column
           && check_comparison_value(comparison->value, current_meta_table, meta_column)
           && check_opr(comparison->type, meta_column->column_type);
}

/* Check InNode. */
static bool check_in_node(InNode *in_node, AliasMap alias_map) {
    ColumnNode *column = in_node->column;
    /* Confirm MetaTable. */
    MetaTable *current_meta_table = confirm_meta_table_via_column(column, alias_map);

    return check_column_node(in_node->column, current_meta_table) // check select column
           && check_value_item_set_node(current_meta_table, column->column_name, in_node->value_set);
}

/* Check like data type. */
static bool check_like_data_type(MetaColumn *meta_column) {
    if (meta_column->column_type != T_STRING) {
        db_log(ERROR, "For like predicate, only support string data type.");
        return false;
    }
    return true;
}

/* Check LikeNode. */
static bool check_like_node(LikeNode *like_node, AliasMap alias_map) {
    ColumnNode *column = like_node->column;

    /* Confirm MetaTable. */
    MetaTable *current_meta_table = confirm_meta_table_via_column(column, alias_map);
    MetaColumn *meta_column = get_meta_column_by_name(current_meta_table, column->column_name);

    return check_column_node(column, current_meta_table) // check select column
           && check_like_data_type(meta_column)
           && check_value_item_node(current_meta_table, column->column_name, like_node->value);
}

/* Check PredicateNode. */
static bool check_predicate_node(PredicateNode *predicate_node, AliasMap alias_map) {
    switch (predicate_node->type) {
        case PRE_COMPARISON:
            return check_comparison_node(predicate_node->comparison, alias_map);
        case PRE_IN:
            return check_in_node(predicate_node->in, alias_map);
        case PRE_LIKE:
            return check_like_node(predicate_node->like, alias_map);
    }
}

/* Check condition node. */
static bool check_condition_node(ConditionNode *condition_node, AliasMap alias_entry) {
    if (condition_node == NULL)
        return true;
    switch(condition_node->conn_type) {
        case C_AND:
        case C_OR:
            return check_condition_node(condition_node->left, alias_entry) 
                && check_condition_node(condition_node->right, alias_entry);
        case C_NONE: 
            return check_predicate_node(condition_node->predicate, alias_entry);
    }
}


/* Check TableRefNode. */
static bool check_table_ref(TableRefNode *table_ref) {
    Table *table = open_table(table_ref->table);
    if (table == NULL) {
        db_log(ERROR, "Table '%s' not exist.", table_ref->table);
        return false;
    }
    return true;
}

/* Check TableRefSetNode. */
static bool check_table_ref_set(TableRefSetNode *table_ref_set) {
    uint32_t i, j;
    for (i = 0; i < table_ref_set->size; i++) {
        TableRefNode *table_ref = table_ref_set->set[i];
        if (!check_table_ref(table_ref))
            return false;

        for (j = i + 1; j < table_ref_set->size; j++) {
            TableRefNode *table_ref2 = table_ref_set->set[j];
            /* Check duplicate table. */
            if (streq(table_ref->table, table_ref2->table)) {
                db_log(ERROR, "Duaplicate table '%s'. ", table_ref->table);
                return false;
            }
            /* Check duplicate table alias name. */
            if (table_ref->range_variable && table_ref2->range_variable 
                && streq(table_ref->range_variable, table_ref2->range_variable)) {
                db_log(ERROR, "Duaplicate table alias name: '%s'. ", table_ref->range_variable);
                return false;
            }
        }
    }

    return true;
}

/* Check FromClauseNode. */
static bool check_from_clause(FromClauseNode *from_clause) {
    return from_clause == NULL || check_table_ref_set(from_clause->from);
}

/* Check WhereClauseNode. */
static bool check_where_clause(WhereClauseNode *where_clause, AliasMap alias_map) {
    if (where_clause == NULL)
        return true;

    return check_condition_node(where_clause->condition, alias_map);
}

/* Check TableExpNode. */
static bool check_table_exp(TableExpNode *table_exp, AliasMap alias_map) {
    return check_from_clause(table_exp->from_clause)
        && check_where_clause(table_exp->where_clause, alias_map);
}


/* Check assignment set node */
static bool check_assignment_set_node(UpdateNode *update_node, Table *table) { 

    AssignmentSetNode *assignment_set_node = update_node->assignment_set_node;
    SelectResult *select_result = new_select_result(update_node->table_name);
    ConditionNode *condition_node = get_condition_from_where_clause(update_node->where_clause);
    query_with_condition(condition_node, select_result, count_row, NULL);

    bool change_priamry = false;
    void *new_key = NULL;
    MetaColumn *primary_meta_column = NULL;

    uint32_t i;
    for (i = 0; i < assignment_set_node->num; i++) {
        AssignmentNode *assignment_node = *(assignment_set_node->assignment_node + i);
        ColumnNode *column_node = assignment_node->column;
        ValueItemNode *value_node = assignment_node->value;
        assert_not_null(column_node, "System error, there is no column node in assignment set node.\n");
        MetaColumn *meta_column = get_meta_column_by_name(table->meta_table, column_node->column_name);

        if (meta_column->is_primary) {
            change_priamry = true;
            new_key = get_value_from_value_item_node(value_node, meta_column);
            primary_meta_column = meta_column;
        }

        /* Check column, check type, check if value valid. */
        if (!check_column_node(column_node, table->meta_table) 
            || !if_convert_type(meta_column->column_type, value_node->data_type, meta_column->column_name, table->meta_table->table_name) 
            || !check_value_valid(meta_column, value_node)) {
            free_select_result(select_result);
            return false;
        }
    }

    if (change_priamry) {
        if (select_result->row_size > 1) {
            select_result->row_size = 0;
            free_select_result(select_result);
            db_log(ERROR, "Duplicate key not allowd. ");
            return false;
        }
        
        Assert(new_key);
        Assert(primary_meta_column);
        if (select_result->row_size == 1) {
            Cursor *new_cursor = define_cursor(table, new_key);
            Refer *new_refer = convert_refer(new_cursor);
            Row *default_row = define_row(new_refer);
            free_cursor(new_cursor);
            free_refer(new_refer);
            if (!row_is_deleted(default_row) && equal(default_row->key, new_key, primary_meta_column->column_type)) {
                free_row(default_row);
                select_result->row_size = 0;
                free_select_result(select_result);
                db_log(ERROR, "Key '%s' already exists, not allowd duplicate key. ", get_key_str(new_key, primary_meta_column->column_type));
                return false;
            }
        }
    }

    select_result->row_size = 0;
    free_select_result(select_result);
    return true;
}

/* Check if table alreay exist. */
static bool check_duplicate_table(char *table_name) {
    if (check_table_exist(table_name)) {
        db_log(ERROR, "Table '%s' already exists.", table_name); 
        return false;
    } else 
        return true;
}

/* Check if support priamay key. 
 * Maybe it will allow to not support primary key, but now, must to do.  */
static bool check_primary_null(CreateTableNode *create_table_node) {

    /* check primary key node. */
    if (create_table_node->primary_key_node)
        return true;

    /* check column def define primary. */
    uint32_t i;
    for(i = 0; i < create_table_node->column_def_set_node->size; i++) {
        if (create_table_node->column_def_set_node->column_defs[i]->is_primary)
            return true;
    }

    db_log(ERROR, "Lack primary key definition in table '%s'. ", create_table_node->table_name);

    return false;
}

/* Check if exists duplicate column name. */
static bool check_duplicate_column_name(ColumnDefSetNode *column_def_set_node) {
    uint32_t i, j;
    for(i = 0; i < column_def_set_node->size; i++) {
        ColumnDefNode *column_def_node1 = column_def_set_node->column_defs[i];
        for(j = 0; j < column_def_set_node->size; j++) {
            ColumnDefNode *column_def_node2 = column_def_set_node->column_defs[j];
            if (i !=j && strcmp(column_def_node1->column->column_name, column_def_node2->column->column_name) == 0) {
                db_log(ERROR, "Not allow duplicate column name '%s' in the same table.", column_def_node1->column->column_name);
                return false;
            }
        }
    }

    return true;
}

/* Check SelectNode. */
bool check_select_node(SelectNode *select_node) {
    AliasMap alias_map;
    alias_map.size = 0;

    FromClauseNode *from_clause = select_node->table_exp->from_clause;
    if (from_clause == NULL)
        return true;

    if (from_clause->from->size > MAX_MULTI_TABLE_NUM) {
        db_log(ERROR, "Exceed max table numbers.");
        return false;
    }

    uint32_t i;
    for (i = 0; i < from_clause->from->size; i++) {
        TableRefNode *table_ref = from_clause->from->set[i];
        alias_map.map[i].name = table_ref->table;
        alias_map.map[i].alias = table_ref->range_variable;
        alias_map.size++;
    }

    return check_table_exp(select_node->table_exp, alias_map)
        && check_selection(select_node->selection, alias_map);
}

/* Check insert node. */
bool check_insert_node(InsertNode *insert_node) {

    /* Check table exist.*/
    Table *table = open_table(insert_node->table_name);
    if (table == NULL)
        return false;

    MetaTable *meta_table = table->meta_table;
    
    /* According to all column flag, determine the number of column set. */
    if (insert_node->all_column) {
        
        /* Check column number equals the insert values number. */
        if (meta_table->column_size != insert_node->value_item_set_node->num) {
            db_log(ERROR, "Column count doesn't match value count: %d != %d.", meta_table->column_size, insert_node->value_item_set_node->num);
            return false;
        }
        uint32_t i;
        for (i = 0; i < meta_table->column_size; i++) {
            MetaColumn *meta_column = meta_table->meta_column[i];
            ValueItemNode *value_item_node = *(insert_node->value_item_set_node->value_item_node + i);
            /* Check data type. */
            if (!if_convert_type(meta_column->column_type, value_item_node->data_type, meta_column->column_name, meta_table->table_name))  
                return false;
            if (!check_value_valid(meta_column, value_item_node))
                return false;
        }
    } else {

        /* Check column number equals the insert values number. */
        if (insert_node->columns_set_node->size  != insert_node->value_item_set_node->num) {
            db_log(ERROR, "Column count doesn't match value count\n");
            return false;
        }

        uint32_t i;
        for (i = 0; i < insert_node->columns_set_node->size; i++) {
            ColumnNode *column_node = *(insert_node->columns_set_node->columns + i);
            ValueItemNode *value_item_node = *(insert_node->value_item_set_node->value_item_node + i);
            MetaColumn *meta_column = get_meta_column_by_name(meta_table, column_node->column_name);
            /* Check data type. */
            if (!if_convert_type(meta_column->column_type, value_item_node->data_type, meta_column->column_name, meta_table->table_name)) 
                return false;
            /* Check value valid. */
            if (!check_value_valid(meta_column, value_item_node)) 
                return false;
        }
    }

    return true;
}

/* Check for update node. */
bool check_update_node(UpdateNode *update_node) {
    AliasMap alias_map;
    alias_map.size = 1;
    alias_map.map[0].name = update_node->table_name;
    alias_map.map[0].alias = update_node->table_name;

    Table *table = open_table(update_node->table_name);
    return table != NULL 
           && check_assignment_set_node(update_node, table) 
           && check_where_clause(update_node->where_clause, alias_map);
}

/* Check for delete node. */
bool check_delete_node(DeleteNode *delete_node) {
    /* Unimplement. */
    AliasMap alias_map;
    alias_map.size = 1;
    alias_map.map[0].name = delete_node->table_name;
    alias_map.map[0].alias = delete_node->table_name;

    return check_table_exist(delete_node->table_name)
        && check_condition_node(delete_node->condition_node, alias_map);
}

/* Check for create table node. */
bool check_create_table_node(CreateTableNode *create_table_node) {
    return check_duplicate_table(create_table_node->table_name)
           && check_duplicate_column_name(create_table_node->column_def_set_node)
           && check_primary_null(create_table_node);
}

/* Check if table uses refer. */
static bool if_table_used_refer(char *table_name, char *refer_table_name) {
    Table *table = open_table(table_name);
    assert_not_null(table, "Table '%s' not exist. ", refer_table_name);
    MetaTable *meta_table = table->meta_table;

    uint32_t i;
    for(i = 0; i < meta_table->column_size; i++) {
        MetaColumn *current_meta_column = meta_table->meta_column[i];
        if (current_meta_column->column_type == T_REFERENCE && strcmp(current_meta_column->table_name, refer_table_name) == 0) {
            db_log(ERROR , "Table '%s' is refered by column '%s' in table '%s', so it cant`t be droped.", refer_table_name, current_meta_column->column_name, table_name);
            return true;
        }
    }

    return false;
}

/* Chech allowed to drop table. */
bool check_drop_table(char *table_name) {
    TableList *table_list = get_table_list();

    uint32_t i;
    for (i = 0; i < table_list->count; i++) {
        char *curent_table_name = table_list->table_name_list[i];
        if (if_table_used_refer(curent_table_name, table_name))
            return false;
    }

    return true;
}
