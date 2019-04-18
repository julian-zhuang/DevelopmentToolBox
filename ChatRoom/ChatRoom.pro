#-------------------------------------------------
#
# Project created by QtCreator 2019-03-25T22:49:15
#
#-------------------------------------------------

QT       += widgets network sql

TEMPLATE = lib

DESTDIR = $$PWD/../bin/Plugins

TRANSLATIONS+=$$PWD/../bin/Lang/ChatRoom_zh.ts

INCLUDEPATH += $$PWD/../include
CONFIG += debug_and_release
CONFIG += c++11

CONFIG(debug,debug|release){
    TARGET = ChatRoomd
    UI_DIR  = $$PWD/../tmp/$${TARGET}
    RCC_DIR  = $$PWD/../tmp/$${TARGET}
    MOC_DIR  = $$PWD/../tmp/$${TARGET}
    RCC_DIR  = $$PWD/../tmp/$${TARGET}
}
CONFIG(release,debug|release){
    TARGET = ChatRoom
    UI_DIR  = $$PWD/../tmp/$${TARGET}
    RCC_DIR  = $$PWD/../tmp/$${TARGET}
    MOC_DIR  = $$PWD/../tmp/$${TARGET}
    RCC_DIR  = $$PWD/../tmp/$${TARGET}
}

DEFINES += CHATROOM_LIBRARY

SOURCES += ChatRoomInterFace.cpp \
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

HEADERS += ChatRoomInterFace.h \
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

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    ChatRoomUI.ui \
    LocalInfoMation.ui \
    StrMessage.ui \
    FileMessage.ui \
    ImageMessage.ui \
    MemberInfoCard.ui \
    GroupInfoCard.ui
