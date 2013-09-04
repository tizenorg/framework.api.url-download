
Name:	capi-web-url-download
Summary:	CAPI for content download with web url
Version:	1.0.3
Release:	1
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
* Tue Jul 03 2013 Jungki Kwak <jungki.kwak@samsung.com>
- Add enum error about smack deny

* Wed Jun 12 2013 Jungki Kwak <jungki.kwak@samsung.com>
- Remove the define of download service operation
- Update doxygen comments
- Remove unused file

* Tue May 7 2013 Kwangmin Bang <justine.bang@samsung.com>
- add new network type (DOWNLOAD_NETWORK_WIFI_DIRECT)

* Tue Mar 19 2013 Kwangmin Bang <justine.bang@samsung.com>
- new API : download_get_http_header_field_list

* Tue Mar 05 2013 Jungki Kwak <jungki.kwak@samsung.com>
- Changes APIs for notification extra list
- Use download-provider-interface library

* Sat Feb 23 2013 Kwangmin Bang <justine.bang@samsung.com>
- do not close the socket in Interrupted System Call

* Mon Feb 18 2013 Kwangmin Bang <justine.bang@samsung.com>
- use invalid pointer
- return wrong state in _download_change_dp_state()

* Thu Jan 31 2013 Kwangmin Bang <justine.bang@samsung.com>
- support new state of provider

* Tue Jan 29 2013 Jungki Kwak <jungki.kwak@samsung.com>
- Check invalid download id when set the callback
- Create new slot when set callback for the request exist only in provider

* Mon Jan 28 2013 Kwangmin Bang <justine.bang@samsung.com>
- simple launch provider without dbus interface
- Modify the name of license and add notice file
- refer wrong address after free

* Tue Jan 08 2013 Jungki Kwak <jungki.kwak@samsung.com>
- Update doxygen comments
- Add soversion to shared library file
- Remove unnecessary dependency and configuration
- Removed deprecated APIs

* Fri Dec 21 2012 Kwangmin Bang <justine.bang@samsung.com>
- Remove duplicated dlog message
- Modify license information at spec file
- Support ECHO command

* Fri Dec 14 2012 Kwangmin Bang <justine.bang@samsung.com>
- Resolve prevent defect
- Remove old source codes
- Add missed boiler plate
- the limitation of the number of download ID which can be created at same time
- Update comments about state
- Update comments

* Fri Nov 30 2012 Kwangmin Bang <justine.bang@samsung.com>
- support DBUS-activation
- [Prevent Defect] The same expression occurs on both sides of an operator

* Tue Nov 27 2012 Jungki Kwak <jungki.kwak@samsung.com>
- Remove deprecated APIs
- Add an error code about download id
- Change the name of notification API
- Add APIs for notification extra param
- Update comments and add some error code

* Fri Nov 16 2012 Jungki Kwak <jungki.kwak@samsung.com>
- Three APIs will be deprecated
- Operands don't affect result
- Add new CAPIs to register notification message
- Add to add, get and remove http header values
- Modify comments for getting file name
- send pid from client when no support SO_PEERCRED

* Thu Nov 01 2012 Kwangmin Bang <justine.bang@samsung.com>
- prevent duplicated event thread
- print dlog message with thread id
- enhance mutex for event thread

* Wed Oct 31 2012 Jungki Kwak <jungki.kwak@samsung.com>
- enhance mutex for event thread

* Mon Oct 29 2012 Kwangmin Bang <justine.bang@samsung.com>
- fix the defects found by prevent tool
- Thread Safe APIs
- increase the timeout of socket
- do not disconnect socket in case of timeout

* Thu Oct 24 2012 Kwangmin Bang <justine.bang@samsung.com>
- fix prevent defects
- Remove TCs about removed API
- arrange the usage of mutex for IPC

* Tue Oct 23 2012 Kwangmin Bang <justine.bang@samsung.com>
- check IPC connection at the head of All APIs
- use write API instead of send API
- apply sending timeout for socket

* Mon Oct 22 2012 Jungki Kwak <jungki.kwak@samsung.com>
- Resolve the lockup when client app is crashed
- Prevent the crash by calling url_download_destory twice
- Remove memory leak code by fixing of clients

* Fri Oct 19 2012 Kwangmin Bang <justine.bang@samsung.com>
- wrapping Handle based CAPI to ID based CAPI
- Call the progress callback when total size of the content is zero.

* Fri Oct 12 2012 Jungki Kwak <jungki.kwak@samsung.com>
- Fix the crash when clear invalid socket from FD_SET
- Install LICENSE file.

* Fri Sep 21 2012 Jungki Kwak <jungki.kwak@samsung.com>
- Apply a default manifest file.

* Mon Sep 18 2012 Kwangmin Bang <justine.bang@samsung.com>
- fix the crash by referring invalid handle
- Add function to release headers
- Add exception code when fail to reconnect socket
- add license
- fix the error and warning of spec file

* Fri Sep 07 2012 Kwangmin Bang <justine.bang@samsung.com>
- fix timeout thread can run exactly

* Thu Sep 06 2012 Kwangmin Bang <justine.bang@samsung.com>
- check the state before clear socket
- add limitation in already completed state
- add checking INVALID_STATE error

* Tue Sep 04 2012 Jungki Kwak <jungki.kwak@samsung.com>
- Remove unused code which is base on libdownload-agent
- Change the name of application operation
- Add exception handling for non requestid
- Call clear_provider after getting the state
- url_download_get_state return IO error
- Resolve prevent defects

* Mon Sep 03 2012 Kwangmin Bang <justine.bang@samsung.com>
- stop the download even if no socket or callback
- pause/resume the download even if no socket or callback
- calling stopped callback in error case
- request STOP for free after finished download

* Thu Aug 30 2012 Kwangmin Bang <justine.bang@samsung.com>
- maxfd should be updated before created event thread

* Thu Aug 30 2012 Kwangmin Bang <justine.bang@samsung.com>
- remove duplicated call for creating socket
- fix the crash regarding pthread_kill
- allow to call url_download_stop in case of PAUSED state

* Mon Aug 27 2012 Kwangmin Bang <justine.bang@samsung.com>
- one thread model for event
- get state info from download-provider even if no connection
- fix the bug take a long time to receive first event

* Tue Aug 22 2012 Jungki Kwak <jungki.kwak@samsung.com>
- Enhance the exception handling in event thread
- Resolve a bug about state
- Add to pass service handle data to download daemon

* Mon Aug 17 2012 Jungki Kwak <jungki.kwak@samsung.com>
- Resolve a bug when getting a state
- Add error case for invalid id

* Mon Aug 16 2012 Jungki Kwak <jungki.kwak@samsung.com>
- Add new APIs for notification function
- The TC is changed due to change of url_download_start
- When unseting the callback function, the callback should be initialized although the error is happened.
- It remove the stop function when is called twice when destroying handle
- Add pc requries for app.h

* Mon Aug 08 2012 Jungki Kwak <jungki.kwak@samsung.com>
- Change requestid to INTEGER from String

* Mon Aug 06 2012 Jungki Kwak <jungki.kwak@samsung.com>
- The base model is changed to download provider daemon

