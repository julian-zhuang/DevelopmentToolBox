QT += gui widgets

TEMPLATE = lib

DEFINES += HTTPTES_LIBRARY

TRANSLATIONS+=HttpTest_zh.ts

DESTDIR += $$PWD/../../bin/plugin

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
