
includedir = ../../include
headerdirs = $(includedir)/common $(includedir)/utils $(includedir)/memory \
			 $(includedir)/storage $(includedir)/trans $(includedir)/backend
objects := $(patsubst %.c,%.o,$(wildcard *.c))
headers := $(shell find $(headerdirs) -name "*.h")
CC = gcc
CFLAGS = $(foreach headerdir, $(headerdirs), -I$(headerdir))

all: $(objects)

%.o: %.c $(headers)
	$(CC) -c $(CFLAGS) $< -o $@

.PHONY: clean all

clean:
	rm -f *.o
