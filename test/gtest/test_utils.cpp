#include "gtest/gtest.h"
#include <cstddef>
#include <cstdint>

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

/* Test for stoi32. */
TEST(utils, stoi32) {
    int32_t ret;
    ASSERT_EQ(stoi32("121211213232323442322", &ret), -1);
    ASSERT_EQ(stoi32("1212asbaddd", &ret), 0);
    ASSERT_EQ(stoi32("124322787873871871983727462737647826737627", &ret), -1);
    ASSERT_EQ(stoi32("-1217284658497394738478324878437847288784744323", &ret), -1);
    ASSERT_EQ(stoi32("-882732832748329724959437223", &ret), -1);
    ASSERT_EQ(stoi32("-2372877477774837276372637627367263726376273627637263786273672637263762783", &ret), -1);
    ASSERT_EQ(stoi32("2327837473478374872837487487238472387483274872387482374823784723847823748358928482378547237482374823748", &ret), -1);
    ASSERT_EQ(stoi32("2147483648", &ret), -1);
    ASSERT_EQ(stoi32("2147483647", &ret), 1);
    ASSERT_EQ(ret, 2147483647);
    ASSERT_EQ(stoi32("-2147483648", &ret), 1);
    ASSERT_EQ(ret, -2147483648);
    ASSERT_EQ(stoi32("232873823", &ret), 1);
    ASSERT_EQ(ret, 232873823);
    ASSERT_EQ(stoi32("-2337827", &ret), 1);
    ASSERT_EQ(ret, -2337827);
    ASSERT_EQ(stoi32("-1122323233", &ret), 1);
    ASSERT_EQ(ret, -1122323233);
}


/* Test for stoi64. */
TEST(utils, stoi64) {
    int64_t ret;
    ASSERT_EQ(stoi64("121211213232323442322", &ret), -1);
    ASSERT_EQ(stoi64("1212asbaddd", &ret), 0);
    ASSERT_EQ(stoi64("124322787873871871983727462737647826737627", &ret), -1);
    ASSERT_EQ(stoi64("-1217284658497394738478324878437847288784744323", &ret), -1);
    ASSERT_EQ(stoi64("-882732832748329724959437223", &ret), -1);
    ASSERT_EQ(stoi64("-2372877477774837276372637627367263726376273627637263786273672637263762783", &ret), -1);
    ASSERT_EQ(stoi64("2327837473478374872837487487238472387483274872387482374823784723847823748358928482378547237482374823748", &ret), -1);
    ASSERT_EQ(stoi64("9223372036854775808", &ret), -1);
    ASSERT_EQ(stoi64("9223372036854775807", &ret), 1);
    ASSERT_EQ(ret, 9223372036854775807);
    ASSERT_EQ(stoi64("-9223372036854775808", &ret), 1);
    ASSERT_EQ(ret, -9223372036854775808);
    ASSERT_EQ(stoi64("232873823", &ret), 1);
    ASSERT_EQ(ret, 232873823);
    ASSERT_EQ(stoi64("-2337827", &ret), 1);
    ASSERT_EQ(ret, -2337827);
    ASSERT_EQ(stoi64("-1122323233", &ret), 1);
    ASSERT_EQ(ret, -1122323233);
}
