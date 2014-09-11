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
    mock/MockOwnSocket.cpp


DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    tst_OwnInputParser.h \
    ../../src/OpenWebNet/OwnInputParser.h \
    ../../src/configuration.h \
    ../../src/OpenWebNet/OwnLink.h \
    tst_OwnLink.h \
    ../../src/OpenWebNet/NetworkUi_IF.h \
    ../../src/OpenWebNet/ErrorNotifier_IF.h \
    mock/MockErrorNotifier.h \
    mock/MockNetworkUi.h \
    mock/MockOwnSocket.h \
    ../../src/OpenWebNet/OwnSocket_IF.h \
    ../../src/OpenWebNet/OwnConstants.h \
    ../../src/GUI/GuiInterface_IF.h



INCLUDEPATH += ../../src/ \
    ../../src/OpenWebNet/ \
    mock

OTHER_FILES +=
