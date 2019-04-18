#-------------------------------------------------
#
# Project created by QtCreator 2019-03-17T18:04:45
#
#-------------------------------------------------

QT       += widgets sql xml

TEMPLATE = lib

DESTDIR = $$PWD/../bin/Plugins

TRANSLATIONS+=$$PWD/../bin/Lang/Work_zh.ts

INCLUDEPATH += $$PWD/../include
CONFIG += debug_and_release
CONFIG += c++11

CONFIG(debug,debug|release){
    TARGET = Workd
    UI_DIR  = $$PWD/../tmp/$${TARGET}
    RCC_DIR  = $$PWD/../tmp/$${TARGET}
    MOC_DIR  = $$PWD/../tmp/$${TARGET}
    RCC_DIR  = $$PWD/../tmp/$${TARGET}
}
CONFIG(release,debug|release){
    TARGET = Work
    UI_DIR  = $$PWD/../tmp/$${TARGET}
    RCC_DIR  = $$PWD/../tmp/$${TARGET}
    MOC_DIR  = $$PWD/../tmp/$${TARGET}
    RCC_DIR  = $$PWD/../tmp/$${TARGET}
}

DEFINES += WORKLOGINTERFACE_LIBRARY

SOURCES += \
    WorkUI.cpp \
    WorkInterface.cpp

HEADERS += \
    WorkUI.h \
    WorkInterface.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    WorkUI.ui
