###############################################################################
# Spec file for ESL development files
################################################################################
#
Summary: ESL development files
Name: libesl-devel
Version: 0.3.0
Release: 1
License: MIT
URL: http://www.sven-lukas.de
Group: System
Packager: Sven Lukas
Requires: libesl = 0.3.0
BuildRoot: ./rpmbuild/

%description
A collection of utility scripts for testing RPM creation.

%prep
################################################################################
# Create the build tree and copy the files from the development directories    #
# into the build tree.                                                         #
################################################################################

#echo "BUILDROOT = $RPM_BUILD_ROOT"
#echo "Current path: $PWD"

mkdir -p $RPM_BUILD_ROOT/usr/include/esl-0.3.0
cd ../../src/main
find . -name '*.h' -exec cp --parents {} $RPM_BUILD_ROOT/usr/include/esl-0.3.0 \;
cd ../../rpm/BUILD
ln -s esl-0.3.0/esl $RPM_BUILD_ROOT/usr/include/esl
rm -rf $RPM_BUILD_ROOT/usr/include/esl-0.3.0/esl/caching
rm -rf $RPM_BUILD_ROOT/usr/include/esl-0.3.0/esl/com/mqtt
rm -rf $RPM_BUILD_ROOT/usr/include/esl-0.3.0/esl/com/smtp
rm -rf $RPM_BUILD_ROOT/usr/include/esl-0.3.0/esl/compression

exit

%files
%defattr(644, root, root, 755)
/usr/include/esl-0.3.0
/usr/include/esl

%pre

%post

%postun

%clean
rm -rf $RPM_BUILD_ROOT/usr/include/esl

%changelog
* Sat Jan 8 2022 Sven Lukas <sven.lukas@gmail.com>
  - First prebuild RPM
