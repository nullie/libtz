lib_LTLIBRARIES = libtz.la

libtz_la_SOURCES = libtz.c private.h tzfile.h tz.h
libtz_la_CPPFLAGS = -DBUILDING_LIBTZ $(CFLAG_VISIBILITY) -DTZDIR='"${datadir}/zoneinfo"'