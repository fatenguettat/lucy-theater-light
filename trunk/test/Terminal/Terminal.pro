#-------------------------------------------------
#
# Project created by QtCreator 2014-08-24T13:37:02
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_Terminal
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

DEFINES += PROJECT_PATH=\\\"$$PWD/\\\"
DEFINES += UNIT_TEST
DEFINES += QT_FORCE_ASSERTS

# full path for __FILE__
QMAKE_CXXFLAGS += /FC

#so far use memory tools for Qt 5.2
equals(QT_MINOR_VERSION, 2) : QMAKE_CXXFLAGS += /Zi /EHsc /Oy- /Ob0


SOURCES +=  main.cpp \
    tst_CabledNetworkUI.cpp \
    ../../src/terminal/CabledNetworkUI.cpp


DEFINES += SRCDIR=\\\"$$PWD/\\\"


HEADERS += \
    tst_CabledNetworkUI.h \
    ../../src/GUI/NetworkUi_IF.h \
    ../../src/terminal/CabledNetworkUI.h


INCLUDEPATH += \
    ../../src/OpenWebNet \
    ../../src/GUI \
    ../../src/terminal


OTHER_FILES +=
