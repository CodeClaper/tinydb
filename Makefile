PROG=cache.c cond.c conf.c copy.c create.c desc.c free.c index.c input.c\
	 insert.c meta.c misc.c node.c opr.c output.c pager.c row.c select.c show.c stmt.c\
	 table.c token.c utils.c server.c log.c\
	 ./sql/lex.yy.c ./sql/y.tab.c ./sql/intpr.c 
PROMT=tinydb
CLIENT=tinydb-cli
CFLAGS=-w -lreadline -ltinfo
DFLAGS=-w -lreadline -ltinfo -g -D DEBUG

tinydb: ${PROG}
	gcc ${PROG} main.c -o ${PROMT} ${CFLAGS}
	gcc client.c input.c -o ${CLIENT} ${CFLAGS}
debug: ${PROG}
	gcc ${PROG} main.c -o ${PROMT} ${DFLAGS}
	gcc client.c input.c -o ${CLIENT} ${DFLAGS}
info: ${PRMT}
	cloc ./
test: ${PROMT}
	gcc ./test/test_client.c -g -o ./test/test_client
install: tinydb
	install tinydb /usr/bin 
clean:
	rm -r -f ${OBJECT} ${PROMT} ${CLIENT} ./test/test_client core.*
.PHONY: clean
