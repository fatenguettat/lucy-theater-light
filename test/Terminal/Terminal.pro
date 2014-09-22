#-------------------------------------------------
#
# Project created by QtCreator 2014-08-24T13:37:02
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_Terminaltest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

DEFINES += PROJECT_PATH=\\\"$$PWD/\\\"
DEFINES += UNIT_TEST

#let '__FILE__' contain full path
QMAKE_CXXFLAGS += /FC


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
