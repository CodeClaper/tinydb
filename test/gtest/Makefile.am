# TESTS -- Programs run automatically by "make check"
# check_PROGRAMS -- Programs built by "make check" but not necessarily run
TESTS = gtest
check_PROGRAMS = gtest

gtest_LDADD = -lgtest_main -lgtest
gtest_SOURCES = main.cpp test_spinlock.cpp
gtest_LDFLAGS = -pthread
gtest_CPPFLAGS = -w -I/usr/src/googletest/googletest/include -I/usr/src/googletest/googletest -I$(top_srcdir)/include/lock -I$(top_srcdir)/include/common -pthread



