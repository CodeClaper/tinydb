#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <ctype.h>
#include <stddef.h>
#include "sql/intpr.h"

#ifndef DATA_H
#define DATA_H
#define PAGE_SIZE 4096
#define MAX_TABLE_PAGE 100
#define MAX_COLUMN_SIZE 25 // max column size
#define MAX_COLUMN_NAME_LEN 30 // max column name length

typedef struct {
    char *input;
    size_t buffer_length;
    ssize_t input_length;
} InputBuffer;

typedef enum {
    LEAF_NODE,
    INTERNAL_NODE
}NodeType;

typedef enum {
    STMT_CREATE_TABLE,
    STMT_SELECT,
    STMT_UPDATE,
    STMT_INSERT,
    STMT_DELETE,
    STMT_DESCRIBE,
    STMT_SHOW_TABLES
}StamentType;

typedef struct {
    StamentType statement_type;
    ASTNode *ast_node;
}Statement;

typedef enum {
    EXECUTE_SUCCESS,
    EXECUTE_FAIL,
    EXECUTE_TABLE_EXIST_FAIL,
    EXECUTE_TABLE_CREATE_FAIL,
    EXECUTE_TABLE_DROP_FAIL,
    EXECUTE_TABLE_OPEN_FAIL,
    EXECUTE_DUPLICATE_KEY
}ExecuteResult;

typedef struct {
    int file_descriptor; 
    uint32_t file_length;
    uint32_t num_page;
    void *pages[MAX_TABLE_PAGE];
} Pager;

typedef struct {
    char column_name[MAX_COLUMN_NAME_LEN];
    DataType column_type;
    uint32_t column_length;
    bool is_primary;
} MetaColumn;

typedef struct {
    char *table_name;
    MetaColumn *meta_column[MAX_COLUMN_SIZE];
    uint32_t column_size;
} MetaTable;


typedef struct {
    Pager *pager;
    uint32_t root_page_num;
    MetaTable *meta_table;
}Table;

typedef struct {
    Table *table;
    uint32_t page_num;
    uint32_t cell_num;
}Cursor;

typedef struct {
    char *key;
    void *value;
}KeyValue;

typedef struct {
    uint32_t key;
    char *table_name;
    KeyValue **data;
    uint32_t column_len;
}Row;


typedef struct {
    char *table_name;
    bool is_function;
    MetaColumn **meta_columns;
    uint32_t column_size;
    FunctionNode *function_node;
    ConditionNode *condition_node;
}QueryParam;

typedef struct {
    char *table_name;
    Row **row;
    uint32_t row_len;
}SelectResult;

#endif
