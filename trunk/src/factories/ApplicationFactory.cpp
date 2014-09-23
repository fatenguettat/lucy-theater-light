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
#include "ErrorNotifierQt.h"


ApplicationFactory::ApplicationFactory()
{
}

MainWindow *ApplicationFactory::buildMainWindow()
{
   QGraphicsScene  *scene = new QGraphicsScene(NULL);
   PlantView * view = new PlantView( scene);
   GuiInterfaceQt *gui = new GuiInterfaceQt( *scene, *view);
   ErrorNotifier_IF *errorNotifier = new ErrorNotifierQt( NULL);
   PlantFactory * plantFactory = new PlantFactory( *gui, *errorNotifier);
   PlantLoader  *plantLoader = new PlantLoader( *gui, *plantFactory);
   PlantParser *plantParser = new PlantParser();
   ApplicationSettings *settings = new ApplicationSettings();

   MainWindow * mainWindow = new MainWindow( *plantParser, *plantLoader, *view,
                                             *settings, *errorNotifier);

   return  mainWindow;
}
