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
DEFINES += QT_FORCE_ASSERTS

# full path for __FILE__
QMAKE_CXXFLAGS += /FC

#so far use memory tools for Qt 5.2
equals(QT_MINOR_VERSION, 2) : QMAKE_CXXFLAGS += /Zi /EHsc /Oy- /Ob0



SOURCES +=  main.cpp \
    tst_OwnInputParser.cpp \
    ../../src/OpenWebNet/OwnInputParser.cpp \
    ../../src/OpenWebNet/OwnLink.cpp \
    tst_OwnLink.cpp \
    mock/MockErrorNotifier.cpp \
    mock/MockNetworkUi.cpp \
    mock/MockOwnSocket.cpp \
    tst_OwnFormatter.cpp \
    ../../src/OpenWebNet/OwnFormatter.cpp \
    tst_OwnEngine.cpp \
    ../../src/OpenWebNet/OwnEngine.cpp \
    ../PlantParser/mock/MockGuiInterafce.cpp \
    ../../src/plant/LightPoint.cpp


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
    ../../src/OpenWebNet/OwnFormatter.h \
    tst_OwnEngine.h \
    ../../src/OpenWebNet/OwnEngine.h \
    ../PlantParser/mock/MockGuiInterafce.h \
    ../../src/plant/LightPoint.h



INCLUDEPATH += ../../src/ \
    ../../src/OpenWebNet/ \
    ../../src/GUI/ \
    mock \
    ../PlantParser/mock \
    ../../src/plant

OTHER_FILES +=
