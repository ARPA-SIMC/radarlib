cdoxdeps = Doxyfile

all: html/index.html

html/index.html: $(cdoxdeps)
	doxygen  $<

install-data-local:
	for pkg in html ; do \
	  test -d $$pkg && \
	  $(mkinstalldirs) $(DESTDIR)$(docdir)/$$pkg && \
	  find $$pkg -type f -exec $(INSTALL_DATA) '{}' $(DESTDIR)$(docdir)/$$pkg/ \; ; \
	done || true

uninstall-local:
	for pkg in html ; do \
	  rm -rf $(DESTDIR)$(docdir)/$${pkg}; \
	done || true

clean-local:
	rm -rf html

dist_doc_DATA = \
		OPERA_2008_03_WP2.1a_InformationModel_UML_2.0.pdf

EXTRA_DIST = \
	     mainpage.dox \
	     FAQ.dox

CLEANFILES = \
	     Doxygen.log
