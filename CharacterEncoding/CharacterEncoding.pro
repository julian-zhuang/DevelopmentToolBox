#-------------------------------------------------
#
# Project created by QtCreator 2019-04-06T12:44:18
#
#-------------------------------------------------

QT       += widgets gui

TEMPLATE = lib

INCLUDEPATH += $$PWD/../include

DESTDIR = $$PWD/../bin/Plugins

TRANSLATIONS+=$$PWD/../bin/Lang/CharacterEncoding_zh.ts

CONFIG += debug_and_release

CONFIG += c++11

CONFIG(debug,debug|release){
    TARGET = CharacterEncodingd
    UI_DIR  = $$PWD/../tmp/$${TARGET}
    RCC_DIR  = $$PWD/../tmp/$${TARGET}
    MOC_DIR  = $$PWD/../tmp/$${TARGET}
    RCC_DIR  = $$PWD/../tmp/$${TARGET}
}
CONFIG(release,debug|release){
    TARGET = CharacterEncoding
    UI_DIR  = $$PWD/../tmp/$${TARGET}
    RCC_DIR  = $$PWD/../tmp/$${TARGET}
    MOC_DIR  = $$PWD/../tmp/$${TARGET}
    RCC_DIR  = $$PWD/../tmp/$${TARGET}
}

DEFINES += CHARACTERENCODING_LIBRARY

SOURCES += \
    CharacterEncodingUI.cpp \
    CharacterEncodingInterface.cpp

HEADERS +=\
    CharacterEncodingUI.h \
    CharacterEncodingInterface.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    CharacterEncodingUI.ui
