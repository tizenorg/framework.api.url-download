
Name:	capi-web-url-download
Summary:	CAPI for content download with web url
Version:	1.2.6
Release:	0
Group:		Development/Libraries
License:	Apache License, Version 2.0
URL:		N/A
Source0:	%{name}-%{version}.tar.gz
BuildRequires: pkgconfig(capi-base-common)
BuildRequires: pkgconfig(dlog)
BuildRequires: pkgconfig(capi-appfw-application)
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
export CFLAGS="$CFLAGS -DTIZEN_DEBUG_ENABLE"
export CXXFLAGS="$CXXFLAGS -DTIZEN_DEBUG_ENABLE"
export FFLAGS="$FFLAGS -DTIZEN_DEBUG_ENABLE"
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

