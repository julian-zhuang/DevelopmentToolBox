include(../Tools.pri)

QT       += widgets network sql

TEMPLATE = lib

TRANSLATIONS+=ChatRoom_zh.ts

DEFINES += CHATROOM_LIBRARY

SOURCES += \
    ChatRoomExport.cpp \
    ChatRoomUI.cpp \
    DiscoveryService.cpp \
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
    DiscoveryService.h \
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
