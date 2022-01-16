###############################################################################
# Spec file for ESL development files
################################################################################

Summary: C++ Enterprise Support Library development files
Name: libesl-devel
Version: 1.4.0
Release: 1
License: MIT
URL: http://www.sven-lukas.de
Group: System
Packager: Sven Lukas
Requires: libesl = 1.4.0
BuildRoot: ./rpmbuild/

%description
ESL is a C++ API specification to create enterprise application with C++.
This includes:
- profesional logging
- execute processes and process stdin, stdout, stderr
- HTTP client communication
- HTTP server communication
- Streaming/Messaging stuff (Kafka, ...)
- Throwing exceptions with stacktrace
- Database connectivity
- ...
ESL is an API specification. There is no implementation included.
You can use every ESL compatibal implementation (binding) for each subsystem of ESL.
Later you can use another binding without rewriting your application.
There is a free implementation available that you can use. Take a look at libeslx.

You can build and link your application already without using any specific implementation.
But if you create a class that needs an implemetation (e.g. esl::com::http::server::Socket)
you will get a std::runtime_error if you did not previously load an ESL implementation that
implements at least esl::com::http::server::Interface::Socket.

%prep
#echo "BUILDROOT = $RPM_BUILD_ROOT"
#echo "Current path: $PWD"

mkdir -p $RPM_BUILD_ROOT/usr/include/esl-1.4.0
cd ../../src/main
find . -name '*.h' -exec cp --parents {} $RPM_BUILD_ROOT/usr/include/esl-1.4.0 \;
cd ../../rpm/BUILD
ln -s esl-1.4.0/esl $RPM_BUILD_ROOT/usr/include/esl
rm -rf $RPM_BUILD_ROOT/usr/include/esl-1.4.0/esl/caching
rm -rf $RPM_BUILD_ROOT/usr/include/esl-1.4.0/esl/com/mqtt
rm -rf $RPM_BUILD_ROOT/usr/include/esl-1.4.0/esl/com/smtp
rm -rf $RPM_BUILD_ROOT/usr/include/esl-1.4.0/esl/compression

exit

%files
%defattr(644, root, root, 755)
/usr/include/esl-1.4.0
/usr/include/esl

%pre

%post

%postun

%clean
rm -rf $RPM_BUILD_ROOT/usr/include/esl

%changelog
* Sun Jan 16 2022 Sven Lukas <sven.lukas@gmail.com>
  - First prebuild RPM
