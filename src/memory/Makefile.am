
includedir = $(top_srcdir)/include

noinst_LIBRARIES = libmemory.a

libmemory_a_SOURCES = mmu.c cache.c buffer.c
libmemory_a_CFLAGS = -I$(includedir)/common -I$(includedir)/utils -I$(includedir)/memory -I$(includedir)/lock -I$(includedir)/trans
