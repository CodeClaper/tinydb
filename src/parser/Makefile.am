
includedir = $(top_srcdir)/include

noinst_LIBRARIES = libparser.a

libparser_a_SOURCES = intpr.c parser.c lex.yy.c y.tab.c y.tab.h
libparser_a_CFLAGS = -I$(includedir)/common  -I$(includedir)/parser -I$(includedir)/memory -I$(includedir)/utils
