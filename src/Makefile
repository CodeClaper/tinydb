# Makefile.in generated by automake 1.16.5 from Makefile.am.
# src/Makefile.  Generated from Makefile.in by configure.

# Copyright (C) 1994-2021 Free Software Foundation, Inc.

# This Makefile.in is free software; the Free Software Foundation
# gives unlimited permission to copy and/or distribute it,
# with or without modifications, as long as this notice is preserved.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY, to the extent permitted by law; without
# even the implied warranty of MERCHANTABILITY or FITNESS FOR A
# PARTICULAR PURPOSE.




am__is_gnu_make = { \
  if test -z '$(MAKELEVEL)'; then \
    false; \
  elif test -n '$(MAKE_HOST)'; then \
    true; \
  elif test -n '$(MAKE_VERSION)' && test -n '$(CURDIR)'; then \
    true; \
  else \
    false; \
  fi; \
}
am__make_running_with_option = \
  case $${target_option-} in \
      ?) ;; \
      *) echo "am__make_running_with_option: internal error: invalid" \
              "target option '$${target_option-}' specified" >&2; \
         exit 1;; \
  esac; \
  has_opt=no; \
  sane_makeflags=$$MAKEFLAGS; \
  if $(am__is_gnu_make); then \
    sane_makeflags=$$MFLAGS; \
  else \
    case $$MAKEFLAGS in \
      *\\[\ \	]*) \
        bs=\\; \
        sane_makeflags=`printf '%s\n' "$$MAKEFLAGS" \
          | sed "s/$$bs$$bs[$$bs $$bs	]*//g"`;; \
    esac; \
  fi; \
  skip_next=no; \
  strip_trailopt () \
  { \
    flg=`printf '%s\n' "$$flg" | sed "s/$$1.*$$//"`; \
  }; \
  for flg in $$sane_makeflags; do \
    test $$skip_next = yes && { skip_next=no; continue; }; \
    case $$flg in \
      *=*|--*) continue;; \
        -*I) strip_trailopt 'I'; skip_next=yes;; \
      -*I?*) strip_trailopt 'I';; \
        -*O) strip_trailopt 'O'; skip_next=yes;; \
      -*O?*) strip_trailopt 'O';; \
        -*l) strip_trailopt 'l'; skip_next=yes;; \
      -*l?*) strip_trailopt 'l';; \
      -[dEDm]) skip_next=yes;; \
      -[JT]) skip_next=yes;; \
    esac; \
    case $$flg in \
      *$$target_option*) has_opt=yes; break;; \
    esac; \
  done; \
  test $$has_opt = yes
am__make_dryrun = (target_option=n; $(am__make_running_with_option))
am__make_keepgoing = (target_option=k; $(am__make_running_with_option))
pkgdatadir = $(datadir)/tinydb
pkgincludedir = $(includedir)/tinydb
pkglibdir = $(libdir)/tinydb
pkglibexecdir = $(libexecdir)/tinydb
am__cd = CDPATH="$${ZSH_VERSION+.}$(PATH_SEPARATOR)" && cd
install_sh_DATA = $(install_sh) -c -m 644
install_sh_PROGRAM = $(install_sh) -c
install_sh_SCRIPT = $(install_sh) -c
INSTALL_HEADER = $(INSTALL_DATA)
transform = $(program_transform_name)
NORMAL_INSTALL = :
PRE_INSTALL = :
POST_INSTALL = :
NORMAL_UNINSTALL = :
PRE_UNINSTALL = :
POST_UNINSTALL = :
bin_PROGRAMS = tinydb$(EXEEXT) tinydb_cli$(EXEEXT)
subdir = src
ACLOCAL_M4 = $(top_srcdir)/aclocal.m4
am__aclocal_m4_deps = $(top_srcdir)/configure.ac
am__configure_deps = $(am__aclocal_m4_deps) $(CONFIGURE_DEPENDENCIES) \
	$(ACLOCAL_M4)
DIST_COMMON = $(srcdir)/Makefile.am $(am__DIST_COMMON)
mkinstalldirs = $(install_sh) -d
CONFIG_HEADER = $(top_builddir)/config.h
CONFIG_CLEAN_FILES =
CONFIG_CLEAN_VPATH_FILES =
am__installdirs = "$(DESTDIR)$(bindir)"
PROGRAMS = $(bin_PROGRAMS)
am_tinydb_OBJECTS = db.$(OBJEXT) cache.$(OBJEXT) check.$(OBJEXT) \
	cond.$(OBJEXT) conf.$(OBJEXT) copy.$(OBJEXT) create.$(OBJEXT) \
	delete.$(OBJEXT) desc.$(OBJEXT) free.$(OBJEXT) index.$(OBJEXT) \
	input.$(OBJEXT) insert.$(OBJEXT) intpr.$(OBJEXT) \
	lex.yy.$(OBJEXT) log.$(OBJEXT) mem.$(OBJEXT) meta.$(OBJEXT) \
	misc.$(OBJEXT) node.$(OBJEXT) opr.$(OBJEXT) pager.$(OBJEXT) \
	select.$(OBJEXT) server.$(OBJEXT) session.$(OBJEXT) \
	show.$(OBJEXT) stmt.$(OBJEXT) table.$(OBJEXT) token.$(OBJEXT) \
	update.$(OBJEXT) utils.$(OBJEXT) y.tab.$(OBJEXT)
tinydb_OBJECTS = $(am_tinydb_OBJECTS)
tinydb_LDADD = $(LDADD)
tinydb_DEPENDENCIES =
am_tinydb_cli_OBJECTS = db_cli.$(OBJEXT) input.$(OBJEXT)
tinydb_cli_OBJECTS = $(am_tinydb_cli_OBJECTS)
tinydb_cli_DEPENDENCIES =
AM_V_P = $(am__v_P_$(V))
am__v_P_ = $(am__v_P_$(AM_DEFAULT_VERBOSITY))
am__v_P_0 = false
am__v_P_1 = :
AM_V_GEN = $(am__v_GEN_$(V))
am__v_GEN_ = $(am__v_GEN_$(AM_DEFAULT_VERBOSITY))
am__v_GEN_0 = @echo "  GEN     " $@;
am__v_GEN_1 = 
AM_V_at = $(am__v_at_$(V))
am__v_at_ = $(am__v_at_$(AM_DEFAULT_VERBOSITY))
am__v_at_0 = @
am__v_at_1 = 
DEFAULT_INCLUDES = -I. -I$(top_builddir)
depcomp = $(SHELL) $(top_srcdir)/depcomp
am__maybe_remake_depfiles = depfiles
am__depfiles_remade = ./$(DEPDIR)/cache.Po ./$(DEPDIR)/check.Po \
	./$(DEPDIR)/cond.Po ./$(DEPDIR)/conf.Po ./$(DEPDIR)/copy.Po \
	./$(DEPDIR)/create.Po ./$(DEPDIR)/db.Po ./$(DEPDIR)/db_cli.Po \
	./$(DEPDIR)/delete.Po ./$(DEPDIR)/desc.Po ./$(DEPDIR)/free.Po \
	./$(DEPDIR)/index.Po ./$(DEPDIR)/input.Po \
	./$(DEPDIR)/insert.Po ./$(DEPDIR)/intpr.Po \
	./$(DEPDIR)/lex.yy.Po ./$(DEPDIR)/log.Po ./$(DEPDIR)/mem.Po \
	./$(DEPDIR)/meta.Po ./$(DEPDIR)/misc.Po ./$(DEPDIR)/node.Po \
	./$(DEPDIR)/opr.Po ./$(DEPDIR)/pager.Po ./$(DEPDIR)/select.Po \
	./$(DEPDIR)/server.Po ./$(DEPDIR)/session.Po \
	./$(DEPDIR)/show.Po ./$(DEPDIR)/stmt.Po ./$(DEPDIR)/table.Po \
	./$(DEPDIR)/token.Po ./$(DEPDIR)/update.Po \
	./$(DEPDIR)/utils.Po ./$(DEPDIR)/y.tab.Po
am__mv = mv -f
COMPILE = $(CC) $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) \
	$(CPPFLAGS) $(AM_CFLAGS) $(CFLAGS)
AM_V_CC = $(am__v_CC_$(V))
am__v_CC_ = $(am__v_CC_$(AM_DEFAULT_VERBOSITY))
am__v_CC_0 = @echo "  CC      " $@;
am__v_CC_1 = 
CCLD = $(CC)
LINK = $(CCLD) $(AM_CFLAGS) $(CFLAGS) $(AM_LDFLAGS) $(LDFLAGS) -o $@
AM_V_CCLD = $(am__v_CCLD_$(V))
am__v_CCLD_ = $(am__v_CCLD_$(AM_DEFAULT_VERBOSITY))
am__v_CCLD_0 = @echo "  CCLD    " $@;
am__v_CCLD_1 = 
SOURCES = $(tinydb_SOURCES) $(tinydb_cli_SOURCES)
DIST_SOURCES = $(tinydb_SOURCES) $(tinydb_cli_SOURCES)
am__can_run_installinfo = \
  case $$AM_UPDATE_INFO_DIR in \
    n|no|NO) false;; \
    *) (install-info --version) >/dev/null 2>&1;; \
  esac
am__tagged_files = $(HEADERS) $(SOURCES) $(TAGS_FILES) $(LISP)
# Read a list of newline-separated strings from the standard input,
# and print each of them once, without duplicates.  Input order is
# *not* preserved.
am__uniquify_input = $(AWK) '\
  BEGIN { nonempty = 0; } \
  { items[$$0] = 1; nonempty = 1; } \
  END { if (nonempty) { for (i in items) print i; }; } \
'
# Make sure the list of sources is unique.  This is necessary because,
# e.g., the same source file might be shared among _SOURCES variables
# for different programs/libraries.
am__define_uniq_tagged_files = \
  list='$(am__tagged_files)'; \
  unique=`for i in $$list; do \
    if test -f "$$i"; then echo $$i; else echo $(srcdir)/$$i; fi; \
  done | $(am__uniquify_input)`
am__DIST_COMMON = $(srcdir)/Makefile.in $(top_srcdir)/depcomp
DISTFILES = $(DIST_COMMON) $(DIST_SOURCES) $(TEXINFOS) $(EXTRA_DIST)
ACLOCAL = ${SHELL} '/home/zc/work/c/TinyDb/missing' aclocal-1.16
AMTAR = $${TAR-tar}
AM_DEFAULT_VERBOSITY = 1
AUTOCONF = ${SHELL} '/home/zc/work/c/TinyDb/missing' autoconf
AUTOHEADER = ${SHELL} '/home/zc/work/c/TinyDb/missing' autoheader
AUTOMAKE = ${SHELL} '/home/zc/work/c/TinyDb/missing' automake-1.16
AWK = mawk
CC = gcc
CCDEPMODE = depmode=gcc3
CFLAGS = -w
CPPFLAGS = 
CSCOPE = cscope
CTAGS = ctags
CYGPATH_W = echo
DEFS = -DHAVE_CONFIG_H
DEPDIR = .deps
ECHO_C = 
ECHO_N = -n
ECHO_T = 
ETAGS = etags
EXEEXT = 
INSTALL = /usr/bin/install -c
INSTALL_DATA = ${INSTALL} -m 644
INSTALL_PROGRAM = ${INSTALL}
INSTALL_SCRIPT = ${INSTALL}
INSTALL_STRIP_PROGRAM = $(install_sh) -c -s
LDFLAGS = 
LEX = flex
LEXLIB = -ll 
LEX_OUTPUT_ROOT = lex.yy
LIBOBJS = 
LIBREADLINE = -lreadline -lncurses
LIBS = 
LTLIBOBJS = 
MAKEINFO = ${SHELL} '/home/zc/work/c/TinyDb/missing' makeinfo
MKDIR_P = /usr/bin/mkdir -p
OBJEXT = o
PACKAGE = tinydb
PACKAGE_BUGREPORT = jerryzhou.zc@gmail.com
PACKAGE_NAME = tinydb, tinydb_cli
PACKAGE_STRING = tinydb, tinydb_cli 0.1
PACKAGE_TARNAME = tinydb
PACKAGE_URL = 
PACKAGE_VERSION = 0.1
PATH_SEPARATOR = :
SET_MAKE = 
SHELL = /bin/bash
STRIP = 
VERSION = 0.1
YACC = bison -y
YFLAGS = 
abs_builddir = /home/zc/work/c/TinyDb/src
abs_srcdir = /home/zc/work/c/TinyDb/src
abs_top_builddir = /home/zc/work/c/TinyDb
abs_top_srcdir = /home/zc/work/c/TinyDb
ac_ct_CC = gcc
am__include = include
am__leading_dot = .
am__quote = 
am__tar = $${TAR-tar} chof - "$$tardir"
am__untar = $${TAR-tar} xf -
bindir = ${exec_prefix}/bin
build_alias = 
builddir = .
datadir = ${datarootdir}
datarootdir = ${prefix}/share
docdir = ${datarootdir}/doc/${PACKAGE_TARNAME}
dvidir = ${docdir}
exec_prefix = ${prefix}
host_alias = 
htmldir = ${docdir}
includedir = ${prefix}/include
infodir = ${datarootdir}/info
install_sh = ${SHELL} /home/zc/work/c/TinyDb/install-sh
libdir = ${exec_prefix}/lib
libexecdir = ${exec_prefix}/libexec
localedir = ${datarootdir}/locale
localstatedir = ${prefix}/var
mandir = ${datarootdir}/man
mkdir_p = $(MKDIR_P)
oldincludedir = /usr/include
pdfdir = ${docdir}
prefix = /usr/local
program_transform_name = s,x,x,
psdir = ${docdir}
runstatedir = ${localstatedir}/run
sbindir = ${exec_prefix}/sbin
sharedstatedir = ${prefix}/com
srcdir = .
sysconfdir = ${prefix}/etc
target_alias = 
top_build_prefix = ../
top_builddir = ..
top_srcdir = ..
BUILT_SOURCES = data.h
AM_YFLAGS = -d
#AM_CFLAGS = -O2
AM_CFLAGS = -g3 -O0
LDADD = -lpthread
tinydb_SOURCES = db.c cache.c cache.h check.c check.h common.h cond.c cond.h  conf.c conf.h const.h \
				 copy.c copy.h create.c create.h data.h defs.h delete.c delete.h desc.c desc.h free.c free.h index.c index.h \
				 input.c input.h insert.c insert.h intpr.c intpr.h lex.yy.c log.c log.h mem.c mem.h meta.c meta.h \
				 misc.c misc.h node.c node.h opr.c opr.h pager.c pager.h select.c select.h server.c server.h session.c session.h \
				 show.c show.h stmt.c stmt.h table.c table.h token.c token.h update.c update.h utils.c utils.h y.tab.c y.tab.h

tinydb_cli_SOURCES = db_cli.c input.c input.h
tinydb_cli_LDADD = -lreadline -ltinfo
all: $(BUILT_SOURCES)
	$(MAKE) $(AM_MAKEFLAGS) all-am

.SUFFIXES:
.SUFFIXES: .c .o .obj
$(srcdir)/Makefile.in:  $(srcdir)/Makefile.am  $(am__configure_deps)
	@for dep in $?; do \
	  case '$(am__configure_deps)' in \
	    *$$dep*) \
	      ( cd $(top_builddir) && $(MAKE) $(AM_MAKEFLAGS) am--refresh ) \
	        && { if test -f $@; then exit 0; else break; fi; }; \
	      exit 1;; \
	  esac; \
	done; \
	echo ' cd $(top_srcdir) && $(AUTOMAKE) --gnu src/Makefile'; \
	$(am__cd) $(top_srcdir) && \
	  $(AUTOMAKE) --gnu src/Makefile
Makefile: $(srcdir)/Makefile.in $(top_builddir)/config.status
	@case '$?' in \
	  *config.status*) \
	    cd $(top_builddir) && $(MAKE) $(AM_MAKEFLAGS) am--refresh;; \
	  *) \
	    echo ' cd $(top_builddir) && $(SHELL) ./config.status $(subdir)/$@ $(am__maybe_remake_depfiles)'; \
	    cd $(top_builddir) && $(SHELL) ./config.status $(subdir)/$@ $(am__maybe_remake_depfiles);; \
	esac;

$(top_builddir)/config.status: $(top_srcdir)/configure $(CONFIG_STATUS_DEPENDENCIES)
	cd $(top_builddir) && $(MAKE) $(AM_MAKEFLAGS) am--refresh

$(top_srcdir)/configure:  $(am__configure_deps)
	cd $(top_builddir) && $(MAKE) $(AM_MAKEFLAGS) am--refresh
$(ACLOCAL_M4):  $(am__aclocal_m4_deps)
	cd $(top_builddir) && $(MAKE) $(AM_MAKEFLAGS) am--refresh
$(am__aclocal_m4_deps):
install-binPROGRAMS: $(bin_PROGRAMS)
	@$(NORMAL_INSTALL)
	@list='$(bin_PROGRAMS)'; test -n "$(bindir)" || list=; \
	if test -n "$$list"; then \
	  echo " $(MKDIR_P) '$(DESTDIR)$(bindir)'"; \
	  $(MKDIR_P) "$(DESTDIR)$(bindir)" || exit 1; \
	fi; \
	for p in $$list; do echo "$$p $$p"; done | \
	sed 's/$(EXEEXT)$$//' | \
	while read p p1; do if test -f $$p \
	  ; then echo "$$p"; echo "$$p"; else :; fi; \
	done | \
	sed -e 'p;s,.*/,,;n;h' \
	    -e 's|.*|.|' \
	    -e 'p;x;s,.*/,,;s/$(EXEEXT)$$//;$(transform);s/$$/$(EXEEXT)/' | \
	sed 'N;N;N;s,\n, ,g' | \
	$(AWK) 'BEGIN { files["."] = ""; dirs["."] = 1 } \
	  { d=$$3; if (dirs[d] != 1) { print "d", d; dirs[d] = 1 } \
	    if ($$2 == $$4) files[d] = files[d] " " $$1; \
	    else { print "f", $$3 "/" $$4, $$1; } } \
	  END { for (d in files) print "f", d, files[d] }' | \
	while read type dir files; do \
	    if test "$$dir" = .; then dir=; else dir=/$$dir; fi; \
	    test -z "$$files" || { \
	      echo " $(INSTALL_PROGRAM_ENV) $(INSTALL_PROGRAM) $$files '$(DESTDIR)$(bindir)$$dir'"; \
	      $(INSTALL_PROGRAM_ENV) $(INSTALL_PROGRAM) $$files "$(DESTDIR)$(bindir)$$dir" || exit $$?; \
	    } \
	; done

uninstall-binPROGRAMS:
	@$(NORMAL_UNINSTALL)
	@list='$(bin_PROGRAMS)'; test -n "$(bindir)" || list=; \
	files=`for p in $$list; do echo "$$p"; done | \
	  sed -e 'h;s,^.*/,,;s/$(EXEEXT)$$//;$(transform)' \
	      -e 's/$$/$(EXEEXT)/' \
	`; \
	test -n "$$list" || exit 0; \
	echo " ( cd '$(DESTDIR)$(bindir)' && rm -f" $$files ")"; \
	cd "$(DESTDIR)$(bindir)" && rm -f $$files

clean-binPROGRAMS:
	-test -z "$(bin_PROGRAMS)" || rm -f $(bin_PROGRAMS)

tinydb$(EXEEXT): $(tinydb_OBJECTS) $(tinydb_DEPENDENCIES) $(EXTRA_tinydb_DEPENDENCIES) 
	@rm -f tinydb$(EXEEXT)
	$(AM_V_CCLD)$(LINK) $(tinydb_OBJECTS) $(tinydb_LDADD) $(LIBS)

tinydb_cli$(EXEEXT): $(tinydb_cli_OBJECTS) $(tinydb_cli_DEPENDENCIES) $(EXTRA_tinydb_cli_DEPENDENCIES) 
	@rm -f tinydb_cli$(EXEEXT)
	$(AM_V_CCLD)$(LINK) $(tinydb_cli_OBJECTS) $(tinydb_cli_LDADD) $(LIBS)

mostlyclean-compile:
	-rm -f *.$(OBJEXT)

distclean-compile:
	-rm -f *.tab.c

include ./$(DEPDIR)/cache.Po # am--include-marker
include ./$(DEPDIR)/check.Po # am--include-marker
include ./$(DEPDIR)/cond.Po # am--include-marker
include ./$(DEPDIR)/conf.Po # am--include-marker
include ./$(DEPDIR)/copy.Po # am--include-marker
include ./$(DEPDIR)/create.Po # am--include-marker
include ./$(DEPDIR)/db.Po # am--include-marker
include ./$(DEPDIR)/db_cli.Po # am--include-marker
include ./$(DEPDIR)/delete.Po # am--include-marker
include ./$(DEPDIR)/desc.Po # am--include-marker
include ./$(DEPDIR)/free.Po # am--include-marker
include ./$(DEPDIR)/index.Po # am--include-marker
include ./$(DEPDIR)/input.Po # am--include-marker
include ./$(DEPDIR)/insert.Po # am--include-marker
include ./$(DEPDIR)/intpr.Po # am--include-marker
include ./$(DEPDIR)/lex.yy.Po # am--include-marker
include ./$(DEPDIR)/log.Po # am--include-marker
include ./$(DEPDIR)/mem.Po # am--include-marker
include ./$(DEPDIR)/meta.Po # am--include-marker
include ./$(DEPDIR)/misc.Po # am--include-marker
include ./$(DEPDIR)/node.Po # am--include-marker
include ./$(DEPDIR)/opr.Po # am--include-marker
include ./$(DEPDIR)/pager.Po # am--include-marker
include ./$(DEPDIR)/select.Po # am--include-marker
include ./$(DEPDIR)/server.Po # am--include-marker
include ./$(DEPDIR)/session.Po # am--include-marker
include ./$(DEPDIR)/show.Po # am--include-marker
include ./$(DEPDIR)/stmt.Po # am--include-marker
include ./$(DEPDIR)/table.Po # am--include-marker
include ./$(DEPDIR)/token.Po # am--include-marker
include ./$(DEPDIR)/update.Po # am--include-marker
include ./$(DEPDIR)/utils.Po # am--include-marker
include ./$(DEPDIR)/y.tab.Po # am--include-marker

$(am__depfiles_remade):
	@$(MKDIR_P) $(@D)
	@echo '# dummy' >$@-t && $(am__mv) $@-t $@

am--depfiles: $(am__depfiles_remade)

.c.o:
	$(AM_V_CC)$(COMPILE) -MT $@ -MD -MP -MF $(DEPDIR)/$*.Tpo -c -o $@ $<
	$(AM_V_at)$(am__mv) $(DEPDIR)/$*.Tpo $(DEPDIR)/$*.Po
#	$(AM_V_CC)source='$<' object='$@' libtool=no \
#	DEPDIR=$(DEPDIR) $(CCDEPMODE) $(depcomp) \
#	$(AM_V_CC_no)$(COMPILE) -c -o $@ $<

.c.obj:
	$(AM_V_CC)$(COMPILE) -MT $@ -MD -MP -MF $(DEPDIR)/$*.Tpo -c -o $@ `$(CYGPATH_W) '$<'`
	$(AM_V_at)$(am__mv) $(DEPDIR)/$*.Tpo $(DEPDIR)/$*.Po
#	$(AM_V_CC)source='$<' object='$@' libtool=no \
#	DEPDIR=$(DEPDIR) $(CCDEPMODE) $(depcomp) \
#	$(AM_V_CC_no)$(COMPILE) -c -o $@ `$(CYGPATH_W) '$<'`

ID: $(am__tagged_files)
	$(am__define_uniq_tagged_files); mkid -fID $$unique
tags: tags-am
TAGS: tags

tags-am: $(TAGS_DEPENDENCIES) $(am__tagged_files)
	set x; \
	here=`pwd`; \
	$(am__define_uniq_tagged_files); \
	shift; \
	if test -z "$(ETAGS_ARGS)$$*$$unique"; then :; else \
	  test -n "$$unique" || unique=$$empty_fix; \
	  if test $$# -gt 0; then \
	    $(ETAGS) $(ETAGSFLAGS) $(AM_ETAGSFLAGS) $(ETAGS_ARGS) \
	      "$$@" $$unique; \
	  else \
	    $(ETAGS) $(ETAGSFLAGS) $(AM_ETAGSFLAGS) $(ETAGS_ARGS) \
	      $$unique; \
	  fi; \
	fi
ctags: ctags-am

CTAGS: ctags
ctags-am: $(TAGS_DEPENDENCIES) $(am__tagged_files)
	$(am__define_uniq_tagged_files); \
	test -z "$(CTAGS_ARGS)$$unique" \
	  || $(CTAGS) $(CTAGSFLAGS) $(AM_CTAGSFLAGS) $(CTAGS_ARGS) \
	     $$unique

GTAGS:
	here=`$(am__cd) $(top_builddir) && pwd` \
	  && $(am__cd) $(top_srcdir) \
	  && gtags -i $(GTAGS_ARGS) "$$here"
cscopelist: cscopelist-am

cscopelist-am: $(am__tagged_files)
	list='$(am__tagged_files)'; \
	case "$(srcdir)" in \
	  [\\/]* | ?:[\\/]*) sdir="$(srcdir)" ;; \
	  *) sdir=$(subdir)/$(srcdir) ;; \
	esac; \
	for i in $$list; do \
	  if test -f "$$i"; then \
	    echo "$(subdir)/$$i"; \
	  else \
	    echo "$$sdir/$$i"; \
	  fi; \
	done >> $(top_builddir)/cscope.files

distclean-tags:
	-rm -f TAGS ID GTAGS GRTAGS GSYMS GPATH tags
distdir: $(BUILT_SOURCES)
	$(MAKE) $(AM_MAKEFLAGS) distdir-am

distdir-am: $(DISTFILES)
	@srcdirstrip=`echo "$(srcdir)" | sed 's/[].[^$$\\*]/\\\\&/g'`; \
	topsrcdirstrip=`echo "$(top_srcdir)" | sed 's/[].[^$$\\*]/\\\\&/g'`; \
	list='$(DISTFILES)'; \
	  dist_files=`for file in $$list; do echo $$file; done | \
	  sed -e "s|^$$srcdirstrip/||;t" \
	      -e "s|^$$topsrcdirstrip/|$(top_builddir)/|;t"`; \
	case $$dist_files in \
	  */*) $(MKDIR_P) `echo "$$dist_files" | \
			   sed '/\//!d;s|^|$(distdir)/|;s,/[^/]*$$,,' | \
			   sort -u` ;; \
	esac; \
	for file in $$dist_files; do \
	  if test -f $$file || test -d $$file; then d=.; else d=$(srcdir); fi; \
	  if test -d $$d/$$file; then \
	    dir=`echo "/$$file" | sed -e 's,/[^/]*$$,,'`; \
	    if test -d "$(distdir)/$$file"; then \
	      find "$(distdir)/$$file" -type d ! -perm -700 -exec chmod u+rwx {} \;; \
	    fi; \
	    if test -d $(srcdir)/$$file && test $$d != $(srcdir); then \
	      cp -fpR $(srcdir)/$$file "$(distdir)$$dir" || exit 1; \
	      find "$(distdir)/$$file" -type d ! -perm -700 -exec chmod u+rwx {} \;; \
	    fi; \
	    cp -fpR $$d/$$file "$(distdir)$$dir" || exit 1; \
	  else \
	    test -f "$(distdir)/$$file" \
	    || cp -p $$d/$$file "$(distdir)/$$file" \
	    || exit 1; \
	  fi; \
	done
check-am: all-am
check: $(BUILT_SOURCES)
	$(MAKE) $(AM_MAKEFLAGS) check-am
all-am: Makefile $(PROGRAMS)
installdirs:
	for dir in "$(DESTDIR)$(bindir)"; do \
	  test -z "$$dir" || $(MKDIR_P) "$$dir"; \
	done
install: $(BUILT_SOURCES)
	$(MAKE) $(AM_MAKEFLAGS) install-am
install-exec: $(BUILT_SOURCES)
	$(MAKE) $(AM_MAKEFLAGS) install-exec-am
install-data: install-data-am
uninstall: uninstall-am

install-am: all-am
	@$(MAKE) $(AM_MAKEFLAGS) install-exec-am install-data-am

installcheck: installcheck-am
install-strip:
	if test -z '$(STRIP)'; then \
	  $(MAKE) $(AM_MAKEFLAGS) INSTALL_PROGRAM="$(INSTALL_STRIP_PROGRAM)" \
	    install_sh_PROGRAM="$(INSTALL_STRIP_PROGRAM)" INSTALL_STRIP_FLAG=-s \
	      install; \
	else \
	  $(MAKE) $(AM_MAKEFLAGS) INSTALL_PROGRAM="$(INSTALL_STRIP_PROGRAM)" \
	    install_sh_PROGRAM="$(INSTALL_STRIP_PROGRAM)" INSTALL_STRIP_FLAG=-s \
	    "INSTALL_PROGRAM_ENV=STRIPPROG='$(STRIP)'" install; \
	fi
mostlyclean-generic:

clean-generic:

distclean-generic:
	-test -z "$(CONFIG_CLEAN_FILES)" || rm -f $(CONFIG_CLEAN_FILES)
	-test . = "$(srcdir)" || test -z "$(CONFIG_CLEAN_VPATH_FILES)" || rm -f $(CONFIG_CLEAN_VPATH_FILES)

maintainer-clean-generic:
	@echo "This command is intended for maintainers to use"
	@echo "it deletes files that may require special tools to rebuild."
	-test -z "$(BUILT_SOURCES)" || rm -f $(BUILT_SOURCES)
clean: clean-am

clean-am: clean-binPROGRAMS clean-generic mostlyclean-am

distclean: distclean-am
		-rm -f ./$(DEPDIR)/cache.Po
	-rm -f ./$(DEPDIR)/check.Po
	-rm -f ./$(DEPDIR)/cond.Po
	-rm -f ./$(DEPDIR)/conf.Po
	-rm -f ./$(DEPDIR)/copy.Po
	-rm -f ./$(DEPDIR)/create.Po
	-rm -f ./$(DEPDIR)/db.Po
	-rm -f ./$(DEPDIR)/db_cli.Po
	-rm -f ./$(DEPDIR)/delete.Po
	-rm -f ./$(DEPDIR)/desc.Po
	-rm -f ./$(DEPDIR)/free.Po
	-rm -f ./$(DEPDIR)/index.Po
	-rm -f ./$(DEPDIR)/input.Po
	-rm -f ./$(DEPDIR)/insert.Po
	-rm -f ./$(DEPDIR)/intpr.Po
	-rm -f ./$(DEPDIR)/lex.yy.Po
	-rm -f ./$(DEPDIR)/log.Po
	-rm -f ./$(DEPDIR)/mem.Po
	-rm -f ./$(DEPDIR)/meta.Po
	-rm -f ./$(DEPDIR)/misc.Po
	-rm -f ./$(DEPDIR)/node.Po
	-rm -f ./$(DEPDIR)/opr.Po
	-rm -f ./$(DEPDIR)/pager.Po
	-rm -f ./$(DEPDIR)/select.Po
	-rm -f ./$(DEPDIR)/server.Po
	-rm -f ./$(DEPDIR)/session.Po
	-rm -f ./$(DEPDIR)/show.Po
	-rm -f ./$(DEPDIR)/stmt.Po
	-rm -f ./$(DEPDIR)/table.Po
	-rm -f ./$(DEPDIR)/token.Po
	-rm -f ./$(DEPDIR)/update.Po
	-rm -f ./$(DEPDIR)/utils.Po
	-rm -f ./$(DEPDIR)/y.tab.Po
	-rm -f Makefile
distclean-am: clean-am distclean-compile distclean-generic \
	distclean-tags

dvi: dvi-am

dvi-am:

html: html-am

html-am:

info: info-am

info-am:

install-data-am:

install-dvi: install-dvi-am

install-dvi-am:

install-exec-am: install-binPROGRAMS
	@$(NORMAL_INSTALL)
	$(MAKE) $(AM_MAKEFLAGS) install-exec-hook
install-html: install-html-am

install-html-am:

install-info: install-info-am

install-info-am:

install-man:

install-pdf: install-pdf-am

install-pdf-am:

install-ps: install-ps-am

install-ps-am:

installcheck-am:

maintainer-clean: maintainer-clean-am
		-rm -f ./$(DEPDIR)/cache.Po
	-rm -f ./$(DEPDIR)/check.Po
	-rm -f ./$(DEPDIR)/cond.Po
	-rm -f ./$(DEPDIR)/conf.Po
	-rm -f ./$(DEPDIR)/copy.Po
	-rm -f ./$(DEPDIR)/create.Po
	-rm -f ./$(DEPDIR)/db.Po
	-rm -f ./$(DEPDIR)/db_cli.Po
	-rm -f ./$(DEPDIR)/delete.Po
	-rm -f ./$(DEPDIR)/desc.Po
	-rm -f ./$(DEPDIR)/free.Po
	-rm -f ./$(DEPDIR)/index.Po
	-rm -f ./$(DEPDIR)/input.Po
	-rm -f ./$(DEPDIR)/insert.Po
	-rm -f ./$(DEPDIR)/intpr.Po
	-rm -f ./$(DEPDIR)/lex.yy.Po
	-rm -f ./$(DEPDIR)/log.Po
	-rm -f ./$(DEPDIR)/mem.Po
	-rm -f ./$(DEPDIR)/meta.Po
	-rm -f ./$(DEPDIR)/misc.Po
	-rm -f ./$(DEPDIR)/node.Po
	-rm -f ./$(DEPDIR)/opr.Po
	-rm -f ./$(DEPDIR)/pager.Po
	-rm -f ./$(DEPDIR)/select.Po
	-rm -f ./$(DEPDIR)/server.Po
	-rm -f ./$(DEPDIR)/session.Po
	-rm -f ./$(DEPDIR)/show.Po
	-rm -f ./$(DEPDIR)/stmt.Po
	-rm -f ./$(DEPDIR)/table.Po
	-rm -f ./$(DEPDIR)/token.Po
	-rm -f ./$(DEPDIR)/update.Po
	-rm -f ./$(DEPDIR)/utils.Po
	-rm -f ./$(DEPDIR)/y.tab.Po
	-rm -f Makefile
maintainer-clean-am: distclean-am maintainer-clean-generic

mostlyclean: mostlyclean-am

mostlyclean-am: mostlyclean-compile mostlyclean-generic

pdf: pdf-am

pdf-am:

ps: ps-am

ps-am:

uninstall-am: uninstall-binPROGRAMS

.MAKE: all check install install-am install-exec install-exec-am \
	install-strip

.PHONY: CTAGS GTAGS TAGS all all-am am--depfiles check check-am clean \
	clean-binPROGRAMS clean-generic cscopelist-am ctags ctags-am \
	distclean distclean-compile distclean-generic distclean-tags \
	distdir dvi dvi-am html html-am info info-am install \
	install-am install-binPROGRAMS install-data install-data-am \
	install-dvi install-dvi-am install-exec install-exec-am \
	install-exec-hook install-html install-html-am install-info \
	install-info-am install-man install-pdf install-pdf-am \
	install-ps install-ps-am install-strip installcheck \
	installcheck-am installdirs maintainer-clean \
	maintainer-clean-generic mostlyclean mostlyclean-compile \
	mostlyclean-generic pdf pdf-am ps ps-am tags tags-am uninstall \
	uninstall-am uninstall-binPROGRAMS

.PRECIOUS: Makefile

install-exec-hook: mkdir /usr/local/data

# Tell versions [3.59,3.63) of GNU make to not export all variables.
# Otherwise a system limit (for SysV at least) may be exceeded.
.NOEXPORT: