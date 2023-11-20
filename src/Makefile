PROG=cache.c cond.c conf.c copy.c create.c desc.c free.c index.c input.c\
	 insert.c meta.c misc.c node.c opr.c pager.c select.c show.c stmt.c update.c delete.c\
	 table.c token.c utils.c server.c log.c check.c mem.c session.c\
	 lex.yy.c y.tab.c intpr.c 
PROMT=tinydb
CLIENT=tinydb-cli
CFLAGS=-w -lreadline -ltinfo
DFLAGS=-w -lreadline -ltinfo -g -D DEBUG

all: ${PROG}
	gcc ${PROG} db.c -o ${PROMT} ${CFLAGS}
	gcc db_cli.c input.c -o ${CLIENT} ${CFLAGS}
debug: ${PROG}
	gcc ${PROG} db.c -o ${PROMT} ${DFLAGS}
	gcc db_cli.c input.c -o ${CLIENT} ${DFLAGS}
sql: sql.y sql.l intpr.c
	lex sql.l
	yacc -d sql.y
info: ${PRMT}
	cloc ./
test: ${PROMT}
	gcc ./test/test_client.c -g -o ./test/test_client
install: 
	install tinydb /usr/bin 
clean:
	rm -r -f ${OBJECT} ${PROMT} ${CLIENT} 
.PHONY: sql
.PHONY: install
.PHONY: clean
