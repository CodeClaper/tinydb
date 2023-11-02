#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <ctype.h>
#include <stddef.h>

#ifndef DATA_H
#define DATA_H
#define PAGE_SIZE 4096
#define MAX_TABLE_PAGE 100
#define MAX_COLUMN_SIZE 25 // max column size
#define MAX_COLUMN_NAME_LEN 30 // max column name length
#define BUFF_SIZE 1024

#define MAX_COLUMN_SIZE 25
#define MAX_COLUMN_NAME_LEN 30 // max column name length

typedef enum {
  O_EQ,
  O_NE,
  O_GT,
  O_GE,
  O_LT,
  O_LE,
  O_IN,
  O_LIKE
} OprType; // operator type

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

typedef enum { F_COUNT, F_MAX, F_MIN, F_SUM, F_AVG } FunctionType;

typedef enum { C_OR, C_AND } ConnType; // connector type

typedef enum { V_INT, V_COLUMN, V_ALL } FunctionValueType; // value type.

typedef enum { SELECT_COLUMNS, SELECT_FUNCTION, SELECT_ALL} SelectItemType;

typedef enum { LOGIC_CONDITION, EXEC_CONDITION } ConditionNodeType;

typedef enum { SHOW_TABLES, SHOW_MEMORY } ShowNodeType;

typedef enum {
  CREATE_TABLE_STMT,
  SELECT_STMT,
  INSERT_STMT,
  UPDATE_STMT,
  DELETE_STMT,
  DESCRIBE_STMT,
  SHOW_STMT
} StatementType; // statement type

typedef struct {
    char *column_name;
    bool exist_table_name;
    char *table_name;
}ColumnNode;

typedef struct {
    ColumnNode **columns;
    uint32_t size;
} ColumnSetNode;

typedef struct {
  FunctionValueType value_type;
  union {
    int32_t i_value;
    ColumnNode *column;
  };
} FunctionValueNode;

typedef struct {
  FunctionType function_type;
  FunctionValueNode *value;
} FunctionNode;


typedef struct {
    ColumnSetNode *column_set_node;
    FunctionNode *function_node;
    SelectItemType type;
} SelectItemsNode;

typedef struct {
    ColumnNode *column;
    DataType data_type;
    bool is_primary;
    bool allow_null;
} ColumnDefNode;

typedef struct {
  ColumnDefNode **column_defs;
  uint32_t size;
} ColumnDefSetNode;

typedef struct {
  ColumnNode *column;
} PrimaryKeyNode;

typedef struct {
  DataType data_type;
  union {
    int i_value;
    bool b_value;
    char *s_value;
    char c_value;
    float f_value;
    double d_value;
    time_t t_value;
  };
} ValueItemNode;

typedef struct {
  ValueItemNode **value_item_node;
  uint32_t num;
} ValueItemSetNode;

typedef struct {
   ColumnNode *column; 
   ValueItemNode *value;
}AssignmentNode;

typedef struct {
    AssignmentNode **assignment_node;
    uint32_t num;
}AssignmentSetNode;

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

typedef struct {
  char *table_name;
  ColumnDefSetNode *column_def_set_node;
  PrimaryKeyNode *primary_key_node;
} CreateTableNode;

typedef struct {
  SelectItemsNode *select_items_node;
  char *table_name;
  ConditionNode *condition_node;
} SelectNode;

typedef struct {
   bool all_column;
   char *table_name;
   ColumnSetNode *columns_set_node;
   ValueItemSetNode *value_item_set_node;
} InsertNode;

typedef struct {
   char *table_name; 
   AssignmentSetNode *assignment_set_node;
   ConditionNode *condition_node;
} UpdateNode;

typedef struct {
    char *table_name;
    ConditionNode *condition_node;
}DeleteNode;

typedef struct {
    char *table_name;
} DescribeNode;

typedef struct {
    ShowNodeType type;
} ShowNode;

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
    STMT_SHOW
}StamentType;

typedef struct {
    StamentType statement_type;
    ASTNode *ast_node;
}Statement;

typedef enum {
    EXECUTE_SUCCESS,
    EXECUTE_FAIL,
    EXECUTE_SQL_ERROR,
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
    DataType data_type;
}KeyValue;

typedef struct {
    void *key;
    char *table_name;
    KeyValue **data;
    uint32_t column_len;
}Row;

typedef struct {
    char *table_name;
    SelectItemsNode *select_items;
    ConditionNode *condition_node;
}QueryParam;

typedef struct {
    char *table_name;
    Row **row;
    uint32_t row_size;
}SelectResult;

typedef struct {
    char *json_data;
    char *message;
    uint32_t buffer_size;
    ExecuteResult result;
    char duration[1024];
}Output;

typedef struct {
    char **table_name_list;
    uint32_t count;
}TableList;

typedef struct MEntry {
    void *ptr;
    size_t size;
    char data_type_name[1024];
    struct MEntry *next;
}MEntry;

typedef struct {
    MEntry **entry_list;
    uint32_t num; // number of entry list.
    uint32_t capacity; // lenght of table cell.
}MHashTable;

#endif
