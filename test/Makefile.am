AM_CPPFLAGS = -I$(top_srcdir) -I$(top_builddir) -DTESTDIR='"$(abs_srcdir)"'

TESTS = \
	test-support \
	test-create-PVOL \
	test-create-IMAGE \
	test-create-PROD  \
	test-polar-volume  \
	test-prod-splitter \
	test-visitor  \
	test-odimh5v21-support \
	test-odimh5v21-create-PVOL \
	test-odimh5v21-polar-volume  \
	test-odimh5v21-create-ETOP \
	test-odimh5v21-create-IMAGE \
	test-odimh5v21-create-PROD  \
	test-odimh5v21-prod-splitter \
	test-odimh5v21-visitor \
	test-odimh5v21-azangle

check_PROGRAMS = \
		 test-support \
		 test-polar-volume \
		 test-create-PVOL  \
		 test-create-IMAGE \
		 test-create-PROD \
		 test-prod-splitter \
		 test-visitor     \
		 test-odimh5v21-support \
		 test-odimh5v21-polar-volume \
		 test-odimh5v21-create-ETOP \
		 test-odimh5v21-create-PVOL \
		 test-odimh5v21-create-IMAGE \
		 test-odimh5v21-create-PROD  \
		 test-odimh5v21-prod-splitter \
		 test-odimh5v21-visitor \
		 test-odimh5v21-azangle

test_support_SOURCES = test-support.cc
test_support_LDADD = $(top_builddir)/radarlib/libradar_static.la

test_polar_volume_SOURCES = test-polar-volume.cc
test_polar_volume_LDADD = $(top_builddir)/radarlib/libradar_static.la

test_create_PVOL_SOURCES = test-create-PVOL.cc
test_create_PVOL_LDADD = $(top_builddir)/radarlib/libradar_static.la

test_create_IMAGE_SOURCES = test-create-IMAGE.cc
test_create_IMAGE_LDADD = $(top_builddir)/radarlib/libradar_static.la

test_create_PROD_SOURCES = test-create-PROD.cc
test_create_PROD_LDADD = $(top_builddir)/radarlib/libradar_static.la

test_prod_splitter_SOURCES = test-prod-splitter.cc
test_prod_splitter_LDADD = $(top_builddir)/radarlib/libradar_static.la

test_visitor_SOURCES = test-visitor.cc
test_visitor_LDADD = $(top_builddir)/radarlib/libradar_static.la

test_odimh5v21_support_SOURCES = test-odimh5v21-support.cc
test_odimh5v21_support_LDADD = $(top_builddir)/radarlib/libradar_static.la

test_odimh5v21_polar_volume_SOURCES = test-odimh5v21-polar-volume.cc
test_odimh5v21_polar_volume_LDADD = $(top_builddir)/radarlib/libradar_static.la

test_odimh5v21_create_PVOL_SOURCES = test-odimh5v21-create-PVOL.cc
test_odimh5v21_create_PVOL_LDADD = $(top_builddir)/radarlib/libradar_static.la

test_odimh5v21_create_IMAGE_SOURCES = test-odimh5v21-create-IMAGE.cc
test_odimh5v21_create_IMAGE_LDADD = $(top_builddir)/radarlib/libradar_static.la

test_odimh5v21_create_PROD_SOURCES = test-odimh5v21-create-PROD.cc
test_odimh5v21_create_PROD_LDADD = $(top_builddir)/radarlib/libradar_static.la

test_odimh5v21_create_ETOP_SOURCES = test-odimh5v21-create-ETOP.cc
test_odimh5v21_create_ETOP_LDADD = $(top_builddir)/radarlib/libradar_static.la

test_odimh5v21_prod_splitter_SOURCES = test-odimh5v21-prod-splitter.cc
test_odimh5v21_prod_splitter_LDADD = $(top_builddir)/radarlib/libradar_static.la

test_odimh5v21_visitor_SOURCES = test-odimh5v21-visitor.cc
test_odimh5v21_visitor_LDADD = $(top_builddir)/radarlib/libradar_static.la

test_odimh5v21_azangle_SOURCES = test-odimh5v21-azangle.cc
test_odimh5v21_azangle_LDADD = $(top_builddir)/radarlib/libradar_static.la

CLEANFILES = \
	     ETOP-10_HGHT_200001020304.h5 \
	     IMAGE.h5 \
	     PPI-0.5_DBZH_200001020304.h5 \
	     PPI-0.5_TH_200001020304.h5 \
	     PROD.h5 \
	     PVOL.h5 \
	     ETOP-ODIMh5V21.h5 \
	     ODIMH5V21_ETOP-10_HGHT_200001020304.h5  \
	     ODIMH5V21_PPI-0.5_TH_200001020304.h5  \
	     PVOL-ODIMH5V21.h5   \
	     IMAGE-ODIMh5V21.h5  \
	     ODIMH5V21_PPI-0.5_DBZH_200001020304.h5 \
	     PROD-ODIMH5V21.h5 \
	     ODIMH5V21_CAPPI-500_DBZH_200001020304.h5 \
	     ODIMh5V21_HVMI_DBZH_200001020304.h5      \
	     ODIMH5V21_PCAPPI-500_DBZH_200001020304.h5 \
	     ODIMh5V21_RR_ACRR_200001020304.h5        \
	     ODIMh5V21_VIL-10-100_DBZH_200001020304.h5

