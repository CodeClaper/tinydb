#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

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
} OpType; // operator type

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

typedef enum { V_INT, V_IDENT, V_ALL } FunctionValueType; // value type.

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
  int i_value;
} IntValueNode;

typedef struct {
  char *s_value;
} StringValueNode;

typedef struct {
  char *name;
} IdentNode;

typedef struct {
  FunctionValueType value_type;
  union {
    IntValueNode *i_value;
    IdentNode *id_value;
  };
} FunctionValueNode;

typedef struct {
  FunctionType function_type;
  FunctionValueNode *value;
} FunctionNode;

typedef struct {
  ConnType conn_type;
} ConnNode;

typedef struct {
  DataType data_type;
} DataTypeNode;

typedef struct {
  OpType op_type;
} OprNode;

typedef struct {
  bool all_column;
  IdentNode **ident_node;
  uint32_t num;
} IdentSetNode;

typedef struct {
  IdentSetNode *ident_set_node;
  FunctionNode *function_node;
  bool is_function_node;
} SelectItemsNode;

typedef struct {
  IdentNode *column_name;
  DataTypeNode *column_type;
} ColumnDefNode;

typedef struct {
  ColumnDefNode **column_def;
  uint32_t column_size;
} ColumnDefSetNode;

typedef struct {
  IdentNode *primary_key_column;
} PrimaryKeyNode;

typedef struct {
  IdentSetNode *ident_set_node;
} ColumnSetNode;

typedef struct {
  DataType data_type;
  union {
    IntValueNode *i_value;
    StringValueNode *s_value;
  };
} ValueItemNode;

typedef struct {
  ValueItemNode **value_item_node;
  uint32_t num;
} ValueItemSetNode;

typedef struct {
  IdentNode *table;
} FromItemNode;

typedef enum { LOGIC_CONDITION, EXEC_CONDITION } ConditionNodeType;

typedef struct ConditionNode {
  IdentNode *column;
  OprNode *opr_node;
  ValueItemNode *compare;
  ConnNode *conn_node;
  struct ConditionNode *next;
  struct ConditionNode *left;
  struct ConditionNode *right;
  ConditionNodeType type;
} ConditionNode;

typedef struct {
  IdentNode *table_name;
  ColumnDefSetNode *column_def_set_node;
  PrimaryKeyNode *primary_key_node;
} CreateTableNode;

typedef struct {
  SelectItemsNode *select_items_node;
  FromItemNode *from_item_node;
  ConditionNode *condition_node;
} SelectNode;

typedef struct {
  bool if_ignore_columns;
  FromItemNode *from_item_node;
  ColumnSetNode *columns_set_node;
  ValueItemSetNode *value_item_set_node;
} InsertNode;

typedef struct {
  FromItemNode *from_item_node;
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

// make an int value node.
IntValueNode *make_int_value_node(int i);

// make a string value node.
StringValueNode *make_string_value_node(char *s);

// make an ident node.
IdentNode *make_ident_node(char *s);

// make an ident set node.
IdentSetNode *make_ident_set_node();

// add a new ident node to set
void add_ident(IdentSetNode *ident_set_node, IdentNode *ident_node);

// make a function value node.
FunctionValueNode *make_function_value_node();

// make a functon node
FunctionNode *make_function_node();

// make a from item node.
FromItemNode *make_from_item_node();

// make a select items node.
SelectItemsNode *make_select_items_node();

// make a select node.
SelectNode *make_select_node();

// make a column set node.
ColumnSetNode *make_column_set_node();

// make a condition node.
ConditionNode *make_cond_node();

// make a operator node.
OprNode *make_opr_node(OpType op_type);

// make a connnection node.
ConnNode *make_conn_node(ConnType conn_type);

// make a data type node.
DataTypeNode *make_data_type_node(DataType data_type);

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
void add_column_def_to_set(ColumnDefSetNode *columns_def_set_node,
                           ColumnDefNode *column_def_node);

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

// free ast node memory.
void free_ast_node(ASTNode *node);

#endif
