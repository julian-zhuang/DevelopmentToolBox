include(../Tools.pri)

QT       += widgets network core-private xml uitools-private printsupport

DEFINES += QFORMINTERNAL_NAMESPACE
DEFINES += QT_KEYWORDS

TEMPLATE = lib

TRANSLATIONS+=TSFileTranslation_zh.ts

LIBS += -L$$PWD/../bin -lcurl

DEFINES += TSFILETRANSLATION_LIBRARY

SOURCES += \
    TSFileTranslationExport.cpp \
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
    TranslationAPI.cpp

HEADERS += \
    TSFileTranslationExport.h \
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
    TranslationAPI.h

FORMS += \
    statistics.ui \
    phrasebookbox.ui \
    batchtranslation.ui \
    translatedialog.ui \
    mainwindow.ui \
    translationsettings.ui \
    finddialog.ui \
    TranslationAPI.ui

RESOURCES += linguist.qrc

DISTFILES += \
    shared/formats.pri
