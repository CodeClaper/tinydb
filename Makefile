PROP=node.c token.c table.c pager.c misc.c stmt.c meta.c input.c insert.c select.c create.c desc.c show.c index.c utils.c free.c ./sql/lex.yy.c  ./sql/y.tab.c  ./sql/intpr.c main.c
PROMT=tinydb
CFLAGS=-std=c99

compile: ${PROP}
	gcc ${PROP} -o ${PROMT} -w
debug: ${PROP}
	gcc -g ${PROP} -o ${PROMT} -w -D DEBUG
clean:
	rm -r -f *.o ${PROMT} core.*
