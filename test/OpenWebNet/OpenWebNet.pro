#-------------------------------------------------
#
# Project created by QtCreator 2014-08-24T13:37:02
#
#-------------------------------------------------

QT       += testlib network

QT       -= gui

TARGET = tst_OpenWebNet
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

DEFINES += PROJECT_PATH=\\\"$$PWD/\\\"
DEFINES += UNIT_TEST

QMAKE_CXXFLAGS += /FC


SOURCES +=  main.cpp \
    tst_OwnInputParser.cpp \
    ../../src/OpenWebNet/OwnInputParser.cpp \
    ../../src/OpenWebNet/OwnLink.cpp \
    tst_OwnLink.cpp \
    mock/MockErrorNotifier.cpp \
    mock/MockNetworkUi.cpp \
    mock/MockOwnSocket.cpp \
    tst_OwnFormatter.cpp \
    ../../src/OpenWebNet/OwnFormatter.cpp


DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    tst_OwnInputParser.h \
    ../../src/OpenWebNet/OwnInputParser.h \
    ../../src/configuration.h \
    ../../src/OpenWebNet/OwnLink.h \
    tst_OwnLink.h \
    ../../src/GUI/NetworkUi_IF.h \
    ../../src/GUI/ErrorNotifier_IF.h \
    mock/MockErrorNotifier.h \
    mock/MockNetworkUi.h \
    mock/MockOwnSocket.h \
    ../../src/OpenWebNet/OwnSocket_IF.h \
    ../../src/OpenWebNet/OwnConstants.h \
    ../../src/GUI/GuiInterface_IF.h \
    tst_OwnFormatter.h \
    ../../src/OpenWebNet/OwnFormatter.h



INCLUDEPATH += ../../src/ \
    ../../src/OpenWebNet/ \
    ../../src/GUI/ \
    mock

OTHER_FILES +=
