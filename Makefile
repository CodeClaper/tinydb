SUBDIRS := src test/gtest

all: 
	$(foreach dir, $(SUBDIRS), $(MAKE) -C $(dir);)

.PHONY: all check check-pytest check_gtest clean-local

check: check_gtest check-pytest

check-pytest:
	pytest -v test/pytest/unit/

check_gtest:
	@$(MAKE) -C test/gtest check

clean: 
	@$(foreach dir, $(SUBDIRS), $(MAKE) -C $(dir) clean;)

clean-local:
	@rm config.status configure config.log
	@rm Makefile
	@rm -r autom4te.cache/
	@rm aclocal.m4
	@rm compile install-sh missing Makefile.in depcomp
