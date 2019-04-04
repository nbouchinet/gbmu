#! /bin/bash

#This script is only intended to work on school's macs

/sgoinfre/goinfre/Perso/nbouchin/Qt/5.10.0/clang_64/bin/macdeployqt gbmu.app
DIR=$(dirname $1)/../Frameworks
mkdir -p $DIR
move_library() {
	NORPATH=${1/@rpath/\/sgoinfre/goinfre/Perso/nbouchin/Qt/5.10.0/clang_64/lib}
	BASENAME=$(basename $1)
	cd $DIR
	cp -f $NORPATH .
	chmod u+w $BASENAME
	install_name_tool -id @executable_path/../Frameworks/$BASENAME $BASENAME
	cd -
	install_name_tool -change $1 @executable_path/../Frameworks/$BASENAME $2
}

BOOST=$HOME/.brew/Cellar/boost/1.68.0_1/lib/libboost_serialization.dylib
move_library  $BOOST $1

PORTAUDIO=$HOME/.brew/Cellar/portaudio/19.6.0/lib/libportaudio.2.dylib
move_library $PORTAUDIO $1

PORTAUDIOCPP=$HOME/.brew/Cellar/portaudio/19.6.0/lib/libportaudiocpp.0.dylib
move_library $PORTAUDIOCPP $1
install_name_tool -change $PORTAUDIO @executable_path/../Frameworks/$(basename $PORTAUDIO) $DIR/$(basename $PORTAUDIOCPP)

#QTCORE=@rpath/QtCore.framework/Versions/5/QtCore
#move_library $QTCORE $1
#
#QTGUI=@rpath/QtGui.framework/Versions/5/QtGui 
#move_library $QTGUI $1
#install_name_tool -change $QTCORE @executable_path/../Frameworks/$(basename $QTCORE) $DIR/$(basename $QTGUI)
#
#QTWIDGETS=@rpath/QtWidgets.framework/Versions/5/QtWidgets 
#move_library $QTWIDGETS $1
#install_name_tool -change $QTCORE @executable_path/../Frameworks/$(basename $QTCORE) $DIR/$(basename $QTWIDGETS)
#install_name_tool -change $QTGUI @executable_path/../Frameworks/$(basename $QTGUI) $DIR/$(basename $QTWIDGETS)
#
#
#QTOPENGL=@rpath/QtOpenGL.framework/Versions/5/QtOpenGL 
#move_library $QTOPENGL $1
#install_name_tool -change $QTCORE @executable_path/../Frameworks/$(basename $QTCORE) $DIR/$(basename $QTOPENGL)
#install_name_tool -change $QTGUI @executable_path/../Frameworks/$(basename $QTGUI) $DIR/$(basename $QTOPENGL)
#install_name_tool -change $QTWIDGETS @executable_path/../Frameworks/$(basename $QTWIDGETS) $DIR/$(basename $QTOPENGL)

strip $1
