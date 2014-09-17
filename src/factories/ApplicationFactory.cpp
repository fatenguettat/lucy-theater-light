#include "ApplicationFactory.h"

#include <QGraphicsScene>

#include "PlantView.h"
#include "mainwindow.h"
#include "PlantLoader.h"
#include "PlantParser.h"
#include "GuiInterfaceQt.h"
#include "PlantView.h"


ApplicationFactory::ApplicationFactory()
{
}

MainWindow *ApplicationFactory::buildMainWindow()
{
   QGraphicsScene  *scene = new QGraphicsScene(NULL);
   PlantView * view = new PlantView( scene);
   GuiInterfaceQt *gui = new GuiInterfaceQt( *scene, *view);
   PlantLoader  *plantLoader = new PlantLoader( *gui);
   PlantParser *plantParser = new PlantParser();

   return  new MainWindow( *plantParser, *plantLoader, *view);
}
