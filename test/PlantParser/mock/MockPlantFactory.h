#ifndef MOCKPLANTFACTORY_H
#define MOCKPLANTFACTORY_H

#include "PlantFactory_IF.h"

/**
 * @brief The MockPlantFactory class is a fake factory
 *   used for tests
 */
class MockPlantFactory : public PlantFactory_IF
{
public:
   MockPlantFactory();
   ~MockPlantFactory() {}

   // PlantFactory_IF interface
public:
   virtual GuiInterface_IF *buildGuiInterafce(OwnEngine *);
   virtual void destroyGuiInterface(GuiInterface_IF * guiIf);

   virtual OwnEngine *buildOwnEngine(const PlantInfo &plantInfo);
   virtual void destroyOwnEngine(OwnEngine *ownEngine);
};

#endif // MOCKPLANTFACTORY_H
