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
    ./src/factories


FORMS    += src/form/MainWindow.ui

CONFIG += mobility
MOBILITY =

RESOURCES += \
    res/resources.qrc

HEADERS += \
    src/configuration.h \
    src/form/MainWindow.h \
    src/GUI/Button.h \
    src/GUI/GuiInterface_IF.h \
    src/OpenWebNet/ErrorNotifier_IF.h \
    src/OpenWebNet/NetworkUi_IF.h \
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
    src/GUI/PlantView.h

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
    src/GUI/PlantView.cpp

