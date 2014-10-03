#-------------------------------------------------
#
# Project created by QtCreator 2014-08-24T13:37:02
#
#-------------------------------------------------

QT       += testlib network

TARGET = tst_PlantParser
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


SOURCES += tst_PlantParser.cpp \
    ../../src/plant/PlantParser.cpp \
    main.cpp \
    ../../src/plant/LightPoint.cpp \
    mock/MockGuiInterafce.cpp \
    tst_PlantLoader.cpp \
    ../../src/plant/PlantLoader.cpp \
    ../../src/plant/PlantInfo.cpp \
    ../../src/OpenWebNet/OwnFormatter.cpp \
    mock/MockPlantFactory.cpp \
    ../../src/OpenWebNet/OwnLink.cpp \
    ../OpenWebNet/mock/MockNetworkUi.cpp \
    ../OpenWebNet/mock/MockOwnSocket.cpp \
    ../OpenWebNet/mock/MockErrorNotifier.cpp \
    ../../src/OpenWebNet/OwnEngine.cpp \
    ../../src/OpenWebNet/OwnInputParser.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    tst_PlantParser.h \
    ../../src/plant/PlantParser.h \
    ../../src/plant/LightPoint.h \
    ../../src/GUI/GuiInterface_IF.h \
    mock/MockGuiInterafce.h \
    tst_PlantLoader.h \
    ../../src/plant/PlantLoader.h \
    ../../src/plant/PlantInfo.h \
    ../../src/OpenWebNet/OwnFormatter.h \
    mock/MockPlantFactory.h \
    ../../src/factories/PlantFactory_IF.h \
    ../../src/OpenWebNet/OwnLink.h \
    ../OpenWebNet/mock/MockNetworkUi.h \
    ../OpenWebNet/mock/MockOwnSocket.h \
    ../OpenWebNet/mock/MockErrorNotifier.h \
    ../../src/OpenWebNet/OwnEngine.h \
    ../../src/OpenWebNet/OwnInputParser.h \
    ../../src/GUI/NetworkUi_IF.h \
    ../../src/OpenWebNet/OwnSocket_IF.h

INCLUDEPATH += ../../src \
    ../../src/plant \
    ../../src/GUI \
    ../../src/factories \
    ../../src/OpenWebNet/ \
    mock \
    ../OpenWebNet/mock
