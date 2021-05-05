<p align="center">
  <img width="200" height="250" src="mcpp.png">
</p>

<a href="https://www.gnu.org/licenses/gpl-3.0" target="_blank">![License: GPL v3](https://img.shields.io/badge/license-GPLv3-blue)</a>
<a href="https://github.com/harith-alsafi/mcpp/releases" target="_blank">![Version](https://img.shields.io/badge/version-1.0-blue)</a>
<a href="https://travis-ci.org/github/harith-alsafi/mcpp/builds" target="_blank">![Build](https://img.shields.io/badge/windows-passing-brightgreen)</a>
<a href="https://travis-ci.org/github/harith-alsafi/mcpp/builds" target="_blank">![Build Status](https://img.shields.io/badge/windows-passing-brightgreen)</a>
<a href="https://github.com/harith-alsafi/mcpp/issues" target="_blank">![Github Issues](https://img.shields.io/badge/issues-0%20open-yellow)</a>

# Table of content 
- [Features](#features)
- [Compiling](#compiling)
  * [Linux Compilation](#linux-compilation)
  * [Macos Compilation](#macos-compilation)
  * [Windows Compilation](#windows-compilation)
  * [Compilation flags](#compilation-flags)
- [Usage](#usage)
# Features
* mcpp (Math for C Plus Plus) is **cross platform**,  **templated math library** that can be used without compiling (except for the plotting functions). 
* By only including ``mcpp.hpp`` file you get all the functions with their implementations into your code apart from the plotting functionality
* To use the plotting functionality you need to [compile](#compiling) the library as the plotting functionality uses [SFML](https://www.sfml-dev.org/index.php) and compiled as a shared library
* Unit testing is done using [Google test](https://github.com/google/googletest)
* The library is targeted towards engineers and mathematicians
* Main targeted math sectors  :
    * Linear algebra 
    * Normal Algebra 
    * Statistics 
    * Calculus 
    * Vectors 
# Compiling 
* The compiling process is mainly for the plotting functionality if you don't want that then you can just include the header files and you are good to go
* If you want to install the header files into a standard directory then follow the compiling process below (without SFML) and add this [cmake flag](#compilation-flags)
* The scripts are also made to compile the library with the plot functionality 
* Tested Platfroms 
    * Linux Ubuntu 18.04
    * macOS 10.13 with xcode 9.4.1
    * Windows 10 version 1809
* Dependinceis 
    * cmake version 3.13 or higher
    * SFML version 2.5 or higher (for plots)
    * GNU c++ compiler version 6.1 ot higher (C++ 14 features)
    * GNU make version 4.1 or higher

## Linux Compilation

* Run the following script or follow the steps below
```
cd scripts
chmod 755 linux.sh
./linux.sh
```
1) Install SFML dependencies (if needed)
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
2) Cmake new version (if needed)
```
CMAKE_URL="https://cmake.org/files/v3.19/cmake-3.19.0-Linux-x86_64.tar.gz"
mkdir cmake && wget --quiet -O - ${CMAKE_URL} | tar --strip-components=1 -xz -C cmake 
```
3) Build 
```
mkdir build
cd build
# or use ../cmake/bin/cmake .. -DNO-TEST=True 
cmake .. -DNO-TEST=True
make
sudo make install
```
## Macos Compilation
* Run the following script or follow the steps below
```
cd scripts
chmod 755 macos.sh
./macos.sh
```
1) Normal build 
```
mkdir build
cd build
cmake .. -DNO-TEST=True  
make
sudo make install
```
## Windows Compilation
* Run the following script or follow the steps below
```
.\windows.ps1
```
1) Install [chocolatey](https://chocolatey.org/install) (if not installed)
```
Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1'))
```
2) Install C++ compilers (if needed)
```
choco install mingw
choco install cmake
choco install make
choco install gsudo
```
3) Building 
```
mkdir build
cd build
cmake -G "Unix Makefiles" .. -DNO-TEST=True
make 
sudo make install
```

## Compilation flags 
* No plotting functionality 
    ```
    cmake .. -DNO-TEST=True -DNO-PLOT=True
    ```
* Enable Unit tests
    ```
    cmake .. -DNO-TEST=False
    ``` 

# Usage 
* No plot usage
    * Non standard path install
        ```cpp
        #include "includes/mcpp.hpp"
        ```  
    * standard install 
        ```cpp
        #include <mcpp/mcpp.hpp>
        ```  
    * No compilation flags needed 
* Plot usage 
    * Non standard path install
        * Header 
        ```cpp
        #include "includes/plot.hpp"
        ```  
        * Compilation 
        ```
        g++ TEST.cpp -L"build/libmcpp.so"
        ```
    * standard install 
        * Header
        ```cpp
        #include <mcpp/plot.hpp>
        ```  
        * Compilation 
        ```bash
        g++ main.cpp -lmcpp
        ```



* Please see the full [documentation](https://harith-alsafi.github.io/mcpp-doc/) for detailed usage on the classes and functions 
* You can see the class refrence as a [pdf](doc/latex/refman.pdf) or an [html](doc/html/index.html)
 
