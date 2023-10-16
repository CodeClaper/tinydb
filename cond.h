#include "data.h"
#include "./sql/intpr.h"

// generate the binary tree of condition
ConditionNode *tree(ConditionNode *head);

//Tree shound ignore the next node.
void clean_next(ConditionNode *head);
