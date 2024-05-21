
includedir = $(top_srcdir)/include

noinst_LIBRARIES = libbackend.a

libbackend_a_SOURCES = create.c delete.c desc.c drop.c insert.c json.c meta.c select.c server.c session.c show.c stmt.c update.c
libbackend_a_CFLAGS = -I$(includedir)/backend -I$(includedir)/storage -I$(includedir)/trans -I$(includedir)/backend \
				   -I$(includedir)/parser -I$(includedir)/lock -I$(includedir)/memory -I$(includedir)/utils  -I$(includedir)/common 
