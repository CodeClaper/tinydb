
includedir = ../../include
headerdirs = $(includedir)/storage $(includedir)/common $(includedir)/memory \
			 $(includedir)/trans $(includedir)/backend $(includedir)/utils
headers := $(shell find $(headerdirs) -name "*.h")
objects := $(patsubst %.c,%.o,$(wildcard *.c))
CC = gcc

ifdef DEBUG
	CFLAGS := -g -Wall -O0 $(foreach headerdir, $(headerdirs), -I$(headerdir)) -D DEBUG
else
	CFLAGS := -O2 $(foreach headerdir, $(headerdirs), -I$(headerdir))
endif

all: $(objects)

%.o: %.c $(headers)
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY: clean all

clean:
	rm -f *.o
