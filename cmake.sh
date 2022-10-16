#!/bin/sh

#find | grep \\\./src/main | grep \\\.h\\\|\\\.cpp > files.txt
export PATH=${HOME}/cmake-3.24.2-linux-x86_64/bin:$PATH
export CMAKE_PREFIX_PATH=${HOME}/usr/local/lib/cmake

# *****************
# *** (0) Clean ***
# *****************

rm -rf ~/usr
rm -rf build

# ***************************
# *** (1) Create Makefile ***
# ***************************

#mkdir build
#cd build
#cmake ..
#cd ..
cmake -S . -B build

# *****************
# *** (2) Build ***
# *****************

#cd build
#make
#cd ..
cmake --build build

# *******************
# *** (3) Install ***
# *******************

cd build
make DESTDIR=${HOME} install
cd ..
