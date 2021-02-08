#-------------------------------------------------
#
# Project created by QtCreator 2019-03-17T18:04:45
#
#-------------------------------------------------

QT       += widgets sql xml

TEMPLATE = lib

DESTDIR += $$PWD/../../bin/plugin

TRANSLATIONS += Work_zh.ts

DEFINES += WORKLOGINTERFACE_LIBRARY

SOURCES += \
    WorkExport.cpp \
    WorkUI.cpp

HEADERS += \
    WorkExport.h \
    WorkUI.h

FORMS += \
    WorkUI.ui
