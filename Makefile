PROP=node.c token.c table.c pager.c misc.c stmt.c meta.c \
	 	input.c insert.c select.c create.c desc.c show.c index.c \
		utils.c free.c cond.c row.c opr.c copy.c \
		lex.yy.c y.tab.c intpr.c main.c
VPATH=./sql
OBJECT:= $(patsubst %.c,%.o,$(wildcard *.c ./sql/*.c))
PROMT=tinydb
CFLAGS=-w -lreadline -ltinfo


tinydb: ${OBJECT}
	gcc ${OBJECT} -o ${PROMT} ${CFLAGS}
debug: ${OBJECT}
	gcc ${OBJECT} -o ${PROMT} ${CFLAGS} -g -D DEBUG
	rm ${OBJECT}
info: ${PRMT}
	cloc ./
test: ${PROMT}
	rspec test/insert.rb	
install: tinydb
	install tinydb /usr/bin 
clean:
	rm -r -f ${OBJECT} ${PROMT} core.*
.PHONY: clean
