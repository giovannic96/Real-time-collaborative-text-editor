# Installing boost libraries for GCC on Windows - Final Guide

## 1) First step
1. Add to environment variables PATH the string "C:\Qt\Qt5.13.1\Tools\mingw730_64\bin"
2. Order it as first one

## 2) Folder setup
1. Extract downloaded boost source, e.g. `C:\Program Files\boost_1_66_0`.
2. Create a folder for Boost.Build installation, e.g. `C:\Program Files\boost-build`.
2. Create a folder within for building, i.e. `C:\Program Files\boost_1_66_0\build`.
3. Create a folder for installation, e.g. `C:\Program Files\boost`.


## 3) Boost.Build setup
1. Open Command Prompt and navigate to `C:\Program Files\boost_1_66_0\tools\build`.
2. Run `bootstrap.bat gcc`.
3. Run `b2 install --prefix="C:\Program Files\boost-build"`.
4. Add `C:\Program Files\boost-build\bin` to Windows PATH (environment variables).

## 4) Boost building
1. Open Command Prompt and navigate to `C:\Program Files\boost_1_66_0`.
2. Run `bootstrap.bat gcc`.
3. Run
```
b2 --build-dir="C:\Program Files\boost_1_66_0\build" --prefix="C:\Program Files\boost" toolset=gcc install
```

## 5) Project setup
1. Add include folder, i.e. `C:\Program Files\boost\include\boost-1_66`.
2. Add linker folder, i.e. `C:\Program Files\boost\lib`.
3. Link required libraries, e.g. `libboost_regex-mgw48-mt-1_66.a`.
