
ifdef DEBUG
	CFLAGS := -g -Wall -O0 $(foreach headerdir, $(headerdirs), -I$(headerdir)) -D DEBUG
else
	CFLAGS := -g -O0 $(foreach headerdir, $(headerdirs), -I$(headerdir))
endif
