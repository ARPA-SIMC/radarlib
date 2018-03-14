Summary:	libradar shared library
Name: 		radarlib
Version: 	1.4.4
Release: 	1
License: 	GPL
Group: 		Applications/Meteo
URL:            https://github.com/arpa-simc/%{name}
Source0: 	https://github.com/arpa-simc/%{name}/archive/v%{version}-%{release}.tar.gz#/%{name}-%{version}-%{release}.tar.gz
BuildRoot:      %{_tmppath}/%{name}-%{version}-%{release}-buildroot
Packager: 	Daniele Branchini <dbranchini@arpae.it>
BuildRequires:	libtool, gcc-c++, hdf5-devel, doxygen
Requires:       hdf5


%description
libradar shared library

%package devel
Requires: radarlib = %{version}
Group: Libraries/Meteo
Summary: Development for libradar library

%description devel
Development for libradar library

%package doc
Summary: radarlib documentation
Group: Libraries/Meteo

%description doc
libradar library documentation

%prep
%setup -q -n %{name}-%{version}-%{release}
sh autogen.sh

%build
%configure
make
make check

%install
[ "%{buildroot}" != / ] && rm -rf %{buildroot}
%makeinstall

%clean
[ "%{buildroot}" != / ] && rm -rf %{buildroot}

%files
%defattr(-,root,root,-)
%doc 
%{_libdir}/libradar.so*

%files devel
%defattr(-,root,root,-)
%{_includedir}/%{name}/*
%{_libdir}/libradar.a
%{_libdir}/libradar.la
%{_libdir}/pkgconfig/%{name}.pc

%files doc
%defattr(-,root,root,-)
%doc %{_docdir}/%{name}

%changelog
* Thu Nov 10 2016 Daniele Branchini <dbranchini@arpae.it> - 1.4.4-1
- Fixed bug if a generic product is used

* Wed Jun 22 2016 Daniele Branchini <dbranchini@arpae.it> - 1.4.3-1
- Added Quality at dataset level
- Created two quality groups in each dataset

* Thu Oct 22 2015 Daniele Branchini <dbranchini@arpa.emr.it> - 1.4.2-1%{dist}
- new routine set TX power

* Wed Feb  5 2014 Daniele Branchini <dbranchini@arpa.emr.it> - 1.4.1-39%{dist}
- Using target dataspace not source dataspace

* Thu Apr 18 2013 Daniele Branchini <dbranchini@arpa.emr.it> - 1.4.0-26%{dist}
- Namespace OdimH5v21 for ODIMH5v2.1 support

* Fri Mar 15 2013 Daniele Branchini <dbranchini@arpa.emr.it> - 1.2.0-2%{dist}
- Reflecting upstream changes

* Mon Jan 24 2011 Daniele Branchini <dbranchini@arpa.emr.it> - 1.0-499%{dist}
- Documentation included

* Thu Oct 21 2010 Daniele Branchini <dbranchini@arpa.emr.it> - 1.0-444%{dist}
- Upstream changes
