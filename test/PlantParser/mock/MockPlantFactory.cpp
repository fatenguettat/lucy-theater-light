#include "MockPlantFactory.h"

#include <stdlib.h>

MockPlantFactory::MockPlantFactory()
{
}

OwnEngine *MockPlantFactory::buildOwnEngine(const PlantInfo & /*plantInfo*/)
{
   return NULL;
}
