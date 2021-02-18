include(../Tools.pri)

QT       += gui widgets sql

TEMPLATE = lib

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
