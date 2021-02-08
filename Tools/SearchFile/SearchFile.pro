#-------------------------------------------------
#
# Project created by QtCreator 2019-03-10T00:02:40
#
#-------------------------------------------------

QT       += gui widgets sql

TEMPLATE = lib

DESTDIR += $$PWD/../../bin/plugin

TRANSLATIONS+=SearchFile_zh.ts

DEFINES += SEARCHFILE_LIBRARY

SOURCES += \
    SearchFile.cpp \
    FileIndexThread.cpp \
    SearchFileExport.cpp \
    SqliteService.cpp \
    DirectoryList.cpp

HEADERS +=\
    SearchFile.h \
    FileIndexThread.h \
    SearchFileExport.h \
    SqliteService.h \
    DirectoryList.h

FORMS += \
    SearchFile.ui \
    DirectoryList.ui

RESOURCES += \
    SearchFile.qrc
