#-------------------------------------------------
#
# Project created by QtCreator 2019-04-24T20:37:14
#
#-------------------------------------------------

QT       += gui widgets network

TEMPLATE = lib

DESTDIR = $$PWD/../bin/Plugins

TRANSLATIONS+=$$PWD/../bin/Lang/RaspberryPiGPIO_zh.ts

INCLUDEPATH += $$PWD/../include
CONFIG += debug_and_release
CONFIG += c++11

CONFIG(debug,debug|release){
    TARGET = RaspberryPiGPIOd
    UI_DIR  = $$PWD/../tmp/$${TARGET}
    RCC_DIR  = $$PWD/../tmp/$${TARGET}
    MOC_DIR  = $$PWD/../tmp/$${TARGET}
    RCC_DIR  = $$PWD/../tmp/$${TARGET}
}
CONFIG(release,debug|release){
    TARGET = RaspberryPiGPIO
    UI_DIR  = $$PWD/../tmp/$${TARGET}
    RCC_DIR  = $$PWD/../tmp/$${TARGET}
    MOC_DIR  = $$PWD/../tmp/$${TARGET}
    RCC_DIR  = $$PWD/../tmp/$${TARGET}
}

DEFINES += RASPBERRYPIGPIO_LIBRARY

SOURCES += RaspberryPiGPIOInterface.cpp \
    RaspberryPiGPIOUI.cpp

HEADERS += RaspberryPiGPIOInterface.h \
    RaspberryPiGPIOUI.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    RaspberryPiGPIOUI.ui
