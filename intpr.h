#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#ifndef INTPR_H
#define INTPR_H
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

typedef enum {
  CREATE_TABLE_STMT,
  SELECT_STMT,
  INSERT_STMT,
  UPDATE_STMT,
  DELETE_STMT,
  DESCRIBE_STMT,
  SHOW_TABLES_STMT
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

typedef enum { LOGIC_CONDITION, EXEC_CONDITION } ConditionNodeType;

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
} DescribeNode;

typedef struct {

} ShowTablesNode;

typedef struct {
  StatementType statement_type;
  union {
    CreateTableNode *create_table_node;
    SelectNode *select_node;
    InsertNode *insert_node;
    DescribeNode *describe_node;
    ShowTablesNode *show_tables_node;
  };
} ASTNode;


// make a function value node.
FunctionValueNode *make_function_value_node();

// make a functon node
FunctionNode *make_function_node();

// make a select items node.
SelectItemsNode *make_select_items_node();

// make a select node.
SelectNode *make_select_node();

// make a column node.
ColumnNode *make_column_node();

// make a column set node.
ColumnSetNode *make_column_set_node();

// add column node to set.
void add_column_to_set(ColumnSetNode *column_set_node, ColumnNode *column_node);

// make a condition node.
ConditionNode *make_cond_node();

// make a create table node.
CreateTableNode *make_create_table_node();

// make a value item node.
ValueItemNode *make_value_item_node();

// make a value item set node.
ValueItemSetNode *make_value_item_set_node();

// add value item into set.
void add_value_item(ValueItemSetNode *node, ValueItemNode *value_item_node);

// make an insert node.
InsertNode *make_insert_node();

// make a column def node.
ColumnDefNode *make_column_def_node();

// make a column def set node.
ColumnDefSetNode *make_column_def_set_node();

// make a primary key node.
PrimaryKeyNode *make_primary_key_node();

// add column def node to set.
void add_column_def_to_set(ColumnDefSetNode *columns_def_set_node, ColumnDefNode *column_def_node);

// make a describe node.
DescribeNode *make_describe_node();

// make a shwo table node.
ShowTablesNode *make_show_tables_node();

// set ASTNode;
void set_select_ast_node(SelectNode *select_node);

// set ASTNode;
void set_insert_ast_node(InsertNode *insert_node);

// set ASTNode
void set_create_table_ast_node(CreateTableNode *create_table_node);

// set describe node ASTNode.
void set_describe_ast_node(DescribeNode *describe_node);

// set show tables node ASTNode.
void set_show_tables_ast_node(ShowTablesNode *show_table_node);

// get an ASTNode
ASTNode *get_ast_node();

#endif
