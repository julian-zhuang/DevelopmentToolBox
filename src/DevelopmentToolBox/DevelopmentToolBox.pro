include(../GlobalprojectConig.pri)

QT       += core gui widgets

DESTDIR += $$PWD/../../bin/

SOURCES += \
    Log.cpp \
    PluginManager.cpp \
    ResourceManager.cpp \
    main.cpp \
    DevelopmentToolBox.cpp

HEADERS += \
    DevelopmentToolBox.h \
    Log.h \
    PluginManager.h \
    ResourceManager.h

FORMS += \
    DevelopmentToolBox.ui

TRANSLATIONS += \
    DevelopmentToolBox_zh_CN.ts
