#-------------------------------------------------
#
# Project created by QtCreator 2019-04-18T19:12:09
#
#-------------------------------------------------

QT       +=gui widgets network

TEMPLATE = lib

DESTDIR = $$PWD/../bin/Plugins

TRANSLATIONS+=$$PWD/../bin/Lang/HttpTest_zh.ts

INCLUDEPATH += $$PWD/../include
CONFIG += debug_and_release
CONFIG += c++11

CONFIG(debug,debug|release){
    TARGET = HttpTestd
    UI_DIR  = $$PWD/../tmp/$${TARGET}
    RCC_DIR  = $$PWD/../tmp/$${TARGET}
    MOC_DIR  = $$PWD/../tmp/$${TARGET}
    RCC_DIR  = $$PWD/../tmp/$${TARGET}
}
CONFIG(release,debug|release){
    TARGET = HttpTest
    UI_DIR  = $$PWD/../tmp/$${TARGET}
    RCC_DIR  = $$PWD/../tmp/$${TARGET}
    MOC_DIR  = $$PWD/../tmp/$${TARGET}
    RCC_DIR  = $$PWD/../tmp/$${TARGET}
}

DEFINES += HTTPTEST_LIBRARY

SOURCES += \
    HttpTestInterface.cpp \
    HttpTestUI.cpp

HEADERS +=\
    HttpTestInterface.h \
    HttpTestUI.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    HttpTestUI.ui
