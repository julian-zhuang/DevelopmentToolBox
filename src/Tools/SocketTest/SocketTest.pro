include(../Tools.pri)

QT       += widgets xml network

TEMPLATE = lib

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
