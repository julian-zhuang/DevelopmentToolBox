include(../Tools.pri)

QT       += widgets network

TEMPLATE = lib

DEFINES += FILETRANSFER_LIBRARY

SOURCES += \
    FileTransferExport.cpp \
    FileTransferUI.cpp

HEADERS += \
    FileTransferExport.h \
    FileTransferUI.h

FORMS += \
    FileTransferUI.ui
