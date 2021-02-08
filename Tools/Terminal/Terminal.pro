#-------------------------------------------------
#
# Project created by QtCreator 2019-04-27T20:02:17
#
#-------------------------------------------------

QT       += gui widgets sql

TEMPLATE = lib

DESTDIR += $$PWD/../../bin/plugin

TRANSLATIONS+=Terminal_zh.ts

DEFINES += TERMINAL_LIBRARY

SOURCES += \
    TerminalExport.cpp \
    TerminalUI.cpp

HEADERS += \
    TerminalExport.h \
    TerminalUI.h

FORMS += \
    TerminalUI.ui
