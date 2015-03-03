
Name:	capi-web-url-download
Summary:	CAPI for content download with web url
Version:	1.1.1
Release:	0
Group:		Development/Libraries
License:	Apache-2.0
URL:		https://review.tizen.org/git/?p=platform/core/api/url-download.git;a=summary
Source0:	%{name}-%{version}.tar.gz
BuildRequires: pkgconfig(capi-base-common)
BuildRequires: pkgconfig(dlog)
BuildRequires: pkgconfig(bundle)
BuildRequires: pkgconfig(download-provider-interface)
BuildRequires: cmake

%description
Core APIs for the content download with web url

%package devel
Summary:	CAPI web url development files
Group:		Development/Libraries
Requires:	%{name} = %{version}-%{release}

%description devel
CAPI for content downloading with web url (development files)

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
