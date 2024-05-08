
includedir = $(top_srcdir)/include

noinst_LIBRARIES = libtrans.a

libtrans_a_SOURCES = trans.c xlog.c
libtrans_a_CFLAGS = -I$(includedir)/common -I$(includedir)/memory -I$(includedir)/utils -I$(includedir)/trans \
					-I$(includedir)/storage -I$(includedir)/backend
