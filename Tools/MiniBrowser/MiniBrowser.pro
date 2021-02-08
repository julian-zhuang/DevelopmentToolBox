#-------------------------------------------------
#
# Project created by QtCreator 2019-03-10T21:41:57
#
#-------------------------------------------------

QT       += gui widgets webenginewidgets

TEMPLATE = lib

DESTDIR += $$PWD/../../bin/plugin

TRANSLATIONS+=WebWeChat_zh.ts

DEFINES += MINIBROWSER_LIBRARY

SOURCES += \
    MiniBrowserExport.cpp \
    MiniBrowserUI.cpp \
    TabButton.cpp \
    BrowserWidget.cpp \
    UrlAddressBar.cpp \
    WebPageWidget.cpp \
    QWebEngineViewEx.cpp

HEADERS += \
    MiniBrowserExport.h \
    MiniBrowserUI.h \
    TabButton.h \
    BrowserWidget.h \
    UrlAddressBar.h \
    WebPageWidget.h \
    QWebEngineViewEx.h

FORMS += \
    MiniBrowserUI.ui \
    TabButton.ui \
    BrowserWidget.ui \
    UrlAddressBar.ui \
    WebPageWidget.ui

RESOURCES += \
    minibrowserres.qrc
