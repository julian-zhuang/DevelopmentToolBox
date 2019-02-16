#-------------------------------------------------
#
# Project created by QtCreator 2018-12-01T22:27:44
#
#-------------------------------------------------

QT       += core gui sql widgets network

TEMPLATE = app
DESTDIR = $$PWD/../bin

TRANSLATIONS+=$$PWD/../bin/Language_zh.ts

INCLUDEPATH += $$PWD/../include
CONFIG += debug_and_release
CONFIG += c++11

CONFIG(debug,debug|release){
    TARGET = DevelopmentToolBoxd
    UI_DIR  = $$PWD/../tmp/$${TARGET}
    RCC_DIR  = $$PWD/../tmp/$${TARGET}
    MOC_DIR  = $$PWD/../tmp/$${TARGET}
    RCC_DIR  = $$PWD/../tmp/$${TARGET}
}
CONFIG(release,debug|release){
    TARGET = DevelopmentToolBox
    UI_DIR  = $$PWD/../tmp/$${TARGET}
    RCC_DIR  = $$PWD/../tmp/$${TARGET}
    MOC_DIR  = $$PWD/../tmp/$${TARGET}
    RCC_DIR  = $$PWD/../tmp/$${TARGET}
}

SOURCES += \
        main.cpp \
        mainwindow.cpp  \
        Snake.cpp \
        FileTransfer.cpp \
        Working.cpp \
        SocketTransfer.cpp \
        HttpClient.cpp \
        SocketClient.cpp \
        SocketServer.cpp \
        SearchFile.cpp \
        TaskWidget.cpp \
        TaskEdit.cpp \
        SqliteService.cpp \
    SetShortcuts.cpp \
    ColorPicker.cpp \
    DirectoryList.cpp \
    FileIndexThread.cpp \
    Calculation.cpp \
    MItemDelegate.cpp

HEADERS += \
        mainwindow.h    \
        Snake.h \
        FileTransfer.h \
        Working.h \
        SocketTransfer.h \
        HttpClient.h \
        SocketClient.h \
        SocketServer.h \
        SearchFile.h \
        TaskWidget.h \
        TaskEdit.h \
        SqliteService.h \
    SetShortcuts.h \
    ColorPicker.h \
    DirectoryList.h \
    FileIndexThread.h \
    Calculation.h \
    MItemDelegate.h

FORMS += \
        mainwindow.ui \
        FileTransfer.ui \
        Working.ui \
        SocketTransfer.ui \
        HttpClient.ui \
        SocketClient.ui \
        SocketServer.ui \
        SearchFile.ui \
        TaskWidget.ui \
        TaskEdit.ui \
    SetShortcuts.ui \
    ColorPicker.ui \
    DirectoryList.ui \
    Calculation.ui

RESOURCES += \
    DevelopmentToolBoxResource.qrc
