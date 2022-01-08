###############################################################################
# Spec file for ESL library
################################################################################
#
Summary: ESL library
Name: libesl
Version: 0.3.0
Release: 1
License: MIT
URL: http://www.sven-lukas.de
Group: System
Packager: Sven Lukas
BuildRoot: ./rpmbuild/

%description
A collection of utility scripts for testing RPM creation.

%prep
################################################################################
# Create the build tree and copy the files from the development directories    #
# into the build tree.                                                         #
################################################################################

#echo "BUILDROOT = $RPM_BUILD_ROOT"

mkdir -p $RPM_BUILD_ROOT/usr/lib64
cp -a ../../build/esl/0.3.0/variants/trace/architecture/linux-gcc/link-static/libesl.a $RPM_BUILD_ROOT/usr/lib64
cp -a ../../build/esl/0.3.0/variants/trace/architecture/linux-gcc/link-dynamic/libesl.so $RPM_BUILD_ROOT/usr/lib64/libesl.so.0.3.0
ln -s libesl.so.0.3.0 $RPM_BUILD_ROOT/usr/lib64/libesl.so

exit

%files
%attr(0755, root, root) /usr/lib64/libesl.so.0.3.0
%attr(0777, root, root) /usr/lib64/libesl.so
%attr(0644, root, root) /usr/lib64/libesl.a

%pre

%post

%postun

%clean
rm -rf $RPM_BUILD_ROOT/usr/include/esl

%changelog
* Sat Jan 8 2022 Sven Lukas <sven.lukas@gmail.com>
  - First prebuild RPM
