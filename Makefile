SUBDIRS := src 

all: 
	$(foreach dir, $(SUBDIRS), $(MAKE) -C $(dir);)

.PHONY: all check check-pytest check_gtest clean-local

check: check-gtest check-pytest

check-pytest:
	pytest -v test/pytest/unit/

check-gtest:
	@$(MAKE) -C test/gtest check

clean: 
	@$(foreach dir, $(SUBDIRS), $(MAKE) -C $(dir) clean;)
