#-------------------------------------------------
#
# Project created by QtCreator 2014-08-24T13:37:02
#
#-------------------------------------------------

QT       += testlib

TARGET = tst_PlantParserTest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

DEFINES += PROJECT_PATH=\\\"$$PWD/\\\"
DEFINES += UNIT_TEST

QMAKE_CXXFLAGS += /FC


SOURCES += tst_PlantParserTest.cpp \
    ../../src/plant/PlantParser.cpp \
    main.cpp \
    ../../src/plant/LightPoint.cpp \
    mock/MockGuiInterafce.cpp \
    tst_PlantLoader.cpp \
    ../../src/plant/PlantLoader.cpp \
    ../../src/plant/PlantInfo.cpp \
    ../../src/OpenWebNet/OwnFormatter.cpp \
    mock/MockPlantFactory.cpp

DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    tst_PlantParserTest.h \
    ../../src/plant/PlantParser.h \
    ../../src/plant/LightPoint.h \
    ../../src/GUI/GuiInterface_IF.h \
    mock/MockGuiInterafce.h \
    tst_PlantLoader.h \
    ../../src/plant/PlantLoader.h \
    ../../src/plant/PlantInfo.h \
    ../../src/OpenWebNet/OwnFormatter.h \
    mock/MockPlantFactory.h \
    ../../src/factories/PlantFactory_IF.h

INCLUDEPATH += ../../src/plant \
    ../../src/GUI \
    ../../src/factories \
    mock \
    ../OpenWebNet/mock
