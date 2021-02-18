include(../Tools.pri)
QT += gui widgets

DEFINES += CHARACTERENCODING_LIBRARY

TEMPLATE = lib

SOURCES += \
    CharacterEncodingExport.cpp \
    CharacterEncodingUI.cpp

HEADERS += \
    CharacterEncodingExport.h \
    CharacterEncodingUI.h

FORMS += \
    CharacterEncodingUI.ui

TRANSLATIONS += \
    CharacterEncoding_zh_CN.ts
