#include "PlantLoader.h"

#include <QFileInfo>

#include "PlantInfo.h"
#include "GuiInterface_IF.h"


PlantLoader::PlantLoader(GuiInterface_IF & guiinterface) :
   m_guiInterface(guiinterface)
{
}



void PlantLoader::load(const PlantInfo & plantInfo)
{
   loadPlantLayout(plantInfo);
   loadLightpoints(plantInfo);
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
