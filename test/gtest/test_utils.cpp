#include "gtest/gtest.h"
#include <cstddef>

extern "C" {
#include "data.h"
#include "mmu.h"
#include "utils.h"
}

/* Test for ltrim. */
TEST(utils, ltrim) {
    char *string = db_strdup("  hello");
    ASSERT_STREQ(ltrim(string), "hello");
}

/* Test for ltrim. */
TEST(utils, rtrim) {
    char *string = db_strdup("hello  ");
    ASSERT_STREQ(rtrim(string), "hello");
}

/* Test for trim. */
TEST(utils, trim) {
    char *string = db_strdup("  hello  ");
    ASSERT_STREQ(trim(string), "hello");
}

/* Test for contains. */
TEST(utils, contains) {
    ASSERT_TRUE(contains("hello world", "ello"));
    ASSERT_FALSE(contains("hello world", "war"));
}

/* Test for startwith. */
TEST(utils, startwith) {
    ASSERT_TRUE(startwith("hello world", "hello"));
    ASSERT_FALSE(startwith("hello world", "world"));
}

/* Test for startwith. */
TEST(utils, endwith) {
    ASSERT_TRUE(endwith("hello world", "world"));
    ASSERT_FALSE(endwith("hello world", "hello"));
}

/* Test for substr. */
TEST(utils, substr) {
    ASSERT_STREQ(substr("hello world", 2, 4), "llo");
    ASSERT_STREQ(substr("hello world", 1, 7), "ello wo");
}

/* Test for replace_onece. */
TEST(utils, replace_onece) {
    ASSERT_STREQ(replace_once("hello world", "world", "nihao"), "hello nihao");
}

/* Test for replace. */
TEST(utils, replace_all) {
    ASSERT_STREQ(replace_all("There are a hundred Hamlets in a hundred people's eyes", "hundred", "thousand"), 
                 "There are a thousand Hamlets in a thousand people's eyes");
    ASSERT_STREQ(replace_all("There are a thousand Hamlets in a thousand people's eyes", "thousand", "hundred"), 
                 "There are a hundred Hamlets in a hundred people's eyes");
}

/* Test for is_empty. */
TEST(utils, is_empty) {
    ASSERT_TRUE(is_empty(NULL));
    ASSERT_TRUE(is_empty(""));
    ASSERT_TRUE(is_empty("  "));
    ASSERT_FALSE(is_empty("\t"));
    ASSERT_FALSE(is_empty("\v"));
    ASSERT_FALSE(is_empty("\n"));
    ASSERT_FALSE(is_empty("\r"));
}

/* Test for format. */
TEST(utils, format) {
    ASSERT_STREQ(format("hello, %s!", "everyone"), "hello, everyone!");
    ASSERT_STREQ(format("%d percents", 100), "100 percents");
    ASSERT_STREQ(format("%0.1f kilometers left", 2.5), "2.5 kilometers left");
}

/* Test for streq. */
TEST(utils, streq) {
    ASSERT_TRUE(streq("hello", "hello"));
    ASSERT_FALSE(streq("hello", "nihao"));
    ASSERT_FALSE(streq("hello", NULL));
    ASSERT_FALSE(streq(NULL, NULL));
}

/* Test for streq. */
TEST(utils, streq_or_null) {
    ASSERT_TRUE(streq_or_null("hello", "hello"));
    ASSERT_FALSE(streq_or_null("hello", "nihao"));
    ASSERT_FALSE(streq_or_null("hello", NULL));
    ASSERT_TRUE(streq_or_null(NULL, NULL));
}

/* Test for itos. */
TEST(utils, itos) {
    ASSERT_STREQ(itos(32), "32");
    ASSERT_STRNE(itos(61), "32");
}

/* Test for ltos. */
TEST(utils, ltos) {
    ASSERT_STREQ(ltos(1302323), "1302323");
    ASSERT_STREQ(ltos(662323232), "662323232");
}

/* Test for ftos*/
TEST(utils, ftos) {
    ASSERT_STREQ(ftos(3.14), "3.140000");
    ASSERT_STREQ(ftos(6.68232), "6.682320");
}


/* Test for dtos*/
TEST(utils, dtos) {
    ASSERT_STREQ(dtos(3.14159265358979323846264338327950288419716939937510), "3.141592653589793");
}
