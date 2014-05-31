
Name:	capi-web-url-download
Summary:	CAPI for content download with web url
Version:	1.1.1
Release:	0
Group:		Development/Libraries
License:	Apache License, Version 2.0
URL:		N/A
Source0:	%{name}-%{version}.tar.gz
BuildRequires: pkgconfig(capi-base-common)
BuildRequires: pkgconfig(dlog)
BuildRequires: pkgconfig(bundle)
BuildRequires: pkgconfig(download-provider-interface)
BuildRequires: cmake

%description
CAPI for the content download

%package devel
Summary:	url download
Group:		Development/Libraries
Requires:	%{name} = %{version}-%{release}

%description devel
CAPI for content downloading with web url (developement files)

%prep
%setup -q

%build
%if 0%{?tizen_build_binary_release_type_eng}
export CFLAGS="$CFLAGS -DTIZEN_ENGINEER_MODE"
export CXXFLAGS="$CXXFLAGS -DTIZEN_ENGINEER_MODE"
export FFLAGS="$FFLAGS -DTIZEN_ENGINEER_MODE"
%endif
%cmake .

make %{?jobs:-j%jobs}

%install
rm -rf %{buildroot}
%make_install
mkdir -p %{buildroot}/usr/share/license

%post -p /sbin/ldconfig

%postun -p /sbin/ldconfig

%files
%defattr(-,root,root,-)
%manifest capi-web-url-download.manifest
%{_libdir}/libcapi-web-url-download.so.*
/usr/share/license/%{name}

%files devel
%defattr(-,root,root,-)
%manifest capi-web-url-download.manifest
%{_libdir}/libcapi-web-url-download.so
%{_libdir}/pkgconfig/capi-web-url-download.pc
%{_includedir}/web/download.h
%{_includedir}/web/download_doc.h

%changelog
* Thu Sep 26 2013 Jungki Kwak <jungki.kwak@samsung.com>
- Add error exception code for invalid parameter
- Add a missed deprecate API

* Wed Sep 11 2013 Jungki Kwak <jungki.kwak@samsung.com>
- Add missed code to set manifest file
- Deprecate old APIs for notification
- Add new APIs for notification and bundle data

* Tue Jul 03 2013 Jungki Kwak <jungki.kwak@samsung.com>
- Add enum error about smack deny

* Wed Jun 12 2013 Jungki Kwak <jungki.kwak@samsung.com>
- Remove the define of download service operation
- Update doxygen comments
- Remove unused file

