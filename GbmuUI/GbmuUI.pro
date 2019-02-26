#-------------------------------------------------
#
# Project created by QtCreator 2019-01-21T11:49:03
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GbmuUI
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++14
QMAKE_CXXFLAGS += -Wall -Wextra -Werror -g 

SOURCES += \
	main.cpp \
        gbmuscreen.cpp \
        mainwindow.cpp \
    debuggerwindow.cpp \
	worker.cpp

HEADERS += \
        gbmuscreen.h\
        mainwindow.h \
    debuggerwindow.h \
	worker.h

FORMS += \
        mainwindow.ui \
    debuggerwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

ICON = GbmuUI.png

SOURCES += \
	src/Bios.cpp \
	src/Cartridge.cpp \
	src/Debugger.cpp \
	src/Gameboy.cpp \
	src/MemoryBus.cpp \
	src/PPU.class.cpp \
	src/ScreenOutput.class.cpp \
	src/cpu/Core.cpp \
	src/cpu/InputController.cpp \
	src/cpu/InterruptController.cpp \
	src/cpu/Timer.cpp

HEADERS += \
	src/AMemoryBankController.hpp \
	src/Bios.hpp \
	src/Cartridge.hpp \
	src/Debugger.hpp \
	src/Fwd.hpp \
	src/Gameboy.hpp \
	src/IReadWrite.hpp \
	src/LCDRegisters.hpp \
	src/MemoryBankController1.hpp \
	src/MemoryBankController2.hpp \
	src/MemoryBankController3.hpp \
	src/MemoryBankController5.hpp \
	src/MemoryBus.hpp \
	src/PPU.class.h \
	src/RealTimeClock.hpp \
	src/ScreenOutput.class.h \
	src/UnitWorkingRAM.hpp \
	src/cpu/Core.hpp \
	src/cpu/InputController.hpp \
	src/cpu/InterruptController.hpp \
	src/cpu/Timer.hpp