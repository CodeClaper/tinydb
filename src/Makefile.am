
BUILT_SOURCES = ../include/common/data.h

SUBDIRS = common lock memory parser stmt storage trans utils

includedir = $(top_srcdir)/include

AM_YFLAGS = -d
if DEBUG
AM_CFLAGS = -g -Wall -O0 -I$(includedir)/common -I$(includedir)/lock -I$(includedir)/memory -I$(includedir)/parser\
			-I$(includedir)/stmt -I$(includedir)/storage -I$(includedir)/trans -I$(includedir)/utils
else
AM_CFLAGS = -O2 -I$(includedir)/common -I$(includedir)/lock -I$(includedir)/memory -I$(includedir)/parser\
			-I$(includedir)/stmt -I$(includedir)/storage -I$(includedir)/trans -I$(includedir)/utils
endif

LDADD = -lpthread -lm

bin_PROGRAMS = tinydb \
			   tinydb_cli

tinydb_SOURCES = db.c
tinydb_LDADD = memory/libmemory.a lock/liblock.a  trans/libtrans.a \
			   storage/libstorage.a utils/libutils.a stmt/libstmt.a parser/libparser.a common/libcommon.a -lpthread -lm 

tinydb_cli_SOURCES = db_cli.c 
tinydb_cli_LDADD = -lreadline -ltinfo
