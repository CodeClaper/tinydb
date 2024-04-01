#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include "table.h"
#include "copy.h"
#include "free.h"
#include "data.h"
#include "index.h"
#include "meta.h"
#include "log.h"
#include "asserts.h"
#include "common.h"
#include "mmu.h"

/* Copy value. */
void *copy_value(void *value, DataType data_type) {
    if (value == NULL)
        return NULL;
    switch(data_type) {
        case T_BOOL: {
            bool *new_val = db_malloc(sizeof(bool), SDT_BOOL);
            memcpy(new_val, value, sizeof(bool));
            return new_val;
        }
        case T_INT: {
            int32_t *new_val = db_malloc(sizeof(int32_t), SDT_INT);
            memcpy(new_val, value, sizeof(int32_t));
            return new_val;
        }
        case T_LONG: {
            int64_t *new_val = db_malloc(sizeof(int64_t), SDT_INT);
            memcpy(new_val, value, sizeof(int64_t));
            return new_val;
        }
        case T_FLOAT: {
            float *new_val = db_malloc(sizeof(float), SDT_FLOAT);
            memcpy(new_val, value, sizeof(float));
            return new_val;
        }
        case T_DOUBLE: {
            double *new_val = db_malloc(sizeof(double), SDT_DOUBLE);
            memcpy(new_val, value, sizeof(double));
            return new_val;
        }
        case T_DATE:
        case T_TIMESTAMP: {
            time_t *new_val = db_malloc(sizeof(time_t), SDT_TIME_T);
            memcpy(new_val, value, sizeof(time_t));
            return new_val;
        }
        case T_CHAR:
        case T_STRING: {
            char *new_val = db_strdup((char *)value);
            return new_val;
        }
        case T_REFERENCE: {
            Refer *refer = db_malloc(sizeof(Refer), SDT_REFER);
            memcpy(refer, value, sizeof(Refer));
            return refer;
        }
        default:
            db_log(PANIC, "Not supported data type occurs at <copy_value>.");
    }    
}

/* Copy Key value pair. */
KeyValue *copy_key_value(KeyValue *key_value) {
    
    /* check */
    if (key_value == NULL)
        return NULL;

    /* copy key value */
    KeyValue *key_value_copy = db_malloc(sizeof(KeyValue), SDT_KEY_VALUE);

    key_value_copy->key = db_strdup(key_value->key);
    /*Meta column may be null, in fact, key aggregate function, key is min, max, sum, avg ect. there is no meta column. */
    key_value_copy->value = copy_value(key_value->value, key_value->data_type);
    key_value_copy->data_type = key_value->data_type;
    key_value_copy->table_name = db_strdup(key_value->table_name);

    return key_value_copy;
}

/* Copy row. */
Row *copy_row(Row *row) {
    /* check */
    if (row == NULL)
        return NULL;
    Table *table = open_table(row->table_name);
    if (table == NULL) {
        db_log(ERROR, "Table '%s' not exists. ", row->table_name);
        return NULL;
    }

    /* copy row */
    Row *row_copy = db_malloc(sizeof(Row), SDT_ROW);
    MetaColumn *primary_meta_column = get_primary_key_meta_column(table->meta_table);
    row_copy->key = copy_value(row->key, primary_meta_column->column_type);
    row_copy->column_len = row->column_len;
    row_copy->table_name = db_strdup(row->table_name);
    row_copy->data = db_malloc(sizeof(KeyValue *) * row->column_len, SDT_POINTER);

    uint32_t i;
    for(i = 0; i < row->column_len; i++) {
        row_copy->data[i] = copy_key_value(row->data[i]);
    }

    return row_copy;
}

/* Copy row igonore system reserved columns. */
Row *copy_row_without_reserved(Row *row) {
    /* check */
    if (row == NULL)
        return NULL;
    Table *table = open_table(row->table_name);
    if (table == NULL) {
        db_log(ERROR, "Table '%s' not exists. ", row->table_name);
        return NULL;
    }

    MetaColumn *primary_meta_column = get_primary_key_meta_column(table->meta_table);

    /* copy row. */
    Row *row_copy = db_malloc(sizeof(Row), SDT_ROW);
    row_copy->key = copy_value(row->key, primary_meta_column->column_type);
    row_copy->table_name = db_strdup(row->table_name);
    row_copy->column_len = 0;
    row_copy->data = db_malloc(sizeof(KeyValue *) * row_copy->column_len, SDT_STRING);

    uint32_t i;
    for (i = 0; i < row->column_len; i++) {
        KeyValue *key_value = row->data[i];

        /* Skip system reserved columns. */
        MetaColumn *meta_column = get_all_meta_column_by_name(table->meta_table, key_value->key);
        if (meta_column && meta_column->sys_reserved) 
            continue;

        row_copy->data = db_realloc(row_copy->data, sizeof(KeyValue *) * (row_copy->column_len + 1));
        /* copy key value. */
        row_copy->data[row_copy->column_len++] = copy_key_value(key_value);
    }

    return row_copy;
}

/* Copy refer. */
Refer *copy_refer(Refer *refer) {
    if (refer == NULL) return NULL;
    Refer *copy_refer = db_malloc(sizeof(Refer), SDT_REFER);
    memset(copy_refer, 0, sizeof(Refer));
    strcpy(copy_refer->table_name, refer->table_name);
    copy_refer->page_num = refer->page_num;
    copy_refer->cell_num = refer->cell_num;
    return copy_refer;
}

/* Copy meta column. */
MetaColumn *copy_meta_column(MetaColumn *meta_column) {
    if (meta_column == NULL)
        return NULL;

    MetaColumn *meta_column_copy = db_malloc(sizeof(MetaColumn), SDT_META_COLUMN);
    meta_column_copy->is_primary = meta_column->is_primary;
    meta_column_copy->column_type = meta_column->column_type;
    meta_column_copy->column_length = meta_column->column_length;
    meta_column_copy->sys_reserved = meta_column->sys_reserved;
    strcpy(meta_column_copy->column_name, meta_column->column_name);
    strcpy(meta_column_copy->table_name, meta_column->table_name);

    return meta_column_copy;
}

/* Copy MetaTable.*/
MetaTable *copy_meta_table(MetaTable *meta_table) {
    if (meta_table == NULL)
        return NULL;

    MetaTable *copy = db_malloc(sizeof(MetaTable), SDT_META_TABLE);
    copy->table_name = db_strdup(meta_table->table_name);
    copy->column_size = meta_table->column_size;
    copy->all_column_size = meta_table->all_column_size;
    copy->meta_column = db_malloc(sizeof(MetaColumn *) * copy->all_column_size, SDT_POINTER);

    int i;
    for (i = 0; i < meta_table->all_column_size; i++) {
        copy->meta_column[i] = copy_meta_column(meta_table->meta_column[i]);
    }

    return copy;
}

/* Copy Pager. */
Pager *copy_pager(Pager *pager) {
    if (pager == NULL)
        return NULL;

    Pager *pager_copy = db_malloc(sizeof(Pager), SDT_PAGER);
    pager_copy->size = pager->size;
    pager_copy->file_length = pager->file_length;
    pager_copy->file_descriptor = pager->file_descriptor;

    int32_t i;
    for (i = 0; i < pager->size; i++) {
        pager_copy->pages[i] = copy_block(pager->pages[i], PAGE_SIZE);
    }

    return pager_copy;
}

/* Copy Table. */
Table *copy_table(Table *table) {
    if (table == NULL)
        return NULL;

    Table *table_copy = db_malloc(sizeof(Table), SDT_TABLE);
    table_copy->root_page_num = table->root_page_num;
    table_copy->pager = copy_pager(table->pager);
    table_copy->meta_table = copy_meta_table(table->meta_table);

    return table_copy;
}

/* Copy column node. */
ColumnNode *copy_column_node(ColumnNode *column_node) {
    if (column_node == NULL)
        return NULL;
    ColumnNode *column_node_copy = db_malloc(sizeof(ColumnNode), SDT_COLUMN_NODE);
    column_node_copy->has_sub_column = column_node->has_sub_column;
    if (column_node_copy->has_sub_column) {
        column_node_copy->sub_column = copy_column_node(column_node->sub_column);
        column_node_copy->scalar_exp_set = copy_scalar_exp_set_node(column_node->scalar_exp_set);
    }
    column_node_copy->column_name = db_strdup(column_node->column_name);
    return column_node_copy;
}

/* Copy column set node. */
ColumnSetNode *copy_column_set_node(ColumnSetNode *column_set_node) {
    if (column_set_node == NULL)
        return NULL;
    ColumnSetNode *column_set_node_copy = db_malloc(sizeof(ColumnSetNode), SDT_COLUMN_SET_NODE);
    column_set_node_copy->size = column_set_node->size;
    column_set_node_copy->columns = db_malloc(sizeof(ColumnNode *) * column_set_node_copy->size, SDT_POINTER);
    for (uint32_t i = 0; i < column_set_node_copy->size; i++) {
        *(column_set_node_copy->columns + i) = copy_column_node(*(column_set_node->columns + i));
    }
    return column_set_node_copy;
}

/* Copy value item node. */
ValueItemNode *copy_value_item_node(ValueItemNode *value_item_node) {
    if (value_item_node == NULL)
        return NULL;
    ValueItemNode *value_item_node_copy = db_malloc(sizeof(ValueItemNode), SDT_VALUE_ITEM_NODE);
    value_item_node_copy->data_type = value_item_node->data_type;
    switch(value_item_node->data_type) {
        case T_CHAR:
        case T_STRING:
            value_item_node_copy->value.s_value = db_strdup(value_item_node->value.s_value);
            break;
        case T_INT:
        case T_LONG:
            value_item_node_copy->value.i_value = value_item_node->value.i_value;
            break;
        case T_BOOL:
            value_item_node_copy->value.b_value = value_item_node->value.b_value;
            break;
        case T_FLOAT:
            value_item_node_copy->value.f_value = value_item_node->value.f_value;
            break;
        case T_DOUBLE:
            value_item_node_copy->value.d_value = value_item_node->value.d_value;
            break;
        case T_TIMESTAMP:
        case T_DATE:
            value_item_node_copy->value.t_value = value_item_node->value.t_value;
            break;
        case T_REFERENCE: 
            value_item_node_copy->value.r_value = copy_refer_value(value_item_node->value.r_value);
            break;
    }
    return value_item_node_copy;
}

/* Copy ValueItemSetNode. */
ValueItemSetNode *copy_value_item_set_node(ValueItemSetNode *value_item_set_node) {
    if (value_item_set_node == NULL)
        return NULL;
    ValueItemSetNode *copy = db_malloc(sizeof(ValueItemSetNode), SDT_VALUE_ITEM_SET_NODE);
    copy->num = value_item_set_node->num;
    copy->value_item_node = db_malloc(sizeof(ValueItemNode *) * value_item_set_node->num, SDT_POINTER);

    int i;
    for (i = 0; i < value_item_set_node->num; i++) {
        copy->value_item_node[i] = copy_value_item_node(value_item_set_node->value_item_node[i]);
    }
    return copy;
}

/*Copy function value node. */
FunctionValueNode *copy_function_value_node(FunctionValueNode *function_value_node) {
    if (function_value_node == NULL)
        return NULL;
    FunctionValueNode *function_value_node_copy = db_malloc(sizeof(FunctionValueNode), SDT_FUNCTION_VALUE_NODE);
    function_value_node_copy->value_type = function_value_node->value_type;
    switch(function_value_node->value_type) {
        case V_INT:
            function_value_node_copy->i_value = function_value_node->i_value;
            break;
        case V_COLUMN:
            function_value_node_copy->column = copy_column_node(function_value_node->column);
            break;
        case V_ALL:
            break;
    }
    return function_value_node_copy;
}

/* Copy function node. */
FunctionNode *copy_function_node(FunctionNode *function_node) {
    if (function_node == NULL)
        return NULL;
    FunctionNode *function_node_copy = db_malloc(sizeof(FunctionNode), SDT_FUNCTION_NODE);
    function_node_copy->type = function_node->type;
    function_node_copy->value = copy_function_value_node(function_node->value);
    return function_node_copy;
}

CalculateNode *copy_calculate_node(CalculateNode *calculate_node) {
    if (calculate_node == NULL)
        return NULL;
    CalculateNode *copy = db_malloc(sizeof(CalculateNode), SDT_CALCULATE_NODE);
    copy->type = calculate_node->type;
    copy->left = copy_scalar_exp_node(calculate_node->left);
    copy->right = copy_scalar_exp_node(calculate_node->right);

    return copy;
}


PredicateNode *copy_predicate_node(PredicateNode *predicate_node) {
    if (predicate_node == NULL)
        return NULL;
    PredicateNode *copy = db_malloc(sizeof(PredicateNode), SDT_PREDICATE_NODE);
    copy->type = predicate_node->type;
    switch (copy->type) {
        case PRE_COMPARISON:
            copy->comparison = copy_comparison_node(predicate_node->comparison);
            break;
        case PRE_LIKE:
            copy->like = copy_like_node(predicate_node->like);
            break;
        case PRE_IN:
            copy->in = copy_in_node(predicate_node->in);
            break;
        default:
            db_log(PANIC, "Unknown predicate type");
    }
    return copy;
}

/* Copy condition node. */
ConditionNode *copy_condition_node(ConditionNode *condition_node) {
    if (condition_node == NULL)
        return NULL;
    ConditionNode *condition_node_copy = db_malloc(sizeof(ConditionNode), SDT_CONDITION_NODE);
    condition_node_copy->conn_type = condition_node->conn_type;
    switch(condition_node->conn_type) {
        case C_OR:
        case C_AND:
            condition_node_copy->left = copy_condition_node(condition_node->left);
            condition_node_copy->right = copy_condition_node(condition_node->right);
            condition_node_copy->conn_type = condition_node->conn_type;
            break;
        case C_NONE:
            condition_node_copy->predicate = copy_predicate_node(condition_node->predicate);
            break;
    }
    return condition_node_copy;
}

/* Copy a ComparisonNode. */
ComparisonNode *copy_comparison_node(ComparisonNode *comparison_node) {
    if (comparison_node == NULL)
        return NULL;
    ComparisonNode *comparison_node_copy = db_malloc(sizeof(ComparisonNode), SDT_COMPARISON_NODE);
    comparison_node_copy->type = comparison_node->type;
    comparison_node_copy->column = copy_column_node(comparison_node->column);
    comparison_node_copy->value = copy_scalar_exp_node(comparison_node->value);
    return comparison_node_copy;
}

/* Copy a LikeNode. */
LikeNode *copy_like_node(LikeNode *like_node) {
    if (like_node == NULL)
        return NULL;
    LikeNode *copy = db_malloc(sizeof(LikeNode), SDT_LIKE_NODE);
    copy->column = copy_column_node(like_node->column);
    copy->value = copy_value_item_node(like_node->value);
    return copy;
}

/* Copy an InNode. */
InNode *copy_in_node(InNode *in_node) {
    if (in_node == NULL)
        return NULL;
    InNode *copy = db_malloc(sizeof(InNode), SDT_IN_NODE);
    copy->column = copy_column_node(in_node->column);
    copy->value_set = copy_value_item_set_node(in_node->value_set);
    return copy;
}

/* Copy LimitNode. */
LimitNode *copy_limit_node(LimitNode *limit_node) {
    if (limit_node == NULL)
        return NULL;
    LimitNode *limit_node_copy = db_malloc(sizeof(LimitNode), SDT_LIMIT_NODE);
    limit_node_copy->start = limit_node->start;
    limit_node_copy->end = limit_node->end;
    return limit_node_copy;
}

/* Copy ReferValue. */
ReferValue *copy_refer_value(ReferValue *refer_value) {
    if (refer_value == NULL)
        return NULL;
    ReferValue *refer_value_copy = db_malloc(sizeof(ReferValue), SDT_REFER_VALUE);
    refer_value_copy->type = refer_value->type;
    switch (refer_value->type) {
        case DIRECTLY:
            refer_value_copy->nest_value_item_set = copy_value_item_set_node(refer_value->nest_value_item_set);
            break;
        case INDIRECTLY:
            refer_value_copy->condition = copy_condition_node(refer_value->condition);
            break;
    }
    return refer_value_copy;
}

/* Copy select items node. */
SelectItemsNode *copy_select_items_node(SelectItemsNode *select_items_node) {
    if (select_items_node == NULL)
        return NULL;
    SelectItemsNode *select_items_node_copy = db_malloc(sizeof(SelectItemsNode), SDT_SELECT_ITEMS_NODE);
    select_items_node_copy->type = select_items_node->type;
    switch(select_items_node_copy->type) {
        case SELECT_FUNCTION:
            select_items_node_copy->function_node = copy_function_node(select_items_node->function_node);
            break;
        case SELECT_COLUMNS:
            select_items_node_copy->column_set_node = copy_column_set_node(select_items_node->column_set_node);
            break;
        case SELECT_ALL:
            break;
    }
    return select_items_node_copy;
}

/* Copy a ScalarExpNode. */
ScalarExpNode *copy_scalar_exp_node(ScalarExpNode *scalar_exp_node) {
    if (scalar_exp_node == NULL)
        return NULL;

    ScalarExpNode *copy = db_malloc(sizeof(ScalarExpNode), SDT_SCALAR_EXP_NODE);
    copy->type = scalar_exp_node->type;
    switch (scalar_exp_node->type) {
        case SCALAR_COLUMN:
            copy->column = copy_column_node(scalar_exp_node->column);
            break;
        case SCALAR_FUNCTION:
            copy->function = copy_function_node(scalar_exp_node->function);
            break;
        case SCALAR_CALCULATE:
            copy->calculate = copy_calculate_node(scalar_exp_node->calculate);
            break;
        case SCALAR_VALUE:
            copy->value = copy_value_item_node(scalar_exp_node->value);
            break;
        default:
            db_log(ERROR, "Not support scalar type.");
    }
    copy->alias = copy_value(scalar_exp_node->alias, T_STRING);
    return copy;
}

/* Copy ScalarExpSetNode. */
ScalarExpSetNode *copy_scalar_exp_set_node(ScalarExpSetNode *scalar_exp_set_node) {
    if (scalar_exp_set_node == NULL)
         return NULL;
    ScalarExpSetNode *copy = db_malloc(sizeof(ScalarExpSetNode), SDT_SCALAR_EXP_SET_NODE);
    copy->size = scalar_exp_set_node->size;
    copy->data = db_malloc(sizeof(ScalarExpNode *) * scalar_exp_set_node->size, SDT_POINTER);
    int i;
    for (i = 0; i < scalar_exp_set_node->size; i++) {
        copy->data[i] = copy_scalar_exp_node(scalar_exp_set_node->data[i]);
    }
    return copy;
}


/* Copy SelectionNode. */
SelectionNode *copy_selection_node(SelectionNode *selection_node) {
    if (selection_node == NULL)
        return NULL;
    SelectionNode *copy = db_malloc(sizeof(SelectionNode), SDT_SELECTION_NODE);
    copy->all_column = selection_node->all_column;
    if (!copy->all_column)
        copy->scalar_exp_set = copy_scalar_exp_set_node(selection_node->scalar_exp_set);
    return copy;
}

/* Copy query param. */
QueryParam *copy_query_param(QueryParam *query_param) {
    if (query_param == NULL)
        return NULL;
    QueryParam *query_param_copy = db_malloc(sizeof(QueryParam), SDT_QUERY_PARAM);
    query_param_copy->table_name = db_strdup(query_param->table_name);
    query_param_copy->condition_node = copy_condition_node(query_param->condition_node); 
    query_param_copy->selection = copy_selection_node(query_param->selection);
    return query_param_copy;
}

/* Copy a dymamic memory block */
void *copy_block(void *value, size_t size) {
    if (value == NULL)
        return NULL;
    void * block = db_malloc(size, SDT_VOID);
    memcpy(block, value, size);
    return block;
}
