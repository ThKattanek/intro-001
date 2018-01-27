# Intro-001
A simply SFML demo
###[Latest version here](https://github.com/ThKattanek/intro-001/releases)

![Screenshot](screenshot.png)

## Used libraries
* SFML

## Compiling
```bash
cd ~
git clone https://github.com/ThKattanek/intro-001.git
cd intro-001
mkdir build
cd build
cmake ..
make
```
## Compiling for Windows x32 with MXE (Crossdev)
```bash
cd ~
git clone https://github.com/ThKattanek/intro-001.git
cd intro-001
mkdir build-win-x32
cd build-win-x32
[MXE-PATH]/usr/bin/i686-w64-mingw32.static-cmake .. -DSFML_STATIC_LIBRARIES=TRUE
make
```

## Compiling for Windows x64 with MXE (Crossdev)
```bash
cd ~
git clone https://github.com/ThKattanek/intro-001.git
cd intro-001
mkdir build-win-x64
cd build-win-x64
[MXE-PATH]/usr/bin/x86_64-w64-mingw32.static-cmake .. -DSFML_STATIC_LIBRARIES=TRUE
make
```
###[MXE Website](http://mxe.cc)