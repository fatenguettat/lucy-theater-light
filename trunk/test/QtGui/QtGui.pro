#-------------------------------------------------
#
# Project created by QtCreator 2014-10-01T23:11:59
#
#-------------------------------------------------

QT       += widgets testlib network

TARGET = tst_GuiInterfaceQt
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

DEFINES += UNIT_TEST
DEFINES += QT_FORCE_ASSERTS

INCLUDEPATH += mock \
    ../../src/ \
    ../../src/GUI \
    ../../src/OpenWebNet \
    ../../src/plant \
    ../../src/form \
    ../OpenWebNet/mock


SOURCES += tst_GuiInterfaceQt.cpp \
    ../../src/GUI/GuiInterfaceQt.cpp \
    ../../src/plant/LightPoint.cpp \
    ../../src/GUI/LightButton.cpp \
    ../../src/form/LightPanel.cpp \
    ../../src/OpenWebNet/OwnEngine.cpp \
    ../../src/OpenWebNet/OwnFormatter.cpp \
    ../../src/OpenWebNet/OwnInputParser.cpp \
    ../../src/OpenWebNet/OwnLink.cpp \
    ../OpenWebNet/mock/MockErrorNotifier.cpp \
    ../OpenWebNet/mock/MockNetworkUi.cpp \
    ../OpenWebNet/mock/MockOwnSocket.cpp \
    mock/MockLightPanel.cpp \
    ../../src/GUI/Button.cpp \
    ../../src/GUI/Slider.cpp \
    ../../src/plant/LightGroup.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../../src/GUI/GuiInterface_IF.h \
    ../../src/GUI/GuiInterfaceQt.h \
    ../../src/plant/LightPoint.h \
    ../../src/GUI/LightButton.h \
    ../../src/form/LightPanel.h \
    ../../src/OpenWebNet/OwnConstants.h \
    ../../src/OpenWebNet/OwnEngine.h \
    ../../src/OpenWebNet/OwnFormatter.h \
    ../../src/OpenWebNet/OwnInputParser.h \
    ../../src/OpenWebNet/OwnLink.h \
    ../../src/OpenWebNet/OwnSocket_IF.h \
    ../OpenWebNet/mock/MockErrorNotifier.h \
    ../OpenWebNet/mock/MockNetworkUi.h \
    ../OpenWebNet/mock/MockOwnSocket.h \
    ../../src/GUI/NetworkUi_IF.h \
    mock/MockLightPanel.h \
    ../../src/GUI/Button.h \
    ../../src/GUI/Slider.h \
    ../../src/plant/LightGroup.h

