#-------------------------------------------------
#
# Project created by QtCreator 2019-04-27T20:02:17
#
#-------------------------------------------------

QT       += gui widgets sql

TARGET = Terminal
TEMPLATE = lib

DESTDIR = $$PWD/../bin/Plugins

TRANSLATIONS+=$$PWD/../bin/Lang/SearchFile_zh.ts

INCLUDEPATH += $$PWD/../include
CONFIG += debug_and_release
CONFIG += c++11

CONFIG(debug,debug|release){
    TARGET = SearchFiled
    UI_DIR  = $$PWD/../tmp/$${TARGET}
    RCC_DIR  = $$PWD/../tmp/$${TARGET}
    MOC_DIR  = $$PWD/../tmp/$${TARGET}
    RCC_DIR  = $$PWD/../tmp/$${TARGET}
}
CONFIG(release,debug|release){
    TARGET = SearchFile
    UI_DIR  = $$PWD/../tmp/$${TARGET}
    RCC_DIR  = $$PWD/../tmp/$${TARGET}
    MOC_DIR  = $$PWD/../tmp/$${TARGET}
    RCC_DIR  = $$PWD/../tmp/$${TARGET}
}

DEFINES += TERMINAL_LIBRARY

SOURCES += TerminalInterface.cpp \
    TerminalUI.cpp

HEADERS += TerminalInterface.h \
    TerminalUI.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    TerminalUI.ui
