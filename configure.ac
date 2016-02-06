AC_INIT([libtz], [0.1], [ilya.novoselov@gmail.com],
	[libtz], [https://github.com/nullie/libtz])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])

AC_PROG_CC
AC_LANG_C

AC_PROG_INSTALL
AC_PROG_MAKE_SET

AM_PROG_LIBTOOL

AC_HEADER_STDC

AM_PROG_CC_C_O

gl_VISIBILITY

PKG_CHECK_MODULES([CHECK], [check >= 0.9.4])

AC_OUTPUT(Makefile src/Makefile tests/Makefile)
