#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#ifndef DATA_H
#define DATA_H

#define PAGE_SIZE 4096
#define MAX_TABLE_PAGE 10000
#define MAX_COLUMN_SIZE 25     // max column size
#define MAX_COLUMN_NAME_LEN 30 // max column name length
#define BUFF_SIZE 1024

#define MAX_COLUMN_SIZE 25
#define MAX_COLUMN_NAME_LEN 30 // max column name length

/* OprType */
typedef enum { O_EQ, O_NE, O_GT, O_GE, O_LT, O_LE, O_IN, O_LIKE } OprType;

/* DataType */
typedef enum {
  T_BOOL,
  T_CHAR,
  T_INT,
  T_DOUBLE,
  T_FLOAT,
  T_STRING,
  T_DATE,
  T_TIMESTAMP
} DataType;

/* FunctionType */
typedef enum { F_COUNT, F_MAX, F_MIN, F_SUM, F_AVG } FunctionType;

/* ConnType */
typedef enum { C_OR, C_AND } ConnType; // connector type

/* FunctionValueType */
typedef enum { V_INT, V_COLUMN, V_ALL } FunctionValueType; // value type.

/* SelectItemType */
typedef enum { SELECT_COLUMNS, SELECT_FUNCTION, SELECT_ALL } SelectItemType;

/* ConditionNodeType */
typedef enum { LOGIC_CONDITION, EXEC_CONDITION } ConditionNodeType;

/* ShowNodeType */
typedef enum { SHOW_TABLES, SHOW_MEMORY } ShowNodeType;

/* StatementType */
typedef enum {
  CREATE_TABLE_STMT,
  SELECT_STMT,
  INSERT_STMT,
  UPDATE_STMT,
  DELETE_STMT,
  DESCRIBE_STMT,
  SHOW_STMT
} StatementType; // statement type

/* ColumnNode */
typedef struct {
  char *column_name;
  bool exist_table_name;
  char *table_name;
} ColumnNode;

/* ColumnSetNode */
typedef struct {
  ColumnNode **columns;
  uint32_t size;
} ColumnSetNode;

/* FunctionValueType */
typedef struct {
  FunctionValueType value_type;
  union {
    int32_t i_value;
    ColumnNode *column;
  };
} FunctionValueNode;

/* FunctionNode */
typedef struct {
  FunctionType function_type;
  FunctionValueNode *value;
} FunctionNode;

/* SelectItemsNode */
typedef struct {
  ColumnSetNode *column_set_node;
  FunctionNode *function_node;
  SelectItemType type;
} SelectItemsNode;

/* ColumnDefNode */
typedef struct {
  ColumnNode *column;
  DataType data_type;
  bool is_primary;
  bool allow_null;
} ColumnDefNode;

/* ColumnDefSetNode */
typedef struct {
  ColumnDefNode **column_defs;
  uint32_t size;
} ColumnDefSetNode;

/* PrimaryKeyNode */
typedef struct {
  ColumnNode *column;
} PrimaryKeyNode;

/* ValueItemNode */
typedef struct {
  DataType data_type;
  union {
    /* T_INT */
    int i_value;
    /* T_BOOL */
    bool b_value;
    /* T_CHAR, T_STRING */
    char *s_value;
    /* T_FLOAT */
    float f_value;
    /* T_DOUBLE */
    double d_value;
    /* T_TIMESTAMP, T_DATE */
    time_t t_value;
  };
} ValueItemNode;

/* ValueItemSetNode */
typedef struct {
  ValueItemNode **value_item_node;
  uint32_t num;
} ValueItemSetNode;

/* AssignmentNode */
typedef struct {
  ColumnNode *column;
  ValueItemNode *value;
} AssignmentNode;

/* AssignmentSetNode */
typedef struct {
  AssignmentNode **assignment_node;
  uint32_t num;
} AssignmentSetNode;

/* ConditionNode */
typedef struct ConditionNode {
  ColumnNode *column;
  OprType opr_type;
  ValueItemNode *value;
  ConnType conn_type;
  struct ConditionNode *next;
  struct ConditionNode *left;
  struct ConditionNode *right;
  ConditionNodeType type;
} ConditionNode;

/* CreateTableNode */
typedef struct {
  char *table_name;
  ColumnDefSetNode *column_def_set_node;
  PrimaryKeyNode *primary_key_node;
} CreateTableNode;

/* SelectNode */
typedef struct {
  SelectItemsNode *select_items_node;
  char *table_name;
  ConditionNode *condition_node;
} SelectNode;

/* InsertNode */
typedef struct {
  bool all_column;
  char *table_name;
  ColumnSetNode *columns_set_node;
  ValueItemSetNode *value_item_set_node;
} InsertNode;

/* UpdateNode */
typedef struct {
  char *table_name;
  AssignmentSetNode *assignment_set_node;
  ConditionNode *condition_node;
} UpdateNode;

/* DeleteNode */
typedef struct {
  char *table_name;
  ConditionNode *condition_node;
} DeleteNode;

/* DescribeNode */
typedef struct {
  char *table_name;
} DescribeNode;

/* ShowNode */
typedef struct {
  ShowNodeType type;
} ShowNode;

/* ASTNode */
typedef struct {
  StatementType statement_type;
  union {
    CreateTableNode *create_table_node;
    SelectNode *select_node;
    InsertNode *insert_node;
    UpdateNode *update_node;
    DeleteNode *delete_node;
    DescribeNode *describe_node;
    ShowNode *show_node;
  };
} ASTNode;

/* InputBuffer */
typedef struct {
  char *input;
  size_t buffer_length;
  ssize_t input_length;
} InputBuffer;

/* NodeType */
typedef enum { LEAF_NODE, INTERNAL_NODE } NodeType;

/* StatementType */
typedef enum {
  STMT_CREATE_TABLE,
  STMT_SELECT,
  STMT_UPDATE,
  STMT_INSERT,
  STMT_DELETE,
  STMT_DESCRIBE,
  STMT_SHOW
} StamentType;

/* Statement */
typedef struct {
  StamentType statement_type;
  ASTNode *ast_node;
} Statement;

/* ExecuteResult */
typedef enum {
  EXECUTE_SUCCESS,
  EXECUTE_FAIL,
  EXECUTE_SQL_ERROR,
  EXECUTE_TABLE_EXIST_FAIL,
  EXECUTE_TABLE_CREATE_FAIL,
  EXECUTE_TABLE_DROP_FAIL,
  EXECUTE_TABLE_OPEN_FAIL,
  EXECUTE_DUPLICATE_KEY
} ExecuteResult;

/* Pager */
typedef struct {
  int file_descriptor;
  uint32_t file_length;
  uint32_t size;
  void *pages[MAX_TABLE_PAGE];
} Pager;

/* MetaColumn */
typedef struct {
  char column_name[MAX_COLUMN_NAME_LEN];
  DataType column_type;
  uint32_t column_length;
  bool is_primary;
} MetaColumn;

/* MetaTable */
typedef struct {
  char *table_name;
  MetaColumn *meta_column[MAX_COLUMN_SIZE];
  uint32_t column_size;
} MetaTable;

/* Table */
typedef struct {
  Pager *pager;
  uint32_t root_page_num;
  MetaTable *meta_table;
} Table;

/* Cursor */
typedef struct {
  Table *table;
  uint32_t page_num;
  uint32_t cell_num;
} Cursor;

/* KeyValue */
typedef struct {
  char *key;
  void *value;
  DataType data_type;
} KeyValue;

/* Row */
typedef struct {
  void *key;
  char *table_name;
  KeyValue **data;
  uint32_t column_len;
} Row;

/* QueryParam */
typedef struct {
  char *table_name;
  SelectItemsNode *select_items;
  ConditionNode *condition_node;
} QueryParam;

/* SelectResult */
typedef struct {
  char *table_name;
  uint32_t row_size;
  int32_t row_index;
  Row *max_row; /* The max row, used in funciton max. */
  Row *min_row; /* The min row, used in funciton min. */
  union {
    int32_t i;
    float f;
    double d;
  } sum; /* The sum value, used in function sum. */
} SelectResult;

/* TableList */
typedef struct {
  char **table_name_list;
  uint32_t count;
} TableList;

/* MEntry */
typedef struct MEntry {
  void *ptr;
  size_t size;
  char data_type_name[1024];
  struct MEntry *next;
} MEntry;

/* MHashTable */
typedef struct {
  MEntry **entry_list;
  uint32_t num;      /* number of entry list. */
  uint32_t capacity; /* capacity of table cell. */
} MHashTable;

/* Session */
typedef struct {
  int client;
  uint32_t frequency;
  uint32_t volumn;
} Session;

/* Abount configuration. */
typedef struct {
  char *data_dir; /* database file directory. */
  ushort port;    /* Server listening port. */
} Conf;

#endif
