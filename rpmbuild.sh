#!/bin/sh

rpmbuild --define "_topdir `pwd`/rpm" --target x86_64 -bb rpmbuild-libesl-0.3.0.spec
mv rpm/RPMS/x86_64/*.rpm .
rm -rf rpm

rpmbuild --define "_topdir `pwd`/rpm" --target x86_64 -bb rpmbuild-libesl-devel-0.3.0.spec
mv rpm/RPMS/x86_64/*.rpm .
rm -rf rpm
