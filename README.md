[![license](https://img.shields.io/badge/license-MIT-blue.svg)](LICENCE)

# Template for C++ projects with QT5 Gui (For Windows and Linux) 

- Sources, headers and mains separated in distinct folders
- Access to [Google Tests](https://github.com/google/googletest)
- Use of [CMake](https://cmake.org/) for much easier compiling
- Example configuration of QT5:Widgets

## Why?
I wanted to easily port my source codes from linux and compile them on windows without having to configure that tedious visual studio thing.

## Depndencies

### Linux
* CMake
* Qt5


### Windows

* CMake # [Download Link!](https://cmake.org/download/)
* QT5 (Select MinGW 7.30)# [Download Link!](https://www.qt.io/download)
* MinGW (x64, posix, seh) (MinGW is usually included with QT5) # [Download Link!](https://sourceforge.net/projects/mingw-w64/files/latest/download)


## Structure
```
.
├── CMakeLists.txt
├── app
│   ├── main.cpp
    └── example.ui
├── include
│   ├── example.h
│   └── Config.h.in
├── src
│   └── example.cpp
└── tests
    ├── dummy.cpp
    └── main.cpp
```

Sources go in [src/](src/), header files in [include/](include/), main programs (including QT5-related files) in [app/](app), and
tests go in [tests/](tests/) (compiled to `unit_tests.x` by default). 

You can find the example that builds the example in [app/main.cpp](app/main.cpp) under the `Build` section in [CMakeLists.txt](CMakeLists.txt). 
If the executable you made does not use the library in [src/](src), then only the first line is needed.

## Building

Build by making a build directory (i.e. `build/`), run `cmake` in that dir, and then use `mingw32-make` to build the desired target.

### Linux

``` bash
$ mkdir build && cd build
$ cmake .. -DCMAKE_BUILD_TYPE=[Debug | Release] 
$ make
$ make gtest     # Makes and runs the tests.(Only Available in debug mode )
```

### Windows

``` bash
$ mkdir build && cd build
$ cmake .. -DCMAKE_BUILD_TYPE=[Debug | Release] -G "MinGW Makefiles"
$ mingw32-make
$ mingw32-make gtest     # Makes and runs the tests.(Only Available in debug mode )
```

## Setup
``` bash
git clone https://github.com/alcros33/cpp-project
git remote remove origin
```

## .gitignore

The [.gitignore](.gitignore) file is a copy of the [Github C++.gitignore file](https://github.com/github/gitignore/blob/master/C%2B%2B.gitignore),
with the addition of ignoring the build directory (`build/`).

## IMPORTANT!!!
For windows be sure that MinGW installation directory in on PATH
(Guide [Info](https://www.computerhope.com/issues/ch000549.htm))
 




