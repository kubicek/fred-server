#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT([fred-server], [1.10.1])
AC_CONFIG_SRCDIR(src/corba/server.cc)
AC_CONFIG_HEADER([config.h])
AC_CONFIG_MACRO_DIR([m4])

# doxygen
DX_HTML_FEATURE(OFF)
DX_CHM_FEATURE(OFF)
DX_CHI_FEATURE(OFF)
DX_MAN_FEATURE(OFF)
DX_RTF_FEATURE(OFF)
DX_XML_FEATURE(OFF)
DX_PDF_FEATURE(OFF)
DX_PS_FEATURE(OFF)
DX_INIT_DOXYGEN(fred-server, doxy.conf, [doc])

AM_INIT_AUTOMAKE
m4_pattern_allow([^AC_MSG_])

AC_DEFUN([AS_AC_TEST_CORBA_PORTS],
[
 AC_MSG_CHECKING([whether CORBA ports are unique])
 if test $PIFDPORT -eq $RIFDPORT -o $PIFDPORT -eq $ADIFDPORT -o $RIFDPORT -eq $ADIFDPORT; then
	 AC_MSG_RESULT([no])
	 AC_MSG_ERROR([each of CORBA port must be unique])
 else
	 AC_MSG_RESULT([yes])
 fi
])

# Checks for programs.
AC_PROG_AWK
AC_PROG_CXX
AC_PROG_CC
AC_PROG_INSTALL
AC_PROG_MAKE_SET
AC_PROG_RANLIB

PKG_PROG_PKG_CONFIG

# Checks for libraries.
AC_CHECK_LIB([pthread], [pthread_exit])

# Check for omniORB
PKG_CHECK_MODULES(OMNIORB4, [omniORB4, omniDynamic4, omnithread3])

AX_BOOST_BASE
AX_BOOST_DATE_TIME
AX_BOOST_PROGRAM_OPTIONS
AX_BOOST_REGEX

# For logger class when log type is console or custom file
AX_BOOST_THREAD 
# For filter serialization to xml
AX_BOOST_SERIALIZATION


# Checks for PostgreSQL headers and libs
AX_LIB_POSTGRESQL(8.0)

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS(
	[arpa/inet.h stdlib.h string.h sys/socket.h \
	sys/time.h syslog.h unistd.h]
)

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_TYPE_SIZE_T
AC_HEADER_TIME
AC_STRUCT_TM

# Checks for library functions.
AC_FUNC_MALLOC
AC_FUNC_MKTIME
AC_TYPE_SIGNAL
AC_FUNC_VPRINTF
AC_CHECK_FUNCS([gettimeofday memset strcasecmp strncasecmp strspn])

# fred database host
AC_ARG_WITH([dbhost], [AS_HELP_STRING([--with-dbhost],
			[Database host name [localhost]])],
			[AC_SUBST([DBHOST], [$withval])],
			[AC_SUBST([DBHOST], [localhost])])

# fred database port
AC_ARG_WITH([dbport], [AS_HELP_STRING([--with-dbport],
			[Database port number [5432]])],
			[AC_SUBST([DBPORT], [$withval])],
			[AC_SUBST([DBPORT], [5432])])

# fred database name
AC_ARG_WITH([dbname], [AS_HELP_STRING([--with-dbname],
			[Database name [fred]])],
			[AC_SUBST([DBNAME], [$withval])],
			[AC_SUBST([DBNAME], [fred])])

# fred database user name
AC_ARG_WITH([dbuser], [AS_HELP_STRING([--with-dbuser],
			[Database user name [fred]])],
			[AC_SUBST([DBUSER], [$withval])],
			[AC_SUBST([DBUSER], [fred])])

# fred database password
AC_ARG_WITH([dbpass], [AS_HELP_STRING([--with-dbpass],
			[Database access password [password]])],
			[AC_SUBST([DBPASS], [$withval])],
			[AC_SUBST([DBPASS], [password])])

# corba nameservice host
AC_ARG_WITH([nshost], [AS_HELP_STRING([--with-nshost],
			[CORBA nameservice host name [localhost]])],
			[AC_SUBST([NSHOST], [$withval])],
			[AC_SUBST([NSHOST], [localhost])])

# corba nameservice context
AC_ARG_WITH([nscontext], [AS_HELP_STRING([--with-nscontext],
			[CORBA nameservice context name [fred]])],
			[AC_SUBST([contextname], [$withval])],
			[AC_SUBST([contextname], [fred])])
#put context name into config.h file
AC_DEFINE_UNQUOTED([CONTEXT_NAME], [["]$contextname["]], [name of CORBA context])

# cirba rifd port
AC_ARG_WITH([rifdport], [AS_HELP_STRING([--with-rifdport],
			[CORBA fred-rifd port [2222]])],
			[AC_SUBST([RIFDPORT], [$withval])],
			[AC_SUBST([RIFDPORT], [2222])])
#pifd port
AC_ARG_WITH([pifdport], [AS_HELP_STRING([--with-pifdport],
			[CORBA fred-pifd port [2223]])],
			[AC_SUBST([PIFDPORT], [$withval])],
			[AC_SUBST([PIFDPORT], [2223])])
#adifd port
AC_ARG_WITH([adifdport], [AS_HELP_STRING([--with-adifdport],
			[CORBA fred-adifd port [2224]])],
			[AC_SUBST([ADIFDPORT], [$withval])],
			[AC_SUBST([ADIFDPORT], [2224])])

AS_AC_TEST_CORBA_PORTS()

#expand paths for bindir, sbindir and datarootdir variable
AS_AC_EXPAND([BINDIR], [$bindir])
AS_AC_EXPAND([DATAROOTDIR], [$datarootdir])
AS_AC_EXPAND([SBINDIR], [$sbindir])
AS_AC_EXPAND([SYSCONFDIR], [$sysconfdir])
AS_AC_EXPAND([LOCALSTATEDIR], [$localstatedir])

#put context name into config.h file
AC_DEFINE_UNQUOTED([CONFIG_FILE], [["]$SYSCONFDIR/fred/server.conf["]], [location of fred config file])

#location of idl files, when user use this option during configuration
#process, exactly given path will be used, otherwise will be used
#`$datarootdir/idl/fred/', where dataroot dir is `$prefix/share'
#and prefix is by default `/usr/local'. So whole path is
#`/usr/local/share/idl/fred/'
AC_ARG_WITH(
	[idldir], 
	[AS_HELP_STRING(
		[--with-idldir],
		[location of idl directory containing IDL interfaces [DATAROOTDIR/idl/fred/]]
	)],
	[AC_SUBST([IDLDIR], [$withval])],
	[AC_SUBST([IDLDIR], [$DATAROOTDIR/idl/fred/])]
)

AC_CHECK_FILE(
	[$IDLDIR/ccReg.idl], 
	[], 
	[AC_MSG_ERROR(
		[directory "$IDLDIR" does not contain ccReg.idl 
		(use --with-idldir)]
	)]
)

AC_ARG_WITH(
  [libidn], 
  [AC_HELP_STRING(
    [--with-libidn=[DIR]],
    [Support IDN (needs GNU Libidn)]
  )],
  libidn=$withval, 
  libidn=yes
)
if test "$libidn" != "no" ; then
  if test "$libidn" == "yes"; then
    PKG_CHECK_MODULES(LIBIDN, libidn >= 0.5.18, [plibidn=yes], [plibidn=no])
    AC_SUBST(LIBIDN_CFLAGS)
    AC_SUBST(LIBIDN_LIBS)
  fi
  if test "$plibidn" != "yes" ; then
    if test "$libidn" != "yes"; then
      LDFLAGS="${LDFLAGS} -L$libidn/lib"
      CPPFLAGS="${CPPFLAGS} -I$libidn/include"
    fi
    AC_CHECK_HEADER(
      idna.h,
      [AC_CHECK_LIB(
        idn, stringprep_check_version,
        [libidn=yes LIBS="${LIBS} -lidn"], libidn=no
       )],
      libidn=no
    )
  fi
fi
if test "$libidn" == "no"; then
  AC_MSG_ERROR([Libidn not found])
fi

AC_CONFIG_FILES([Makefile
                 util/Makefile
                 util/db/Makefile
		 util/log/Makefile
		 util/conf/Makefile
		 src/Makefile
		 src/old_utils/Makefile
		 src/model/Makefile
		 src/register/Makefile
		 src/corba/Makefile
		 src/corba/admin/Makefile
		 src/corba/epp/Makefile
		 src/cli_admin/Makefile
		 fred-server.spec
		 conf/server.conf
		 init-scripts/fred-server
		 src/cli_admin/banking.sh])
AC_OUTPUT