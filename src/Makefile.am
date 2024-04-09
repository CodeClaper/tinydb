BUILT_SOURCES = ../include/data.h
AM_YFLAGS = -d
if DEBUG
AM_CFLAGS = -g -O0 -I../include/
else
AM_CFLAGS = -O2 -I../include/
endif
LDADD = -lpthread -lm

include_HEADERS= ../include/asserts.h ../include/buffer.h ../include/cache.h ../include/check.h ../include/common.h \
				 ../include/conf.h ../include/const.h ../include/copy.h ../include/create.h ../include/data.h ../include/defs.h \
				 ../include/delete.h ../include/desc.h ../include/free.h ../include/gc.h ../include/index.h ../include/insert.h \
				 ../include/intpr.h ../include/rwlock.h ../include/log.h ../include/mmu.h ../include/meta.h ../include/ltree.h \
				 ../include/compare.h ../include/pager.h ../include/refer.h ../include/ret.h ../include/select.h ../include/server.h \
				 ../include/session.h ../include/show.h ../include/spinlock.h ../include/stmt.h ../include/table.h ../include/timer.h ../include/trans.h \
				 ../include/parser.h ../include/update.h ../include/utils.h ../include/xlog.h  y.tab.h

bin_PROGRAMS = tinydb \
			   tinydb_cli

tinydb_SOURCES = db.c asserts.c  buffer.c  cache.c  check.c conf.c \
				 copy.c  create.c delete.c  desc.c free.c  gc.c index.c \
				 insert.c  intpr.c lex.yy.c rwlock.c log.c mmu.c meta.c \
				 ltree.c compare.c pager.c refer.c ret.c select.c \
				 server.c  session.c show.c spinlock.c stmt.c  table.c timer.c trans.c \
				 parser.c update.c utils.c xlog.c y.tab.c 
tinydb_cli_SOURCES = db_cli.c 
tinydb_cli_LDADD = -lreadline -ltinfo
