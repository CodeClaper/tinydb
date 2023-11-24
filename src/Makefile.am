BUILT_SOURCES = data.h
CFLAGS = -w
AM_YFLAGS = -d
if DEBUG
AM_CFLAGS = -g3 -O0
else
AM_CFLAGS = -O2
endif
LDADD = -lpthread
bin_PROGRAMS = tinydb \
			   tinydb_cli
tinydb_SOURCES = db.c cache.c cache.h check.c check.h common.h cond.c cond.h  conf.c conf.h const.h \
				 copy.c copy.h create.c create.h data.h defs.h delete.c delete.h desc.c desc.h free.c free.h index.c index.h \
				 insert.c insert.h intpr.c intpr.h lex.yy.c log.c log.h mem.c mem.h meta.c meta.h \
				 misc.c misc.h node.c node.h opr.c opr.h pager.c pager.h select.c select.h server.c server.h session.c session.h \
				 show.c show.h stmt.c stmt.h table.c table.h token.c token.h update.c update.h utils.c utils.h y.tab.c y.tab.h
tinydb_cli_SOURCES = db_cli.c utils.c utils.h mem.c mem.h
tinydb_cli_LDADD = -lreadline -ltinfo
