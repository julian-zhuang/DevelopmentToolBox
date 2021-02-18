include(../Tools.pri)

QT       += core gui network widgets

TEMPLATE = lib

DEFINES += CHAT_LIBRARY

SOURCES += \
    ChatExport.cpp \
    ChatWindow.cpp \
    Config.cpp \
    DiscoveryService.cpp \
    Chat.cpp \
    PostService.cpp

HEADERS += \
    Chat.h \
    ChatExport.h \
    ChatWindow.h \
    Config.h \
    DiscoveryService.h \
    PostService.h

FORMS += \
    Chat.ui \
    ChatWindow.ui

TRANSLATIONS += \
    Chat_zh_CN.ts
