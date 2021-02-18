include(../Tools.pri)

QT       += widgets sql xml

TEMPLATE = lib

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
