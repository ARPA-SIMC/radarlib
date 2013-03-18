TESTS = \
	test-support \
	test-create-PVOL \
	test-create-IMAGE \
	test-create-PROD  \
	test-polar-volume  \
	test-prod-splitter \
	test-visitor

check_PROGRAMS = \
		 test-support \
		 test-polar-volume \
		 test-create-PVOL  \
		 test-create-IMAGE \
		 test-create-PROD \
		 test-prod-splitter \
		 test-visitor


test_support_SOURCES = test-support.cc
test_support_LDADD = $(top_builddir)/radarlib/libradar_static.la
test_support_CPPFLAGS = -I$(top_srcdir) -I$(top_builddir) -DTESTDIR='"$(abs_srcdir)"'

test_polar_volume_SOURCES = test-polar-volume.cc
test_polar_volume_LDADD = $(top_builddir)/radarlib/libradar_static.la
test_polar_volume_CPPFLAGS = -I$(top_srcdir) -I$(top_builddir) -DTESTDIR='"$(abs_srcdir)"'

test_create_PVOL_SOURCES = test-create-PVOL.cc
test_create_PVOL_LDADD = $(top_builddir)/radarlib/libradar_static.la
test_create_PVOL_CPPFLAGS = -I$(top_srcdir) -I$(top_builddir) -DTESTDIR='"$(abs_srcdir)"'

test_create_IMAGE_SOURCES = test-create-IMAGE.cc
test_create_IMAGE_LDADD = $(top_builddir)/radarlib/libradar_static.la
test_create_IMAGE_CPPFLAGS = -I$(top_srcdir) -I$(top_builddir) -DTESTDIR='"$(abs_srcdir)"'

test_create_PROD_SOURCES = test-create-PROD.cc
test_create_PROD_LDADD = $(top_builddir)/radarlib/libradar_static.la
test_create_PROD_CPPFLAGS = -I$(top_srcdir) -I$(top_builddir) -DTESTDIR='"$(abs_srcdir)"'

test_prod_splitter_SOURCES = test-prod-splitter.cc
test_prod_splitter_LDADD = $(top_builddir)/radarlib/libradar_static.la
test_prod_splitter_CPPFLAGS = -I$(top_srcdir) -I$(top_builddir) -DTESTDIR='"$(abs_srcdir)"'

test_visitor_SOURCES = test-visitor.cc
test_visitor_LDADD = $(top_builddir)/radarlib/libradar_static.la
test_visitor_CPPFLAGS = -I$(top_srcdir) -I$(top_builddir) -DTESTDIR='"$(abs_srcdir)"'

CLEANFILES = \
	     ETOP-10_HGHT_200001020304.h5 \
	     IMAGE.h5 \
	     PPI-0.5_DBZH_200001020304.h5 \
	     PPI-0.5_TH_200001020304.h5 \
	     PROD.h5 \
	     PVOL.h5
