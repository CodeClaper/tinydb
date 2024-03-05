# TESTS -- Programs run automatically by "make check"
# check_PROGRAMS -- Programs built by "make check" but not necessarily run
TESTS = gtest
check_PROGRAMS = gtest

gtest_LDADD = -lgtest_main -lgtest
gtest_SOURCES = main.cpp spinlock_test.cpp
gtest_LDFLAGS = -pthread
gtest_CPPFLAGS = -w -I/usr/src/googletest/googletest/include -I/usr/src/googletest/googletest -I$(top_srcdir)/src -pthread



