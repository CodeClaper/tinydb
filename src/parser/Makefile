
includedir = ../../include
headerdirs = $(includedir)/parser $(includedir)/common $(includedir)/memory \
			 $(includedir)/utils ./
headers := $(shell find $(headerdirs) -name "*.h")
objects := $(patsubst %.c,%.o,$(wildcard *.c))
CC = gcc

include ../common.mk

all: $(objects)

%.o: %.c $(headers) y.tab.c
	$(CC) -c $(CFLAGS) $< -o $@

y.tab.c: sql.l sql.y
	lex sql.l
	yacc -d sql.y

PHONY: clean all

clean:
	rm -f *.o
