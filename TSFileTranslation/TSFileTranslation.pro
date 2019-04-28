#-------------------------------------------------
#
# Project created by QtCreator 2019-04-15T23:24:28
#
#-------------------------------------------------

QT       += widgets network core-private xml uitools-private printsupport

DEFINES += QFORMINTERNAL_NAMESPACE
DEFINES += QT_KEYWORDS

TEMPLATE = lib

DESTDIR = $$PWD/../bin/Plugins

TRANSLATIONS+=$$PWD/../bin/Lang/TSFileTranslation_zh.ts

include(shared/formats.pri)
INCLUDEPATH += $$PWD/../include
CONFIG += debug_and_release
CONFIG += c++11

CONFIG(debug,debug|release){
    TARGET = TSFileTranslationd
    UI_DIR  = $$PWD/../tmp/$${TARGET}
    RCC_DIR  = $$PWD/../tmp/$${TARGET}
    MOC_DIR  = $$PWD/../tmp/$${TARGET}
    RCC_DIR  = $$PWD/../tmp/$${TARGET}
}
CONFIG(release,debug|release){
    TARGET = TSFileTranslation
    UI_DIR  = $$PWD/../tmp/$${TARGET}
    RCC_DIR  = $$PWD/../tmp/$${TARGET}
    MOC_DIR  = $$PWD/../tmp/$${TARGET}
    RCC_DIR  = $$PWD/../tmp/$${TARGET}
}

DEFINES += TSFILETRANSLATION_LIBRARY

SOURCES += TSFileTranslationInterface.cpp \
    batchtranslationdialog.cpp \
    errorsview.cpp \
    finddialog.cpp \
    formpreviewview.cpp \
    globals.cpp \
    mainwindow.cpp \
    messageeditor.cpp \
    messageeditorwidgets.cpp \
    messagehighlighter.cpp \
    messagemodel.cpp \
    phrasebookbox.cpp \
    phrase.cpp \
    phrasemodel.cpp \
    phraseview.cpp \
    printout.cpp \
    recentfiles.cpp \
    sourcecodeview.cpp \
    statistics.cpp \
    translatedialog.cpp \
    translationsettingsdialog.cpp \
    shared/simtexth.cpp

HEADERS += TSFileTranslationInterface.h \
    batchtranslationdialog.h \
    errorsview.h \
    finddialog.h \
    formpreviewview.h \
    globals.h \
    mainwindow.h \
    messageeditor.h \
    messageeditorwidgets.h \
    messagehighlighter.h \
    messagemodel.h \
    phrasebookbox.h \
    phrase.h \
    phrasemodel.h \
    phraseview.h \
    printout.h \
    recentfiles.h \
    sourcecodeview.h \
    statistics.h \
    translatedialog.h \
    translationsettingsdialog.h \
    shared/simtexth.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

FORMS += \
    statistics.ui \
    phrasebookbox.ui \
    batchtranslation.ui \
    translatedialog.ui \
    mainwindow.ui \
    translationsettings.ui \
    finddialog.ui

RESOURCES += linguist.qrc
