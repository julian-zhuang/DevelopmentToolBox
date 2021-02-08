#-------------------------------------------------
#
# Project created by QtCreator 2019-04-24T20:37:14
#
#-------------------------------------------------

QT       += gui widgets network

TEMPLATE = lib

DESTDIR += $$PWD/../../bin/plugin

TRANSLATIONS+=RaspberryPiGPIO_zh.ts

DEFINES += RASPBERRYPIGPIO_LIBRARY

SOURCES += \
    RaspberryPiGPIOExport.cpp \
    RaspberryPiGPIOUI.cpp

HEADERS += \
    RaspberryPiGPIOExport.h \
    RaspberryPiGPIOUI.h

FORMS += \
    RaspberryPiGPIOUI.ui
