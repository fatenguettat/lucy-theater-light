#ifndef PLANT_FACTORY_INTERFACE_H
#define PLANT_FACTORY_INTERFACE_H

class OwnEngine;
class PlantInfo;

/**
 * @brief The PlantFactory_IF class only exists to allow mocking
 *  a real factory in tests.
 */
class PlantFactory_IF
{
public:
   PlantFactory_IF () {}

   virtual OwnEngine * buildOwnEngine(const PlantInfo &plantInfo) = 0;
};

#endif // PLANT_FACTORY_INTERFACE_H
