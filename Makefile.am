SUBDIRS = src
dist_doc_DATA = README.md

check-local:
	cd test/pytest/unit && pytest create_test.py insert_test.py select_test.py drop_test.py

clean-local:
	@rm config.status configure config.log
	@rm Makefile
	@rm -r autom4te.cache/
	@rm aclocal.m4
	@rm compile install-sh missing Makefile.in ylwrap depcomp
