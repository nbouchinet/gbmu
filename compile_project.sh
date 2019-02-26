#!/bin/sh

NAME=$(whoami)
PROJECT_PATH=$(pwd)

/sgoinfre/goinfre/Perso/$NAME/Qt/5.10.0/clang_64/bin/qmake $PROJECT_PATH/GbmuUI/GbmuUI.pro -spec macx-clang CONFIG+=debug CONFIG+=x86_64 CONFIG+=qml_debug && "/usr/bin/make" -f $PROJECT_PATH/Makefile qmake_all && make -j5 && ./GbmuUI.app/Contents/MacOS/GbmuUI
