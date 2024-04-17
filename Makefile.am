# For using custom m4 macros.
ACLOCAL_AMFLAGS = -I m4

SUBDIRS = src test/gtest
dist_doc_DATA = README.md
EXTRA_DIST = config/tinydb.cnf

check-local:
	pytest -v test/pytest/unit/

clean-local:
	@rm config.status configure config.log
	@rm Makefile
	@rm -r autom4te.cache/
	@rm aclocal.m4
	@rm compile install-sh missing Makefile.in depcomp
