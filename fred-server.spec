Name:           fred-server
Version:        2.19.1
Release:        1%{?dist}
Summary:        FRED - CORBA backend C++ server

Group:          Applications/Utils
License:        GPL
URL:            http://fred.nic.cz
Source:         %{name}-%{version}.tar.gz
BuildRoot:	%{_tmppath}/%{name}-%{version}-%{release}-%(%{__id_u} -n)
BuildRequires:  omniORB-devel, boost-devel, postgresql-devel, gcc-c++, libxml2-devel, libcurl-devel, libidn-devel, fred-idl, mpdecimal, libssh-devel, minizip-devel
Requires: omniORB, boost, postgresql-libs, libxml2, libcurl, libidn, fred-pyfred, fred-doc2pdf fred-db redhat-lsb, mpdecimal

%description
FRED (Free Registry for Enum and Domain) is free registry system for 
managing domain registrations. This package contains binaries for running
CORBA backend server which provides core bussiness logic for it's numerous
clients. 

%prep
%setup

%build
%configure %idldir
make

%install
rm -rf ${RPM_BUILD_ROOT}
make DESTDIR=${RPM_BUILD_ROOT} install

%clean
rm -rf ${RPM_BUILD_ROOT}

%files
%defattr(-,root,root,-)
%config %{_sysconfdir}/fred/*
%{_sysconfdir}/init.d/*
%{_sbindir}/*
%{_docdir}/fred-server/*

%changelog
* Mon Sep 07 2008 Jaromir Talir <jaromir.talir@nic.cz>
- initial spec file
