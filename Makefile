SUBDIRS := src test/gtest

all: 
	$(foreach dir, $(SUBDIRS), $(MAKE) -C $(dir);)

.PHONY: all check check-pytest check_gtest clean

check: check-gtest check-pytest

check-pytest:
	pytest -v 

check-gtest:
	@$(MAKE) -C test/gtest check

clean: 
	@$(foreach dir, $(SUBDIRS), $(MAKE) -C $(dir) clean;)
