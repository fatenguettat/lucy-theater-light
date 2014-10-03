#ifndef PLANT_FACTORY_INTERFACE_H
#define PLANT_FACTORY_INTERFACE_H

class OwnEngine;
class PlantInfo;
class GuiInterface_IF;

/**
 * @brief The PlantFactory_IF class only exists to allow mocking
 *  a real factory in tests.
 */
class PlantFactory_IF
{
public:
   PlantFactory_IF () {}

   virtual OwnEngine * buildOwnEngine(const PlantInfo &plantInfo) = 0;
   virtual void destroyOwnEngine(OwnEngine *ownEngine) = 0;

   virtual GuiInterface_IF *buildGuiInterafce(OwnEngine *) = 0;
   virtual void destroyGuiInterface( GuiInterface_IF *) = 0;
};

#endif // PLANT_FACTORY_INTERFACE_H
