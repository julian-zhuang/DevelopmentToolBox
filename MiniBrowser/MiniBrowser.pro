#-------------------------------------------------
#
# Project created by QtCreator 2019-03-10T21:41:57
#
#-------------------------------------------------

QT       += gui widgets webenginewidgets

TEMPLATE = lib
DESTDIR = $$PWD/../bin/Plugins

TRANSLATIONS+=$$PWD/../bin/Lang/WebWeChat_zh.ts

INCLUDEPATH += $$PWD/../include
CONFIG += debug_and_release
CONFIG += c++11

CONFIG(debug,debug|release){
    TARGET = MiniBrowserd
    UI_DIR  = $$PWD/../tmp/$${TARGET}
    RCC_DIR  = $$PWD/../tmp/$${TARGET}
    MOC_DIR  = $$PWD/../tmp/$${TARGET}
    RCC_DIR  = $$PWD/../tmp/$${TARGET}
}
CONFIG(release,debug|release){
    TARGET = MiniBrowser
    UI_DIR  = $$PWD/../tmp/$${TARGET}
    RCC_DIR  = $$PWD/../tmp/$${TARGET}
    MOC_DIR  = $$PWD/../tmp/$${TARGET}
    RCC_DIR  = $$PWD/../tmp/$${TARGET}
}

DEFINES += MINIBROWSER_LIBRARY

SOURCES += MiniBrowserInterFace.cpp \
    MiniBrowserUI.cpp \
    TabButton.cpp \
    BrowserWidget.cpp \
    UrlAddressBar.cpp \
    WebPageWidget.cpp \
    QWebEngineViewEx.cpp

HEADERS += MiniBrowserInterFace.h \
    MiniBrowserUI.h \
    TabButton.h \
    BrowserWidget.h \
    UrlAddressBar.h \
    WebPageWidget.h \
    QWebEngineViewEx.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    MiniBrowserUI.ui \
    TabButton.ui \
    BrowserWidget.ui \
    UrlAddressBar.ui \
    WebPageWidget.ui

RESOURCES += \
    minibrowserres.qrc
