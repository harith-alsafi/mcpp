#!/bin/bash

if [ $TRAVIS_OS_NAME = 'linux' ]; then

    sudo apt-get update
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
fi