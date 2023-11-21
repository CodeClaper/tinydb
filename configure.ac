AC_INIT([tinydb], [0.1], [jerryzhou.zc@gmail.com])
AM_INIT_AUTOMAKE([-Wall])
AC_PROG_CC
AC_PROG_LEX(yywrap)
if test "x$LEX" != xflex; then
  LEX="$SHELL $missing_dir/missing flex"
  AC_SUBST([LEX_OUTPUT_ROOT], [lex.yy])
  AC_SUBST([LEXLIB], [''])
fi
AC_PROG_YACC
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_FILES([
 Makefile
 src/Makefile
])
AC_OUTPUT
