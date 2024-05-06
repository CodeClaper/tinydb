#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define _XOPEN_SOURCE
#define __USE_XOPEN
#include <time.h>
#include "meta.h"
#include "mmu.h"
#include "copy.h"
#include "free.h"
#include "log.h"
#include "refer.h"
#include "insert.h"
#include "utils.h"
#include "common.h"
#include "ltree.h"
#include "list.h"
#include "asserts.h"
#include "pager.h"
#include "refer.h"

#define DEFAULT_BOOL_LENGTH         2
#define DEFAULT_STRING_LENGTH       48
#define DEFAULT_DATE_LENGTH         20
#define DEFAULT_TIMESTAMP_LENGTH    20
#define DEFAULT_REFERENCE_LENGTH    48


/* Column type length */
uint32_t default_data_len(DataType column_type) {
    switch (column_type) {
        case T_BOOL:
            return DEFAULT_BOOL_LENGTH;
        case T_CHAR:
            return sizeof(char);
        case T_VARCHAR:
            return DEFAULT_STRING_LENGTH;
        case T_INT:
            return sizeof(int32_t);
        case T_LONG:
            return sizeof(int64_t);
        case T_DOUBLE:
            return sizeof(double);
        case T_FLOAT:
            return sizeof(float);
        case T_STRING:
            return DEFAULT_STRING_LENGTH;
        case T_DATE:
            return DEFAULT_DATE_LENGTH;
        case T_TIMESTAMP:
            return DEFAULT_TIMESTAMP_LENGTH;
        case T_REFERENCE:
            return DEFAULT_REFERENCE_LENGTH;
        default:
            db_log(PANIC, "Unknown column type");
  }
}

/* Convert AtomType to DataType. */
DataType convert_data_type(AtomType atom_type) {
    switch (atom_type) {
        case A_INT:
            return T_INT;
        case A_BOOL:
            return T_BOOL;
        case A_FLOAT:
            return T_DOUBLE;
        case A_STRING:
            return T_STRING;
        case A_REFERENCE:
            return T_REFERENCE;
        default:
            UNEXPECTED_VALUE(atom_type);
    }
}

/* Assign value from atom*/
static void *assign_value_from_atom(AtomNode *atom_node, MetaColumn *meta_column) {

    /* Assign new value. */
    switch(meta_column->column_type) {
        case T_BOOL: {
            return copy_value(&atom_node->value.boolval, meta_column->column_type);
        }
        case T_INT: {
            int32_t val = (int32_t)atom_node->value.intval;
            return copy_value(&val, meta_column->column_type);
        }
        case T_LONG: {
            int64_t val = (int64_t)atom_node->value.intval;
            return copy_value(&val, meta_column->column_type);
        }
        case T_FLOAT: {
            float val = 0;
            switch (atom_node->type) {
                case A_INT:
                    val = (float)atom_node->value.intval;
                    break;
                case A_FLOAT:
                    val = (float)atom_node->value.floatval;
                    break;
            }
            return copy_value(&val, meta_column->column_type);
        }
        case T_DOUBLE: {
            double val = 0;
            switch (atom_node->type) {
                case A_INT:
                    val = (double)atom_node->value.intval;
                    break;
                case A_FLOAT:
                    val = (double)atom_node->value.floatval;
                    break;
                default:
                    db_log(ERROR, "Can`t convert to data type [%s] for column '%s'", 
                           convert_data_type(atom_node->type), 
                           meta_column->column_name);
                    break;
            }
            return copy_value(&val, meta_column->column_type);
        }
        case T_CHAR:
        case T_STRING: 
        case T_VARCHAR: {
            return copy_value(atom_node->value.strval, meta_column->column_type);
        }
        case T_DATE: {
            struct tm tmp_time;
            time_t *time = instance(time_t);  
            strptime(atom_node->value.strval, "%Y-%m-%d", &tmp_time);
            tmp_time.tm_sec = 0;
            tmp_time.tm_min = 0;
            tmp_time.tm_hour = 0;
            time_t tmp = mktime(&tmp_time);
            memcpy(time, &tmp, sizeof(time_t));
            return time;
        }
        case T_TIMESTAMP: {
            struct tm tmp_time;
            time_t *time = instance(time_t);  
            strptime(atom_node->value.strval, "%Y-%m-%d %H:%M:%S", &tmp_time);
            time_t tmp = mktime(&tmp_time);
            memcpy(time, &tmp, sizeof(time_t));
            return time;
        }
        case T_REFERENCE: {
            ReferValue *refer_value = atom_node->value.referval;
            switch (refer_value->type) {
                case DIRECTLY: {
                    InsertNode *insert_node = fake_insert_node(meta_column->table_name, refer_value->nest_value_item_set);
                    Refer *refer = insert_for_values(insert_node);
                    free_insert_node(insert_node);
                    return refer;
                }
                case INDIRECTLY: {
                    return fetch_refer(meta_column, refer_value->condition);
                }
                default:
                    UNEXPECTED_VALUE(refer_value->type);
                    return NULL;
            }
            break;
        }
        default:
            UNEXPECTED_VALUE(meta_column->column_type);
            return NULL;
    }    
}

/* Assign value from array. */
void *assign_value_from_array(ValueItemSetNode *value_set, MetaColumn *meta_column) {
    ArrayValue *array_value = instance(ArrayValue);
    array_value->size = value_set->num;
    array_value->type = meta_column->column_type;
    array_value->set = db_malloc(sizeof(void *) * array_value->size, "pointer");

    uint32_t i;
    for (i = 0; i < array_value->size; i++) {
        ValueItemNode *value_item = value_set->value_item_node[i];
        array_value->set[i] = assign_value_from_value_item_node(value_item, meta_column);
    }

    return array_value;
}

/* Assign value from ValueItemNode. */
void *assign_value_from_value_item_node(ValueItemNode *value_item_node, MetaColumn *meta_column) {
    switch (value_item_node->type) {
        case V_ATOM: {
            AtomNode *atom_node = value_item_node->value.atom;
            return assign_value_from_atom(atom_node, meta_column);
        }
        case V_ARRAY: {
            ValueItemSetNode *value_set = value_item_node->value.value_set;
            return assign_value_from_array(value_set, meta_column);
        }
        case V_NULL:
            return NULL;
        default:
            UNEXPECTED_VALUE(value_item_node->type);
    }
}

/* Get value from atom. */
static void *get_value_from_atom(AtomNode *atom_node, MetaColumn *meta_column) {
    /* User can use '%s' fromat in sql to pass multiple types value including char, string, date, timestamp. 
     * So we must use meta column data type to define which data type of the value. */
    switch (meta_column->column_type) {
        case T_BOOL: {
            return copy_value(&atom_node->value.boolval, meta_column->column_type);
        }
        case T_INT: {
            int32_t val = (int32_t)atom_node->value.intval;
            return copy_value(&val, meta_column->column_type);
        }
        case T_LONG: {
            int64_t val = (int64_t)atom_node->value.intval;
            return copy_value(&val, meta_column->column_type);
        }
        case T_FLOAT: {
            float val = 0;
            switch (atom_node->type) {
                case A_INT:
                    val = (float)atom_node->value.intval;
                    break;
                case A_FLOAT:
                    val = (float)atom_node->value.floatval;
                    break;
            }
            return copy_value(&val, meta_column->column_type);
        }
        case T_DOUBLE: {
            double val = 0;
            switch (atom_node->type) {
                case A_INT:
                    val = (double)atom_node->value.intval;
                    break;
                case A_FLOAT:
                    val = (double)atom_node->value.floatval;
                    break;
                default:
                    db_log(ERROR, "Can`t convert to data type [%s] for column '%s'", 
                           convert_data_type(atom_node->type), 
                           meta_column->column_name);
                    break;
            }
            return copy_value(&val, meta_column->column_type);
        }
        case T_CHAR:
        case T_STRING: 
        case T_VARCHAR: {
            return copy_value(atom_node->value.strval, meta_column->column_type);
        }
        case T_DATE: {
            struct tm tmp_time;
            time_t *time = instance(time_t);  
            strptime(atom_node->value.strval, "%Y-%m-%d", &tmp_time);
            tmp_time.tm_sec = 0;
            tmp_time.tm_min = 0;
            tmp_time.tm_hour = 0;
            time_t tmp = mktime(&tmp_time);
            memcpy(time, &tmp, sizeof(time_t));
            return time;
        }
        case T_TIMESTAMP: {
            struct tm tmp_time;
            time_t *time = instance(time_t);  
            strptime(atom_node->value.strval, "%Y-%m-%d %H:%M:%S", &tmp_time);
            time_t tmp = mktime(&tmp_time);
            memcpy(time, &tmp, sizeof(time_t));
            return time;
        }
        case T_REFERENCE: {
            ReferValue *refer_value = atom_node->value.referval;
            switch (refer_value->type) {
                case DIRECTLY:
                    db_log(WARN, "Not support directly fetch refer when query.");
                    return make_null_refer();
                case INDIRECTLY: 
                    return fetch_refer(meta_column, refer_value->condition);
            }
            break;
        }
        default:
            db_log(PANIC, "Not implement yet.");
    }
    return NULL;
}

/* Get value from value item node. */
void *get_value_from_value_item_node(ValueItemNode *value_item_node, MetaColumn *meta_column) {
    /* For array, return value set. */
    switch (value_item_node->type) {
        case V_ATOM: {
            AtomNode *atom_node = value_item_node->value.atom;
            return get_value_from_atom(atom_node, meta_column);
        }
        case V_ARRAY:
            return value_item_node->value.value_set;
        case V_NULL:
            return NULL;
        default:
            UNEXPECTED_VALUE(value_item_node->type);
    }
}

/* Calculate the length of table row. */
uint32_t calc_table_row_length(Table *table) {
    uint32_t row_len = 0;
    uint32_t i;
    for (i = 0; i < table->meta_table->all_column_size; i++) {
        MetaColumn *meta_col = (table->meta_table->meta_column[i]);
        row_len+= meta_col->column_length;
    }
    return row_len;
}

/* Calculate primary key lenght. 
 * Return primary-key column length.
 * Panic if not found. */
uint32_t calc_primary_key_length(Table *table) {
    uint32_t i;
    for (i = 0; i < table->meta_table->all_column_size; i++) {
       MetaColumn *meta_column = table->meta_table->meta_column[i];
       if (meta_column->is_primary)
           return meta_column->column_length;
    }
    panic("Not found primary key.");
    return -1;
}

/* Get index column meta info */
MetaColumn *get_meta_column_by_index(void *root_node, uint32_t index) {
    void *destination = get_meta_column_pointer(root_node, index);
    return deserialize_meta_column(destination);
}

/* Get meta column info by column name. */
MetaColumn *get_meta_column_by_name(MetaTable *meta_table, char *name) {
    uint32_t i;
    for (i = 0; i < meta_table->column_size; i++) {
      MetaColumn *meta_column = meta_table->meta_column[i];
      if (streq(meta_column->column_name, name))
        return meta_column;
    }
    return NULL;
}


/* Get all meta column info by column name including system reserved column. 
 * Return NULL if not found.
 * */
MetaColumn *get_all_meta_column_by_name(MetaTable *meta_table, char *name) {
    uint32_t i;
    for (i = 0; i < meta_table->all_column_size; i++) {
      MetaColumn *meta_column = meta_table->meta_column[i];
      if (streq(meta_column->column_name, name))
        return meta_column;
    }
    return NULL;
}

/* Get table meta info. */
MetaTable *get_meta_table(Table *table, char *table_name) {
    /* Check valid. */
    assert_not_null(table_name, "Input table name can`t be null.");

    MetaTable *meta_table = instance(MetaTable);
    void *root_node = get_page(table_name, table->pager, table->root_page_num);
    uint32_t column_size = get_column_size(root_node);

    meta_table->table_name = db_strdup(table_name);
    meta_table->column_size = 0;
    meta_table->all_column_size = 0;
    meta_table->meta_column = db_malloc(sizeof(MetaColumn *) * column_size, "pointer");

    uint32_t i;
    for (i = 0; i < column_size; i++) {
        MetaColumn *current = get_meta_column_by_index(root_node, i);
        meta_table->meta_column[i] = current;

        /* Skip to system reserved column. */
        if (!current->sys_reserved)
            meta_table->column_size++;

        meta_table->all_column_size++;
    }

    assert_true(meta_table->all_column_size == column_size, "System Logic Error in <get_meta_table>");

    return meta_table;
}
