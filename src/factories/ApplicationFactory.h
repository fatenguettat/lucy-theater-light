#ifndef APPLICATIONFACTORY_H
#define APPLICATIONFACTORY_H

class MainWindow;


class ApplicationFactory
{
public:
   ApplicationFactory();

   MainWindow * buildMainWindow();
};

#endif // APPLICATIONFACTORY_H
