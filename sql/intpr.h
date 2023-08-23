#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

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
    C_AND,
    C_OR
} ConnType; // connector type

typedef enum {
    SELECT_STMT,
    INSERT_STMT,
    UPDATE_STMT,
    DELETE_STMT
} StatementType; // statement type

typedef struct {
    int i_value;
}ConstNode; 

typedef struct {
    char *name;
}IdentNode;

typedef struct {
    ConnType conn_type;
} ConnNode;

typedef struct {
   OpType op_type;  
} OprNode;

typedef struct {
    IdentNode **ident_node;
    uint32_t num;
}IdentSetNode;

typedef struct {
    IdentSetNode *ident_set_node;
}SelectItemsNode;

typedef struct {
    IdentSetNode *ident_set_node;
}ColumnSetNode;

typedef struct {
   union {
      ConstNode *i_value;
      IdentNode *s_value;
   };
}ValueItemNode;

typedef struct {
    ValueItemNode **value_item_node;
    uint32_t num;
}ValueItemSetNode;

typedef struct {
    IdentNode *table;
}FromItemNode;


typedef struct S_ConditionNode {
    IdentNode *column; 
    OprNode *opr_node;
    ConnNode *conn_node;
    struct S_ConditionNode *next;
} ConditionNode;

typedef struct {
    SelectItemsNode *select_items_node; 
    FromItemNode *from_item_node;
    ConditionNode *condition_node;
}SelectNode;

typedef struct { 
    bool if_ignore_columns;
    FromItemNode *from_item_node;
    ColumnSetNode *columns_set_node; 
    ValueItemSetNode *value_item_set_node;
}InsertNode;

typedef struct {
    StatementType statement_type;
    union {
        SelectNode *select_node;
        InsertNode *insert_node;
    };
}ASTNode;

// make a const node.
ConstNode *make_const_node(int i);

// make an ident node.
IdentNode *make_ident_node(char *s);

// make an ident set node.
IdentSetNode *make_ident_set_node();

// add a new ident node to set
void add_ident(IdentSetNode *ident_set_node, IdentNode *ident_node);

// make a from item node.
FromItemNode *make_from_item_node();

// make a select items node.
SelectItemsNode *make_select_items_node();

// make a select node.
SelectNode *make_select_node();

// graph select node tree
void graph(SelectNode *select_node);

// set ASTNode;
void set_select_ast_node(SelectNode *select_node);

// make a column set node.
ColumnSetNode *make_column_set_node();

// make a condition node.
ConditionNode *make_cond_node();

// make a operator node.
OprNode *make_opr_node(OpType op_type);

// make a connnection node.
ConnNode *make_conn_node(ConnType conn_type);

// make a value item node.
ValueItemNode *make_value_item_node();

// make a value item set node.
ValueItemSetNode *make_value_item_set_node();

// add value item into set.
void add_value_item(ValueItemSetNode *node, ValueItemNode *value_item_node);

// make an insert node.
InsertNode *make_insert_node();

// set ASTNode;
void set_insert_ast_node(InsertNode *insert_node);

// get an ASTNode
ASTNode *get_ast_node();

// free ast node memory.
void free_ast_node(ASTNode *node);

#endif
