VPATH=./sql
OBJECT:= $(patsubst %.c,%.o,$(wildcard *.c ./sql/*.c))
PROMT=tinydb
CFLAGS=-w -lreadline -ltinfo
DFLAGS=-w -lreadline -ltinfo -g -D DEBUG


tinydb: ${OBJECT}
	gcc ${OBJECT} -o ${PROMT} ${CFLAGS}
debug: *.c ./sql/*.c
	gcc  *.c ./sql/*.c -o ${PROMT} ${DFLAGS}
info: ${PRMT}
	cloc ./
test: ${PROMT}
	rspec test/insert.rb	
install: tinydb
	install tinydb /usr/bin 
clean:
	rm -r -f ${OBJECT} ${PROMT} core.*
.PHONY: clean
