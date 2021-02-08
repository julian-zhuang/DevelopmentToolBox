#-------------------------------------------------
#
# Project created by QtCreator 2019-03-08T09:03:12
#
#-------------------------------------------------

QT       += widgets xml network

TEMPLATE = lib

DESTDIR += $$PWD/../../bin/plugin

TRANSLATIONS+=SocketTest_zh.ts

DEFINES += SOCKETTEST_LIBRARY

SOURCES += \
    SocketTestExport.cpp \
    SocketTestUI.cpp    \
    DelegateContral.cpp

HEADERS += \
    SocketTestExport.h \
    SocketTestUI.h  \
    DelegateContral.h

FORMS += \
    SocketTestUI.ui
