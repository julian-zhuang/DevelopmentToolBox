#-------------------------------------------------
#
# Project created by QtCreator 2019-04-15T23:24:28
#
#-------------------------------------------------

QT       += widgets network

TEMPLATE = lib

DESTDIR = $$PWD/../bin/Plugins

TRANSLATIONS+=$$PWD/../bin/Lang/TSFileTranslation_zh.ts

INCLUDEPATH += $$PWD/../include
CONFIG += debug_and_release
CONFIG += c++11

CONFIG(debug,debug|release){
    TARGET = TSFileTranslationd
    UI_DIR  = $$PWD/../tmp/$${TARGET}
    RCC_DIR  = $$PWD/../tmp/$${TARGET}
    MOC_DIR  = $$PWD/../tmp/$${TARGET}
    RCC_DIR  = $$PWD/../tmp/$${TARGET}
}
CONFIG(release,debug|release){
    TARGET = TSFileTranslation
    UI_DIR  = $$PWD/../tmp/$${TARGET}
    RCC_DIR  = $$PWD/../tmp/$${TARGET}
    MOC_DIR  = $$PWD/../tmp/$${TARGET}
    RCC_DIR  = $$PWD/../tmp/$${TARGET}
}

DEFINES += TSFILETRANSLATION_LIBRARY

SOURCES += TSFileTranslationInterface.cpp \
    TSFileTranslationUI.cpp

HEADERS += TSFileTranslationInterface.h \
    TSFileTranslationUI.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    TSFileTranslationUI.ui
