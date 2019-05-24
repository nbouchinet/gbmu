# gbmu
gameboy / gameboy color emulator in C++

This project is for educational purpose only.

# Info
The Emulator can be build on either OSX or Linux.
It is possible that some games do not work properly.

# Dependencies
* boost-devel
* portaudio-devel
* qt5-qmake
* clang++

# OSX
```brew install boost portaudio```

# Fedora
```# dnf install portaudio-devel boost-devel clang qt5 qt5-qtbase-devel```

# Debian
```# apt-get install qt5-qmake portaudio19-dev clang libboost-all-dev```

# Build
```./configure && make -j```
