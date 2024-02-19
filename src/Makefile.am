BUILT_SOURCES = ../include/data.h
AM_YFLAGS = -d
if DEBUG
AM_CFLAGS = -g -O0 -w -I../include/
else
AM_CFLAGS = -O2 -w -I../include/
endif
LDADD = -lpthread -lm
bin_PROGRAMS = tinydb \
			   tinydb_cli
tinydb_SOURCES = db.c asserts.c asserts.h buffer.c buffer.h cache.c cache.h check.c check.h common.h conf.c conf.h const.h \
				 copy.c copy.h create.c create.h data.h defs.h delete.c delete.h desc.c desc.h free.c free.h gc.c gc.h index.c index.h \
				 insert.c insert.h intpr.c intpr.h lex.yy.c rwlock.c rwlock.h log.c log.h mmu.c mmu.h meta.c meta.h \
				 ltree.c ltree.h compare.c compare.h pager.c pager.h refer.c refer.h ret.c ret.h select.c select.h \
				 server.c server.h session.c session.h show.c show.h stmt.c stmt.h table.c table.h timer.c timer.h trans.c trans.h \
				 parser.c parser.h update.c update.h utils.c utils.h xlog.c xlog.h y.tab.c y.tab.h 
tinydb_cli_SOURCES = db_cli.c 
tinydb_cli_LDADD = -lreadline -ltinfo
