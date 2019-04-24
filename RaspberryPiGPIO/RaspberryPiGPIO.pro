#-------------------------------------------------
#
# Project created by QtCreator 2019-04-24T20:37:14
#
#-------------------------------------------------

QT       += widgets network

TARGET = RaspberryPiGPIO
TEMPLATE = lib

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
