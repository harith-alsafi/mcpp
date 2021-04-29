#!/usr/bin/bash
sudo apt-get update

# SFML
sudo apt-get -y install libsfml-dev

# cmake 
CMAKE_URL="https://cmake.org/files/v3.19/cmake-3.19.0-Linux-x86_64.tar.gz"
mkdir cmake && wget --quiet -O - ${CMAKE_URL} | tar --strip-components=1 -xz -C cmake 

# build
mkdir build
cd build
../cmake/bin/cmake .. 
make
sudo make install