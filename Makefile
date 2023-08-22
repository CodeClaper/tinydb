PROP=node.c token.c table.c pager.c misc.c stmt.c meta.c input.c insert.c ./sql/lex.yy.c  ./sql/y.tab.c  ./sql/intpr.c main.c
PROMT=tinydb
CFLAGS=-std=c99

compile: ${PROP}
	gcc ${PROP} -o ${PROMT} -w
debug: ${PROP}
	gcc -g ${PROP} -o ${PROMT}
clean:
	rm -r -f *.o ${PROMT}
