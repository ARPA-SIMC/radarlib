Summary:	libradar shared library
Name: 		radarlib
Version: 	1.0
Release: 	499%{dist}
License: 	GPL
Group: 		Applications/Meteo
URL: 		http://arpa.emr.it/sim/
Source0: 	%{name}-%{version}.tar.gz
BuildRoot: 	%{_tmppath}/%{name}-%{version}-%{release}-root
Vendor: 	Guido Billi <guidobilli@gmail.com>
Packager: 	Daniele Branchini <dbranchini@arpa.emr.it>
Requires:       hdf5
BuildRequires:	hdf5-devel zlib-devel

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
%setup -q

%build

%configure
make

%install
rm -rf %{buildroot}
%makeinstall

%clean
rm -rf %{buildroot}

%files
%defattr(-,root,root,-)
%doc 
%{_libdir}/libradar.so*

%files devel
%defattr(-,root,root,-)
%{_includedir}/%{name}/*
%{_libdir}/libradar.a
%{_libdir}/libradar.la
%{_libdir}/pkgconfig/%{name}-%{version}.pc

%files doc
%defattr(-,root,root,-)
%doc %{_docdir}/%{name}

%changelog
* Mon Jan 24 2011 Daniele Branchini <dbranchini@carenza.metarpa> - 1.0-499%{dist}
- Documentation included

* Thu Oct 21 2010 Daniele Branchini <dbranchini@linus.metarpa> - 1.0-444%{dist}
- Upstream changes

* Fri Oct 14 2010 Daniele Branchini <dbranchini@linus.metarpa> - 
- Initial build.
