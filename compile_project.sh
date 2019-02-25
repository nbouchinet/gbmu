#!/bin/sh

/sgoinfre/goinfre/Perso/hublanc/Qt/5.10.0/clang_64/bin/qmake /Users/hublanc/Documents/gbInput/GbmuUI/GbmuUI.pro -spec macx-clang CONFIG+=debug CONFIG+=x86_64 CONFIG+=qml_debug && "/usr/bin/make" -f /Users/hublanc/Documents/gbInput/Makefile qmake_all && make -j4 && ./GbmuUI.app/Contents/MacOS/GbmuUI
