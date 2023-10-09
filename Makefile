PROP=node.c token.c table.c pager.c misc.c stmt.c meta.c \
	 	input.c insert.c select.c create.c desc.c show.c index.c \
		utils.c free.c cond.c row.c opr.c copy.c \
		./sql/lex.yy.c ./sql/y.tab.c ./sql/intpr.c main.c
PROMT=tinydb
CFLAGS=-w -lreadline -ltinfo

run: ${PROP}
	gcc ${PROP} -o ${PROMT} ${CFLAGS}
debug: ${PROP}
	gcc -g ${PROP} -o ${PROMT} ${CFLAGS} -D DEBUG
info: ${PROP}
	cloc ./
test: ${PROMT}
	rspec test/insert.rb	
install: tinydb
	install tinydb /usr/bin 
clean:
	rm -r -f *.o ${PROMT} core.*
