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

   virtual OwnEngine * buildOwnEngine(const PlantInfo &plantInfo);
};

#endif // MOCKPLANTFACTORY_H
