#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cond.h"
#include "mmu.h"
#include "common.h"
#include "copy.h"
#include "asserts.h"

static ConnType find_conn_type(ConditionNode *condition_node);

/* Find the highest priority node. */
static ConditionNode *find_highest_priority_node(ConditionNode *current, ConditionNode *highest_node) {
    if (find_conn_type(current) >= find_conn_type(highest_node))
        highest_node = current;
    if (current->next == NULL || current->next->next == NULL)
        return highest_node;
    return find_highest_priority_node(current->next, highest_node);
}

/* Find the conn type when bin tree. */
static ConnType find_conn_type(ConditionNode *condition_node) {
    assert_not_null(condition_node, "Conditon node cant`t be null in method [find_conn_type]");
    switch(condition_node->type) {
        case LOGIC_CONDITION:
            return find_conn_type(condition_node->right);
        case EXEC_CONDITION:
            return condition_node->conn_type;
    }
}

/* Binary tree */
static ConditionNode *binary_tree(ConditionNode *left, ConditionNode *right) {
    ConditionNode *condition_node = db_malloc(sizeof(ConditionNode), SDT_CONDITION_NODE);
    condition_node->type = LOGIC_CONDITION;
    condition_node->conn_type =find_conn_type(left);
    condition_node->left = left;
    condition_node->right = right;
    left = NULL;
    right = NULL;
    return condition_node;
}

/* Replace old node with new node. */
static ConditionNode *replace(ConditionNode *conditon_node, ConditionNode *old_node, ConditionNode *new_node) {
    if (conditon_node == old_node) {
        new_node->next = old_node->next->next;
        return new_node;
    }
    ConditionNode *head, *pre, *current;
    head = conditon_node;
    pre = conditon_node;
    current = conditon_node;
    while((current = current->next)) {
        if (current == old_node) {
            new_node->next = current->next->next;
            pre->next = new_node;
        }
        pre = current;
    }
    return head;
}

/* Generate the binary tree of condition */
ConditionNode *tree(ConditionNode *head) {
    if (head == NULL)
        return NULL;
    if (head->next == NULL)
        return head;
    ConditionNode *highest = find_highest_priority_node(head, head);
    ConditionNode *merge = binary_tree(highest, highest->next); // merge highest node ant it`s next
    ConditionNode *change = replace(head, highest, merge);
    return tree(change);
}

/* Tree shound ignore the next node. */
void clean_next(ConditionNode *head) {
    if (head) {
        if (head->left) 
            clean_next(head->left);
        if (head->right)
            clean_next(head->right);
        if (head->next)
            head->next = NULL;
    }
}
