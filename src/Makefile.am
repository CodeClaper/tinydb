BUILT_SOURCES = data.h
AM_YFLAGS = -d
if DEBUG
AM_CFLAGS = -g -O0 -w
else
AM_CFLAGS = -O2 -w
endif
LDADD = -lpthread
bin_PROGRAMS = tinydb \
			   tinydb_cli
tinydb_SOURCES = db.c asserts.c asserts.h cache.c cache.h check.c check.h common.h cond.c cond.h conf.c conf.h const.h \
				 copy.c copy.h create.c create.h data.h defs.h delete.c delete.h desc.c desc.h free.c free.h index.c index.h \
				 insert.c insert.h intpr.c intpr.h lex.yy.c lock.c lock.h log.c log.h mmu.c mmu.h meta.c meta.h \
				 misc.c misc.h node.c node.h opr.c opr.h pager.c pager.h refer.c refer.h select.c select.h server.c server.h \
				 session.c session.h show.c show.h stmt.c stmt.h table.c table.h parser.c parser.h update.c update.h utils.c utils.h y.tab.c y.tab.h
tinydb_cli_SOURCES = db_cli.c asserts.c asserts.h utils.c utils.h mmu.c mmu.h
tinydb_cli_LDADD = -lreadline -ltinfo
