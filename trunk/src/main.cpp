#include "MainWindow.h"
#include <QApplication>

#include "ApplicationFactory.h"


int main(int argc, char *argv[])
{
   QApplication a(argc, argv);

   ApplicationFactory factory;
   MainWindow * w = factory.buildMainWindow();

   w->show();

   return a.exec();
}
