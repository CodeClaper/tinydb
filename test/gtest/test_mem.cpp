#include "gtest/gtest.h"
#include <cstdio>
#include <stdint.h>
#include <string.h>

extern "C" {
#include "data.h"
#include "mem.h"
}

/* Test for mmalloc. */
TEST(mem, mmalloc) {
    start_allocator();
    int *col[100];
    for (int i = 0; i < 100; i++) {
        int *ptr = (int *)mmalloc(sizeof(int));
        memcpy(ptr, &i, sizeof(int));
        col[i] = ptr;
    }

    for (int i = 0; i < 100; i++) {
        ASSERT_EQ(*col[i], i);
    }
    end_allocator();
}

/* Test for mfree*/
TEST(mem, mfree) {
    start_allocator();
    int64_t *col1[100];
    int32_t *col2[100];
    for (int64_t i = 0; i < 100; i++) {
        int64_t *ptr = (int64_t *)mmalloc(sizeof(int64_t));
        int64_t c = (int64_t) i;
        memcpy(ptr, &c, sizeof(int));
        col1[i] = ptr;
    }
    for (int i = 0; i < 100; i++) {
        mfree(col1[i]);
    }


    for (int32_t i = 0; i < 100; i++) {
        int32_t *ptr = (int32_t *)mmalloc(sizeof(int32_t));
        memcpy(ptr, &i, sizeof(int32_t));
        col2[i] = ptr;
    }

    for (int i = 0; i < 100; i++) {
        ASSERT_EQ(*col2[i], i);
    }

    end_allocator();
}

/* Test for mrealloc, case 1 */
TEST(mem, mrealloc) {
    start_allocator();
    int *ptr = (int *)mmalloc(0);
    for (int i = 0; i < 100; i++) {
        ptr = (int *)mrealloc(ptr, sizeof(int *) * (i + 1));
        ptr[i] = i;
    }

    for (int i = 0; i < 100; i++)
        ASSERT_EQ(ptr[i], i);

    end_allocator();
}

/* Test for mrealloc, case 2 */
TEST(mem, mrealloc2) {

    int *ptr = (int *)mmalloc(0);
    for (int i = 0; i < 10; i++) {
        ptr = (int *)mrealloc(ptr, sizeof(int *) * (i + 1));
        ptr[i] = i;
    }

    start_allocator();
    for (int i = 10; i < 100; i++) {
        ptr = (int *)mrealloc(ptr, sizeof(int *) * (i + 1));
        ptr[i] = i;
    }

    for (int i = 0; i < 100; i++)
        ASSERT_EQ(ptr[i], i);

    end_allocator();
}


/* Test for mrealloc, case 3 */
TEST(mem, mrealloc3) {
    start_allocator();
    int *ptr = (int *)mmalloc(0);
    for (int i = 0; i < 100; i++) {
        ptr = (int *)mrealloc(ptr, sizeof(int *) * (i + 1));
        ptr[i] = i;
    }

    for (int i = 100; i >=10 ; i--) {
        ptr = (int *)mrealloc(ptr, sizeof(int *) * (i));
    }

    for (int i = 0; i < 10 ; i++) {
        ASSERT_EQ(ptr[i], i);
    }
    end_allocator();
}


TEST(mem, mstrdup) {
    start_allocator();
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
        "مرحباً جميعًا!" 
    };

    char *array[10];
    
    for (int i = 0; i < 10; i++) {
         array[i] = mstrdup(strings[i]) ;      
    }

    for (int i = 0; i < 10; i++) {
        ASSERT_STREQ(array[i], strings[i]);
    }

    end_allocator();
}

