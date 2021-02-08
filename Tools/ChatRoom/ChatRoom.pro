#-------------------------------------------------
#
# Project created by QtCreator 2019-03-25T22:49:15
#
#-------------------------------------------------

QT       += widgets network sql

TEMPLATE = lib

DESTDIR += $$PWD/../../bin/plugin

TRANSLATIONS+=ChatRoom_zh.ts

DEFINES += CHATROOM_LIBRARY

SOURCES += \
    ChatRoomExport.cpp \
    ChatRoomUI.cpp \
    LocalInfoMation.cpp \
    InfomationCenter.cpp \
    CommunicationCenter.cpp \
    DataBaseCenter.cpp \
    StrMessage.cpp \
    FileMessage.cpp \
    ImageMessage.cpp \
    MemberInfoCard.cpp \
    GroupInfoCard.cpp

HEADERS += \
    ChatRoomExport.h \
    ChatRoomUI.h \
    LocalInfoMation.h \
    InfomationCenter.h \
    CommunicationCenter.h \
    DataBaseCenter.h \
    GeneralDataStructure.h \
    StrMessage.h \
    FileMessage.h \
    ImageMessage.h \
    MemberInfoCard.h \
    GroupInfoCard.h

FORMS += \
    ChatRoomUI.ui \
    LocalInfoMation.ui \
    StrMessage.ui \
    FileMessage.ui \
    ImageMessage.ui \
    MemberInfoCard.ui \
    GroupInfoCard.ui
