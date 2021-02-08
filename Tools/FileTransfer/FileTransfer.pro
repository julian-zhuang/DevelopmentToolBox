#-------------------------------------------------
#
# Project created by QtCreator 2019-03-17T16:40:27
#
#-------------------------------------------------

QT       += widgets network

TEMPLATE = lib

DESTDIR += $$PWD/../../bin/plugin

DEFINES += FILETRANSFER_LIBRARY

SOURCES += \
    FileTransferExport.cpp \
    FileTransferUI.cpp

HEADERS += \
    FileTransferExport.h \
    FileTransferUI.h

FORMS += \
    FileTransferUI.ui
