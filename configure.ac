AC_INIT([RadarLib], [1.2.0], [guidobilli@gmail.com], [radarlib],
        [http://www.smr.arpa.emr.it/software/radarlib])

PACKAGE_SO_VERSION="$PACKAGE_VERSION"
PACKAGE_LT_VERSION="3:0:2"

AC_PREREQ([2.59])
AM_INIT_AUTOMAKE([1.10 foreign -Wall no-define subdir-objects nostdinc])

AM_PROG_LIBTOOL

AM_PROG_INSTALL

AC_LANG_C
AC_LANG_CPLUSPLUS
AC_PROG_CC
AC_PROG_CXX
AC_PROG_MAKE_SET

AC_HEADER_STDC

#look for HDF5 ANSI C header
AC_CHECK_HEADER(hdf5.h,,AC_MSG_ERROR([required HDF5 header file missing]))

#look for HDF5 ANSI C library
AC_CHECK_LIB(hdf5, H5open)

#look for HDF5 C++ header
AC_CHECK_HEADER(H5Cpp.h,,AC_MSG_ERROR([required HDF5 C++ header file missing]))

#look for HDF5 C++ library
AC_CHECK_LIB(hdf5_cpp, H5open)

AC_SUBST([PACKAGE_SO_VERSION])
AC_SUBST([PACKAGE_LT_VERSION])

AC_CONFIG_FILES([Makefile
                 radarlib.pc
		 radarlib/Makefile
		 test/Makefile
                 doc/Makefile
		 doc/Doxyfile
                 examples/Makefile])
AC_OUTPUT




