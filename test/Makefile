PROP= ../node.c ../token.c ../table.c ../pager.c ../misc.c ../stmt.c ../meta.c ../insert.c ../sql/lex.yy.c ../sql/y.tab.c ../sql/intpr.c test.c
PROMT=test
test: ${PROP}
	gcc -g ${PROP} -o ${PROMT}
clean:
	rm -f -f *.o ${PROMT}
