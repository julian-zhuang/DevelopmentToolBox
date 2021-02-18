include(../Tools.pri)

QT       += gui widgets sql

TEMPLATE = lib

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
