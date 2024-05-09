
includedir = $(top_srcdir)/include

noinst_LIBRARIES = libcommon.a

libcommon_a_SOURCES = asserts.c check.c compare.c conf.c  index.c list.c log.c refer.c 

libcommon_a_CFLAGS = -I$(includedir)/common -I$(includedir)/utils -I$(includedir)/memory \
					 -I$(includedir)/storage -I$(includedir)/trans  -I$(includedir)/backend
