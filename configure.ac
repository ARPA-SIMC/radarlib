AC_INIT([RadarLib], [1.4.6], [guidobilli@gmail.com], [radarlib],
        [http://www.arpa.emr.it/dettaglio_documento.asp?id=2914&idlivello=64])

PACKAGE_SO_VERSION="$PACKAGE_VERSION"
PACKAGE_LT_VERSION="5:0:4"

AC_PREREQ([2.59])
AM_INIT_AUTOMAKE([1.10 foreign -Wall no-define subdir-objects nostdinc])
AC_CONFIG_MACRO_DIR([m4])

LT_INIT()
LT_LANG([C++])
AM_PROG_LIBTOOL

AC_PROG_INSTALL

AC_LANG([C++])
AC_PROG_CC
AC_PROG_CXX
AC_PROG_MAKE_SET

AX_CXX_COMPILE_STDCXX_11

AC_HEADER_STDC

PKG_CHECK_MODULES([HDF5], [hdf5], [have_hdf5=yes], [have_hdf5=no])
if test $have_hdf5 = yes
then
        PKG_CHECK_MODULES([HDF5], [hdf5])
	AC_SUBST(HDF5_CFLAGS)
 	HDF5_LIBS="$HDF5_LIBS -lhdf5_cpp"
	AC_SUBST(HDF5_LIBS)
else
	#look for HDF5 ANSI C header
	AC_CHECK_HEADER(hdf5.h,,AC_MSG_ERROR([required HDF5 header file missing]))

	#look for HDF5 ANSI C library
	AC_CHECK_LIB(hdf5, H5open)

	#look for HDF5 C++ header
	AC_CHECK_HEADER(H5Cpp.h,,AC_MSG_ERROR([required HDF5 C++ header file missing]))

	#look for HDF5 C++ library
	AC_CHECK_LIB(hdf5_cpp, H5open)
fi

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




