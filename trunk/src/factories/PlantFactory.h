#ifndef PLANTFACTORY_H
#define PLANTFACTORY_H

#include "PlantFactory_IF.h"

class OwnEngine;
class GuiInterface_IF;
class PlantInfo;
class PlantView;
class ErrorNotifier_IF;


class PlantFactory : public PlantFactory_IF
{
public:
   PlantFactory( PlantView & view, ErrorNotifier_IF &errorNotifier);

   // PlantFactory_IF interface
public:
   virtual GuiInterface_IF *buildGuiInterafce(OwnEngine *engine);
   virtual void destroyGuiInterface(GuiInterface_IF *guiIf);

   virtual OwnEngine *buildOwnEngine(const PlantInfo &plantInfo);
   virtual void destroyOwnEngine(OwnEngine *ownEngine);

private:
   ErrorNotifier_IF & m_errorLogger;
   PlantView & m_view;
};

#endif // PLANTFACTORY_H
