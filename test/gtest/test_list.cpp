#include "gtest/gtest.h"

extern "C" {
#include "list.h"
#include "data.h"
#include "mmu.h"
}

/* Test for create list. */
TEST(list, create_list) {
    List *list = create_list(NODE_INT);
    ASSERT_NE(list, NIL);
    ASSERT_EQ(list->size, 0);
}

/* Test for enlarg list. */
TEST(list, enlarge_list) {
    List *list = create_list(NODE_INT);

    int i;
    for (i = 0; i < 30; i++) {
        append_list(list, &i);       
    }

    ASSERT_EQ(list->size, 30);
    ASSERT_EQ(list->capacity, 32);

    ListCell *lc;
    int j = 0;
    foreach (lc, list) {
        ASSERT_EQ(lfirst_int(lc), j);
        j++;
    }
}

TEST(list, append_list) {
    char* strings[10] = {
        "hello everyone!", 
        "¡Hola a todos!", 
        "大家好!", 
        "Bonjour à tous !", 
        "Guten Tag, alle zusammen!", 
        "Ciao a tutti!", 
        "Здравствуйте, все!", 
        "こんにちは、皆さん！", 
        " 여러분, 안녕하세요!", 
        "مرحباً جميعًا!" };
    
    List *list = create_list(NODE_STRING);
    for (int i = 0; i < 10; i++) {
        append_list(list, strings[i]);
    }
    
    ListCell *lc;
    int j = 0;
    foreach (lc, list) {
        ASSERT_STREQ((char *)lfirst(list_nth_cell(list, j)), strings[j]);
        j++;
    }
    ASSERT_EQ(j, 10);
}
/* Test for free list. */
TEST(list, free_list_deep) {

    List *list = create_list(NODE_COLUMN_DEF_NODE);

    int i;
    for (i = 0; i < 30; i++) {
        ColumnDefNode *node = instance(ColumnDefNode);
        append_list(list, node);       
    }

    free_list_deep(list);
}
