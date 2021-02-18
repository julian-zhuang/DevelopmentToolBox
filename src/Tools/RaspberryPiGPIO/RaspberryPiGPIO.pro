include(../Tools.pri)

QT       += gui widgets network

TEMPLATE = lib

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
