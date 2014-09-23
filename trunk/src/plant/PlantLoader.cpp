#include "PlantLoader.h"

#include <QFileInfo>

#include "PlantInfo.h"
#include "GuiInterface_IF.h"
#include "PlantFactory.h"


PlantLoader::PlantLoader(GuiInterface_IF & guiinterface,
                         PlantFactory_IF & plantFactory) :
   m_guiInterface(guiinterface),
   m_plantFactory(plantFactory)
{
}



void PlantLoader::load(const PlantInfo & plantInfo)
{
   loadPlantLayout(plantInfo);
   loadLightpoints(plantInfo);

   m_plantFactory.buildOwnEngine( plantInfo);
}


void PlantLoader::loadPlantLayout(const PlantInfo& plantInfo)
{
   QFileInfo fileInfo(plantInfo.getPlantFilePath());

   // TODO exceptions should be an internal mechanism
   if (! fileInfo.exists())
   {
      throw QString("unable to load file: ") + fileInfo.absoluteFilePath();
   }

   m_guiInterface.setPlantLayoutImagePath( fileInfo.absoluteFilePath());
   m_guiInterface.setPlantLabel( plantInfo.getPlantLabel());
}


void PlantLoader::loadLightpoints(const PlantInfo& plantInfo)
{
   GuiInterface_IF::GuiLightPoint guiLight;

   foreach (const LightPoint * light, plantInfo.getLightPoints())
   {
      guiLight.ownAddress = light->ownAddress();
      guiLight.position = light->position();

      m_guiInterface.addLightPoint( guiLight);
   }
}
