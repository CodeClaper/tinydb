
includedir = $(top_srcdir)/include

noinst_LIBRARIES = libstorage.a

libstorage_a_SOURCES = gc.c ltree.c pager.c table.c
libstorage_a_CFLAGS = -I$(includedir)/common -I$(includedir)/memory -I$(includedir)/utils -I$(includedir)/storage \
					  -I$(includedir)/trans -I$(includedir)/stmt
