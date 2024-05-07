
includedir = $(top_srcdir)/include

noinst_LIBRARIES = liblock.a

liblock_a_SOURCES = rwlock.c spinlock.c
liblock_a_CFLAGS = -I$(includedir)/common -I$(includedir)/utils -I$(includedir)/lock -I$(includedir)/memory -I$(includedir)/storage
