
includedir = $(top_srcdir)/include

noinst_LIBRARIES = libmemory.a

libmemory_a_SOURCES = buffer.c cache.c copy.c free.c  mem.c mmu.c
libmemory_a_CFLAGS = -I$(includedir)/common -I$(includedir)/utils -I$(includedir)/memory -I$(includedir)/lock -I$(includedir)/trans -I$(includedir)/storage
