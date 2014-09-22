#include "ApplicationFactory.h"

#include <QGraphicsScene>

#include "ApplicationSettings.h"
#include "PlantFactory.h"
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
   PlantFactory * plantFactory = new PlantFactory( *gui);
   PlantLoader  *plantLoader = new PlantLoader( *gui, *plantFactory);
   PlantParser *plantParser = new PlantParser();
   ApplicationSettings *settings = new ApplicationSettings();

   return  new MainWindow( *plantParser, *plantLoader, *view, *settings);
}
