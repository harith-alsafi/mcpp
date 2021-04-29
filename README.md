<a href="https://www.gnu.org/licenses/gpl-3.0" target="_blank">![License: GPL v3](https://img.shields.io/badge/license-GPLv3-blue)</a>
<a href="https://github.com/harith-alsafi/mcpp/releases" target="_blank">![Version](https://img.shields.io/badge/version-1.0.1-blue)</a>
<a href="https://www.travis-ci.com/github/harith-alsafi/mcpp/builds" target="_blank">![Build Status](https://img.shields.io/badge/linux%2Fosx-passing-brightgreen)</a>
<a href="https://www.travis-ci.com/github/harith-alsafi/mcpp/builds" target="_blank">![Build Status](https://img.shields.io/badge/windows-passing-brightgreen)</a>
<a href="https://github.com/harith-alsafi/mcpp/issues" target="_blank">![Github Issues](https://img.shields.io/badge/issues-0%20open-yellow)</a>

# Table of content 

# Features
Its a cross platform Math Library for C++

# Compiling 
* Platfroms 
    * Linux Ubuntu 18.04
    * macOS 10.13 with xcode 9.4.1
    * Windows 10 version 1809
* Dependinceis 
    * cmake version 3.13 or higher
    * SFML version 2.5 or higher 
    * GNU c++ compiler version 6.1 ot higher (C++ 14 features)
    * GNU make version 4.1 or higher 
* Compilation
    * Linux
        * Run the script for a one step build or follow the below steps
            ```
            cd scripts
            chmod 755 linux.sh
            ./linux.sh
            ```
        * Install SFML 
            * Through package manager
                ```
                sudo apt-get install libsfml-dev
                ```
            * Through cmake but you need the following dependinceis 
                ```
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
                ```
        * Cmake new version 
            ```
            CMAKE_URL="https://cmake.org/files/v3.19/cmake-3.19.0-Linux-x86_64.tar.gz"
            mkdir cmake && wget --quiet -O - ${CMAKE_URL} | tar --strip-components=1 -xz -C cmake 
            ```
        * Build 
            ```
            mkdir build
            cd build
            cmake .. # or ../cmake/bin/cmake .. 
            make
            sudo make install
            ```
    * Macos 
        * Run the script for a one step build or follow the below steps
            ```
            cd scripts
            chmod 755 macos.sh
            ./macos.sh
            ```
        * Normal build 
            ```
            mkdir build
            cd build
            cmake .. 
            make
            sudo make install
            ```
    * Windows 
* No plotting functionality 
    * Linux / OSX
    ```
    mkdir build
    cd build
    cmake .. -DNO-PLOT=True
    make
    sudo make install
    ```
    * Windows 
# Refrencing 
# Usage 
