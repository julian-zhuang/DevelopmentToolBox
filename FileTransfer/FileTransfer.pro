#-------------------------------------------------
#
# Project created by QtCreator 2019-03-17T16:40:27
#
#-------------------------------------------------

QT       += widgets network

TEMPLATE = lib

DESTDIR = $$PWD/../bin/Plugins

TRANSLATIONS+=$$PWD/../bin/Lang/FileTransfer_zh.ts

INCLUDEPATH += $$PWD/../include
CONFIG += debug_and_release
CONFIG += c++11

CONFIG(debug,debug|release){
    TARGET = FileTransferD
    UI_DIR  = $$PWD/../tmp/$${TARGET}
    RCC_DIR  = $$PWD/../tmp/$${TARGET}
    MOC_DIR  = $$PWD/../tmp/$${TARGET}
    RCC_DIR  = $$PWD/../tmp/$${TARGET}
}
CONFIG(release,debug|release){
    TARGET = FileTransfer
    UI_DIR  = $$PWD/../tmp/$${TARGET}
    RCC_DIR  = $$PWD/../tmp/$${TARGET}
    MOC_DIR  = $$PWD/../tmp/$${TARGET}
    RCC_DIR  = $$PWD/../tmp/$${TARGET}
}

DEFINES += FILETRANSFER_LIBRARY

SOURCES += \
    FileTransferUI.cpp \
    FileTransferInterface.cpp

HEADERS += \
    FileTransferUI.h \
    FileTransferInterface.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    FileTransferUI.ui
