SUBDIRS = src
dist_doc_DATA = README.md

check-local:
	pytest test/pytest/unit/ -vv

clean-local:
	@rm config.status configure config.log
	@rm Makefile
	@rm -r autom4te.cache/
	@rm aclocal.m4
	@rm compile install-sh missing Makefile.in ylwrap depcomp
