#-------------------------------------------------
#
# Project created by QtCreator 2019-03-08T09:03:12
#
#-------------------------------------------------

QT       += widgets xml network

TEMPLATE = lib

DESTDIR = $$PWD/../bin/Plugins

TRANSLATIONS+=$$PWD/../bin/Lang/SocketTest_zh.ts

INCLUDEPATH += $$PWD/../include
CONFIG += debug_and_release
CONFIG += c++11

CONFIG(debug,debug|release){
    TARGET = SocketTestd
    UI_DIR  = $$PWD/../tmp/$${TARGET}
    RCC_DIR  = $$PWD/../tmp/$${TARGET}
    MOC_DIR  = $$PWD/../tmp/$${TARGET}
    RCC_DIR  = $$PWD/../tmp/$${TARGET}
}
CONFIG(release,debug|release){
    TARGET = SocketTest
    UI_DIR  = $$PWD/../tmp/$${TARGET}
    RCC_DIR  = $$PWD/../tmp/$${TARGET}
    MOC_DIR  = $$PWD/../tmp/$${TARGET}
    RCC_DIR  = $$PWD/../tmp/$${TARGET}
}


DEFINES += SOCKETTEST_LIBRARY

SOURCES += \
    SocketTestInterface.cpp \
    SocketTestUI.cpp    \
    DelegateContral.cpp

HEADERS += \
    SocketTestInterface.h \
    SocketTestUI.h  \
    DelegateContral.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    SocketTestUI.ui
