
includedir = ../../include
headerdirs = $(includedir)/storage $(includedir)/common $(includedir)/memory \
			 $(includedir)/trans $(includedir)/backend $(includedir)/utils $(includedir)/lock
headers := $(shell find $(headerdirs) -name "*.h")
objects := $(patsubst %.c,%.o,$(wildcard *.c))
CC = gcc

include ../common.mk

all: $(objects)

%.o: %.c $(headers)
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY: clean all

clean:
	rm -f *.o
