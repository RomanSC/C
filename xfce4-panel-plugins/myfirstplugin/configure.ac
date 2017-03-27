#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.
#
# For a quide on autotools check out:
# https://www.youtube.com/watch?v=4q_inV9M_us

# Name of program, version, and contact information
AC_INIT([myfirstplugin], [1.0], [https://github.com/RomanSC])

# Autoconf prerequisite; autoconf --version must be
# at least 2.69
AC_PREREQ([2.69])

# Safety check, make sure this file exists
AC_CONFIG_SRCDIR([myfirstplugin.c])

# ???
AC_CONFIG_HEADERS([config.h])

# Auxillary files
# AC_CONFIG_AUX_DIR([build-aux])

# ???
AM_INIT_AUTOMAKE([1.11 -Wall -Werror])

# Which C compiler
AC_PROG_CC([gcc])

# To find a C++ compiler
# AC_PROG_CXX([g++])

#
AC_CONFIG_FILES([Makefile])

# Output of makefiles
AC_OUTPUT(makefile src/makefile doc/makefile examples/makefile man/makefile scripts/makefile)
