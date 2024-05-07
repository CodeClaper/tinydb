
includedir = $(top_srcdir)/include

noinst_LIBRARIES = libstmt.a

libstmt_a_SOURCES = create.c delete.c desc.c insert.c json.c meta.c select.c server.c session.c show.c stmt.c update.c
libstmt_a_CFLAGS = -I$(includedir)/stmt -I$(includedir)/storage -I$(includedir)/trans -I$(includedir)/backend \
				   -I$(includedir)/parser -I$(includedir)/lock -I$(includedir)/memory -I$(includedir)/utils  -I$(includedir)/common 
