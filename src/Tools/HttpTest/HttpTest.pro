include(../Tools.pri)

QT += gui widgets

TEMPLATE = lib

DEFINES += HTTPTES_LIBRARY

TRANSLATIONS+=HttpTest_zh.ts

SOURCES += \
    HttpTestExport.cpp \
    HttpTestUI.cpp

HEADERS += \
    HttpTestExport.h \
    HttpTestUI.h

TRANSLATIONS += \
    HttpTes_zh_CN.ts

FORMS += \
    HttpTestUI.ui
