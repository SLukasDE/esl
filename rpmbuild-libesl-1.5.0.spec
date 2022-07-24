###############################################################################
# Spec file for ESL library
################################################################################

Summary: C++ Enterprise Support Library
Name: libesl
Version: 1.5.0
Release: 1
License: MIT
URL: http://www.sven-lukas.de
Group: System
Packager: Sven Lukas
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

mkdir -p $RPM_BUILD_ROOT/usr/lib64
cp -a ../../build/esl/1.5.0/variants/trace/architecture/linux-gcc/link-static/libesl.a $RPM_BUILD_ROOT/usr/lib64
cp -a ../../build/esl/1.5.0/variants/trace/architecture/linux-gcc/link-dynamic/libesl.so $RPM_BUILD_ROOT/usr/lib64/libesl.so.1.5.0
ln -s libesl.so.1.5.0 $RPM_BUILD_ROOT/usr/lib64/libesl.so

exit

%files
%attr(0755, root, root) /usr/lib64/libesl.so.1.5.0
%attr(0777, root, root) /usr/lib64/libesl.so
%attr(0644, root, root) /usr/lib64/libesl.a

%pre

%post

%postun

%clean
rm -rf $RPM_BUILD_ROOT/usr/include/esl

%changelog
* Sat Jul 24 2022 Sven Lukas <sven.lukas@gmail.com>
  - New version 1.5.0
* Sat Jan 16 2022 Sven Lukas <sven.lukas@gmail.com>
  - First prebuild RPM

