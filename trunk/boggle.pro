# -------------------------------------------------
# Project created by QtCreator 2008-11-12T01:15:41
# -------------------------------------------------
TARGET = boggle
TEMPLATE = app
SOURCES += sources/main.cpp \
    sources/mainwindow.cpp \
    sources/die.cpp \
    sources/dicetray.cpp \
    sources/lexicon.cpp
HEADERS += sources/mainwindow.h \
    sources/die.h \
    sources/dicetray.h \
    sources/lexicon.h
FORMS += sources/mainwindow.ui
RESOURCES += resources/files.qrc
TRANSLATIONS += translations/de.ts


QMAKE_MAC_SDK = /Developer/SDKs/MacOSX10.4u.sdk
CONFIG += x86 ppc