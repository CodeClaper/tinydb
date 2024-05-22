
topdir = ../../
includedir = $(topdir)include
srcdir = $(topdir)src
SUBDIRS := $(srcdir)/backend  $(srcdir)/common $(srcdir)/lock \
		   $(srcdir)/memory $(srcdir)/parser $(srcdir)/storage \
		   $(srcdir)/trans $(srcdir)/utils
objects := $(patsubst %.cpp, %.o, $(wildcard *.cpp)) 
objects += $(patsubst %.c, %.o, $(shell find $(SUBDIRS) -name "*.c"))

CPPLDADD = -lgtest_main -lgtest
CPPLDFLAGS= -pthread
CPPFLAGS = -w -I/usr/src/googletest/googletest/include -I/usr/src/googletest/googletest \
		   -I$(includedir)/lock -I$(includedir)/common  -I$(includedir)/utils

target = gtest

all: $(objects)
	$(CXX) $(CPPFLAGS) $(objects) -o $(target) $(CPPLDADD) $(CPPLDFLAGS)

%o: %.cpp
	$(CXX) $(CPPFLAGS) -c $< -o $@ $(CPPLDADD) $(CPPLDFLAGS)

.PHONY: clean all test

check: 
	@./gtest

clean:
	rm -f *.o $(target)
