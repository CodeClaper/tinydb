#include "../mem.h"
#include "../data.h"
#include <stdio.h>

MTable *mtable;

int main(void) {
    mtable = sys_malloc(sizeof(MTable));
    mtable->entry_list = sys_malloc(0);
    mtable->num = 0;
    ASTNode *node = db_malloc(sizeof(ASTNode));
    printf("%ld\n", db_memesize());
    node->select_node = db_malloc(sizeof(SelectNode));
    node->statement_type = SELECT_STMT;
    printf("%ld\n", db_memesize());
    db_free(node->select_node);
    printf("%ld\n", db_memesize());
    db_free(node);
    printf("%ld\n", db_memesize());
}
