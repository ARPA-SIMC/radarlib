%global releaseno 1

# Note: define _srcarchivename in CI build only.
%{!?srcarchivename: %global srcarchivename %{name}-%{version}-%{releaseno}}

Summary:    libradar shared library
Name:       radarlib
Version:    1.4.6
Release:    %{releaseno}
License:    GPL
Group:      Applications/Meteo
URL:        https://github.com/arpa-simc/%{name}
Source0:    https://github.com/arpa-simc/%{name}/archive/v%{version}-%{releaseno}.tar.gz#/%{srcarchivename}.tar.gz

BuildRequires:  autoconf
BuildRequires:  libtool
BuildRequires:  gcc-c++
BuildRequires:  hdf5-devel
BuildRequires:  doxygen


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
%setup -q -n %{srcarchivename}
sh autogen.sh

%build
%configure --disable-static
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
%exclude %{_libdir}/libradar.la
%{_libdir}/pkgconfig/%{name}.pc

%files doc
%defattr(-,root,root,-)
%doc %{_docdir}/%{name}

%changelog
* Fri May 28 2021 Emanuele Di Giadcomo <edigiacomo@arpae.it> - 1.4.6-1
- RADARLIB_SKIP_CHECK_VERSION environment variable

* Thu May 27 2021 Daniele Branchini <dbranchini@arpae.it> - 1.4.5-1
- Fix C++17 errors (#3)

* Wed Mar 14 2018 Daniele Branchini <dbranchini@arpae.it> - 1.4.4-2
- Cleanup for travis integration

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
