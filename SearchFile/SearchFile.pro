#-------------------------------------------------
#
# Project created by QtCreator 2019-03-10T00:02:40
#
#-------------------------------------------------

QT       += gui widgets sql

TEMPLATE = lib

DESTDIR = $$PWD/../bin/Plugins

TRANSLATIONS+=$$PWD/../bin/Lang/SearchFile_zh.ts

INCLUDEPATH += $$PWD/../include
CONFIG += debug_and_release
CONFIG += c++11

CONFIG(debug,debug|release){
    TARGET = SearchFiled
    UI_DIR  = $$PWD/../tmp/$${TARGET}
    RCC_DIR  = $$PWD/../tmp/$${TARGET}
    MOC_DIR  = $$PWD/../tmp/$${TARGET}
    RCC_DIR  = $$PWD/../tmp/$${TARGET}
}
CONFIG(release,debug|release){
    TARGET = SearchFile
    UI_DIR  = $$PWD/../tmp/$${TARGET}
    RCC_DIR  = $$PWD/../tmp/$${TARGET}
    MOC_DIR  = $$PWD/../tmp/$${TARGET}
    RCC_DIR  = $$PWD/../tmp/$${TARGET}
}

DEFINES += SEARCHFILE_LIBRARY

SOURCES += \
    SearchFileInterface.cpp \
    SearchFile.cpp \
    FileIndexThread.cpp \
    SqliteService.cpp \
    DirectoryList.cpp

HEADERS +=\
    SearchFileInterface.h \
    SearchFile.h \
    FileIndexThread.h \
    SqliteService.h \
    DirectoryList.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    SearchFile.ui \
    DirectoryList.ui

RESOURCES += \
    SearchFile.qrc
