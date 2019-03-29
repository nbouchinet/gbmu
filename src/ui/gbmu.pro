#-------------------------------------------------
#
# Project created by QtCreator 2019-01-21T11:49:03
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gbmu 
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

QMAKE_CXX=clang++
CONFIG += c++14
QMAKE_CXXFLAGS += -Wall -Wextra -Werror -std=c++14

OBJECTS_DIR = ./src/obj
UI_DIR = ./src/ui
MOC_DIR = ./src/moc
RCC_DIR = ./src/rcc

SOURCES += \
	main.cpp \
        gbmuscreen.cpp \
        mainwindow.cpp \
    debuggerwindow.cpp \
	worker.cpp \

HEADERS += \
        gbmuscreen.h\
        mainwindow.h \
    debuggerwindow.h \
	worker.h

HOME = $$(HOME)

INCLUDEPATH += $$HOME/.brew/include
LIBS += -L $$HOME/.brew/lib -lportaudiocpp -lportaudio

FORMS += \
        mainwindow.ui \
    debuggerwindow.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

ICON = gbmu.png

SOURCES += \
	src/Cartridge.cpp \
	src/Debugger.cpp \
	src/Gameboy.cpp \
	src/MemoryBus.cpp \
	src/PPU.cpp \
	src/Bios.cpp\
	src/ScreenOutput.cpp \
	src/cpu/Core.cpp \
	src/cpu/CoreExecute.cpp \
	src/cpu/InputController.cpp \
	src/cpu/InterruptController.cpp \
	src/cpu/Timer.cpp \
	src/sound/APU.cpp \
	src/sound/ModulationUnits.cpp \
	src/sound/NoiseChannel.cpp \
	src/sound/SoundChannel.cpp \
	src/sound/SquareChannel.cpp \
	src/sound/WaveChannel.cpp \
	src/sound/portaudio/PortAudioInterface.cpp \
	utils/Logger.cpp

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
	src/PPU.hpp \
	src/RealTimeClock.hpp \
	src/ScreenOutput.hpp \
	src/UnitWorkingRAM.hpp \
	src/cpu/Core.hpp \
	src/cpu/InputController.hpp \
	src/cpu/InterruptController.hpp \
	src/cpu/Timer.hpp \
	src/sound/APU.hpp \
	src/sound/AudioInterface.hpp \
	src/sound/ModulationUnits.hpp \
	src/sound/NoiseChannel.hpp \
	src/sound/SoundChannel.hpp \
	src/sound/SquareChannel.hpp \
	src/sound/VolumeTable.hpp \
	src/sound/WaveChannel.hpp \
	src/sound/portaudio/PortAudioInterface.hpp \
	utils/Logger.hpp \
	utils/Operations_utils.hpp

DISTFILES +=
