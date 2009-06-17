Name:           fred-server
Version:        2.1.1
Release:        1%{?dist}
Summary:        FRED - CORBA backend C++ server

Group:          Applications/Utils
License:        GPL
URL:            http://fred.nic.cz
Source:         %{name}-%{version}.tar.gz
BuildRoot:	%{_tmppath}/%{name}-%{version}-%{release}-%(%{__id_u} -n)
BuildRequires:  libomniORB4.1-devel, boost-devel, postgresql-devel
Requires: libomniORB4.1, boost, postgresql-libs, fred-pyfred, fred-doc2pdf fred-db

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
%config %{_sysconfdir}/fred/server.conf
%{_sysconfdir}/init.d/fred-server
%{_sbindir}/fred-rifd
%{_sbindir}/fred-adifd
%{_sbindir}/fred-pifd
%{_sbindir}/fred-admin
%{_sbindir}/fred-banking
%{_sbindir}/banking.sh

%changelog
* Mon Sep 07 2008 Jaromir Talir <jaromir.talir@nic.cz>
- initial spec file
