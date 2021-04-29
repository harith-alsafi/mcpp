#!/usr/bin/bash
sudo apt-get update

# SFML
sudo apt-get -y install libpthread-stubs0-dev
sudo apt-get -y install libgl1-mesa-dev
sudo apt-get -y install libxrandr-dev
sudo apt-get -y install libfreetype6-dev
sudo apt-get -y install libglew1.5-dev
sudo apt-get -y install libjpeg8-dev
sudo apt-get -y install libsndfile1-dev
sudo apt-get -y install libopenal-dev
sudo apt-get -y install libx11-dev
sudo apt-get -y install xorg-dev
sudo apt-get -y install freeglut3-dev
sudo apt-get -y install libudev-dev

# cmake 
CMAKE_URL="https://cmake.org/files/v3.19/cmake-3.19.0-Linux-x86_64.tar.gz"
mkdir cmake && wget --quiet -O - ${CMAKE_URL} | tar --strip-components=1 -xz -C cmake 

# build
mkdir build
cd build
../cmake/bin/cmake .. 
make
sudo make install