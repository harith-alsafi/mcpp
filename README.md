<p align="center">
  <img width="200" height="250" src="mcpp.png">
</p> 

<a href="https://www.gnu.org/licenses/gpl-3.0" target="_blank">![License: GPL v3](https://img.shields.io/badge/license-GPLv3-blue)</a>
<a href="https://github.com/harith-alsafi/mcpp/releases" target="_blank">![Version](https://img.shields.io/badge/version-1.0-blue)</a> 
<a href="https://harith-alsafi.github.io/mcpp-doc/" target="_blank">![Doc](https://img.shields.io/badge/doc-mkdocs-blue)</a> 
<a href="https://github.com/harith-alsafi/mcpp/actions/workflows" target="_blank">![Cmake build](https://github.com/harith-alsafi/mcpp/actions/workflows/cmake.yml/badge.svg)</a>
<a href="https://github.com/harith-alsafi/mcpp/actions/workflows" target="_blank">![Dokcer build](https://github.com/harith-alsafi/mcpp/actions/workflows/docker-image.yml/badge.svg)</a>
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
* mcpp (Math for C Plus Plus) is **cross platform**,  **templated math library** that can be used without compiling . 
* It is targeted towards **engineers** and **mathematicians**.
* Used with a very simple and intuitive syntax inspired from Python libraries such as [sympy](https://www.sympy.org/en/index.html), [numpy](https://numpy.org/), [scipy](https://www.scipy.org/) .. etc
* By only including ``mcpp.hpp`` file you get all the functions with their implementations into your code 
* Unit testing is done using [Google test](https://github.com/google/googletest)
* Main targeted math sectors  :
    * Algebra 
    * Statistics 
    * Calculus 
    * Vectors 
    * Signal systems 

# Compiling 
* There is **NO NEED FOR COMPILING** just include the header files right away. 
* You can use the compiling procedure to install everything to your standard path 
* The compiling procedure is only used for the test scripts 
* Tested Platforms 
    * Linux Ubuntu 18.04
    * macOS 10.13 with xcode 9.4.1
    * Windows 10 version 1809
* Dependencies 
    * cmake version 3.13 or higher
    * GNU c++ compiler version 6.1 ot higher (C++ 14 features)
    * GNU make version 4.1 or higher

## Linux Compilation

* Run the following script or follow the steps below (this will install the header files into your system)
```bash
cd scripts
chmod 755 linux.sh
./linux.sh # Will also install new version of cmake 
```
1. Cmake new version (if needed)

```bash
CMAKE_URL="https://cmake.org/files/v3.19/cmake-3.19.0-Linux-x86_64.tar.gz"
mkdir cmake && wget --quiet -O - ${CMAKE_URL} | tar --strip-components=1 -xz -C cmake 
```
2. Build 

```bash
mkdir build
cd build
# or use ../cmake/bin/cmake .. -DNO-TEST=True 
cmake .. -DNO-TEST=True
make
sudo make install # (this will install the header files into your system)
```
## Macos Compilation
* Run the following script or follow the steps below (this will install the header files into your system)
```bash
cd scripts
chmod 755 macos.sh
./macos.sh
```
1) Normal build 
```bash
mkdir build
cd build
cmake .. -DNO-TEST=True  
make
sudo make install # (this will install the header files into your system)
```
## Windows Compilation
* Run the following script or follow the steps below (this will install the header files into your system)
```powershell
.\windows.ps1
```
1) Install [chocolatey](https://chocolatey.org/install) (if not installed)
```powershell
Set-ExecutionPolicy Bypass -Scope Process -Force; [System.Net.ServicePointManager]::SecurityProtocol = [System.Net.ServicePointManager]::SecurityProtocol -bor 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://chocolatey.org/install.ps1'))
```
2) Install C++ compilers (if needed)
```powershell
choco install mingw
choco install cmake
choco install make
choco install gsudo
```
3) Building 
```powershell
mkdir build
cd build
cmake -G "Unix Makefiles" .. -DNO-TEST=True
make 
sudo make install # (this will install the header files into your system)
```

## Compilation flags 
* Enable Unit tests
    ```
    cmake .. -DNO-TEST=False
    ```

# Usage 
* Non standard path install (means didn't use cmake install)
    ```cpp
    #include "includes/mcpp.hpp"
    ```

* Standard path install 

    ```c++
    #include <mcpp.hpp>
    ```



* Please see the full [documentation](https://harith-alsafi.github.io/mcpp-doc/) for detailed usage on the classes and functions 

* You can see the class refrence as a [pdf](doc/latex/refman.pdf) or an [html](doc/html/index.html)

