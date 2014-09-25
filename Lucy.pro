#-------------------------------------------------
#
# Project created by QtCreator 2014-08-23T21:02:18
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Lucy
TEMPLATE = app

INCLUDEPATH += \
    ./src \
    ./src/form \
    ./src/GUI \
    ./src/OpenWebNet \
    ./src/plant \
    ./src/factories \
    ./src/terminal


FORMS    += src/form/MainWindow.ui \
    src/form/MessageViewer.ui

CONFIG += mobility
MOBILITY =

DEFINES += QT_FORCE_ASSERTS

RESOURCES += \
    res/resources.qrc

HEADERS += \
    src/configuration.h \
    src/form/MainWindow.h \
    src/GUI/GuiInterface_IF.h \
    src/GUI/ErrorNotifier_IF.h \
    src/GUI/NetworkUi_IF.h \
    src/OpenWebNet/OwnConstants.h \
    src/OpenWebNet/OwnInputParser.h \
    src/OpenWebNet/OwnLink.h \
    src/OpenWebNet/OwnSocket_IF.h \
    src/OpenWebNet/OwnSocketTcp.h \
    src/plant/LightPoint.h \
    src/plant/PlantParser.h \
    src/plant/PlantLoader.h \
    src/plant/PlantInfo.h \
    src/GUI/GuiInterfaceQt.h \
    src/factories/ApplicationFactory.h \
    src/GUI/PlantView.h \
    src/plant/ApplicationSettings.h \
    src/OpenWebNet/OwnFormatter.h \
    src/terminal/CabledNetworkUI.h \
    src/GUI/ErrorNotifierQt.h \
    src/form/MessageViewer.h \
    src/OpenWebNet/OwnEngine.h \
    src/factories/PlantFactory.h \
    src/factories/PlantFactory_IF.h \
    src/GUI/LightButton.h

SOURCES += \
    src/form/MainWindow.cpp \
    src/main.cpp \
    src/OpenWebNet/OwnInputParser.cpp \
    src/OpenWebNet/OwnLink.cpp \
    src/OpenWebNet/OwnSocketTcp.cpp \
    src/plant/LightPoint.cpp \
    src/plant/PlantParser.cpp \
    src/plant/PlantLoader.cpp \
    src/plant/PlantInfo.cpp \
    src/GUI/GuiInterfaceQt.cpp \
    src/factories/ApplicationFactory.cpp \
    src/GUI/PlantView.cpp \
    src/plant/ApplicationSettings.cpp \
    src/OpenWebNet/OwnFormatter.cpp \
    src/terminal/CabledNetworkUI.cpp \
    src/GUI/ErrorNotifierQt.cpp \
    src/form/MessageViewer.cpp \
    src/OpenWebNet/OwnEngine.cpp \
    src/factories/PlantFactory.cpp \
    src/GUI/LightButton.cpp

