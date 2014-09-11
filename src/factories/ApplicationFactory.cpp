#include "ApplicationFactory.h"

#include <QGraphicsScene>
#include <QGraphicsView>

#include "mainwindow.h"
#include "PlantLoader.h"
#include "PlantParser.h"
#include "GuiInterfaceQt.h"


ApplicationFactory::ApplicationFactory()
{
}

MainWindow *ApplicationFactory::buildMainWindow()
{
   QGraphicsScene  *scene = new QGraphicsScene(NULL);
   QGraphicsView * view = new QGraphicsView( scene);
   GuiInterfaceQt *gui = new GuiInterfaceQt( *scene, *view);
   PlantLoader  *plantLoader = new PlantLoader( *gui);
   PlantParser *plantParser = new PlantParser();

   return  new MainWindow( *plantParser, *plantLoader, *view);
}
