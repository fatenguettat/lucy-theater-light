#include "ApplicationFactory.h"

#include <QGraphicsScene>

#include "ApplicationSettings.h"
#include "PlantFactory.h"
#include "PlantView.h"
#include "mainwindow.h"
#include "PlantLoader.h"
#include "PlantParser.h"
#include "PlantView.h"
#include "ErrorNotifierQt.h"


ApplicationFactory::ApplicationFactory()
{
}

MainWindow *ApplicationFactory::buildMainWindow()
{
   QGraphicsScene  *scene = new QGraphicsScene(NULL);
   PlantView * view = new PlantView( scene);
   ErrorNotifier_IF *errorNotifier = new ErrorNotifierQt( NULL);
   PlantFactory * plantFactory = new PlantFactory( *view, *errorNotifier);
   PlantLoader  *plantLoader = new PlantLoader(NULL);
   PlantParser *plantParser = new PlantParser();
   ApplicationSettings *settings = new ApplicationSettings();

   MainWindow * mainWindow = new MainWindow( *plantParser, *plantLoader, *view,
                                             *plantFactory, *settings,
                                             *errorNotifier);

   return  mainWindow;
}
