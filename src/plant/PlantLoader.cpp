#include "PlantLoader.h"

#include <QFileInfo>

#include "testableAssert.h"
#include "PlantInfo.h"
#include "GuiInterface_IF.h"
#include "OwnEngine.h"


PlantLoader::PlantLoader( QObject *parent) :
   QObject(parent),
   m_guiInterface(NULL),
   m_ownEngine(NULL)
{
}

PlantLoader::~PlantLoader()
{
}


void PlantLoader::load(const PlantInfo & plantInfo,
                       GuiInterface_IF *guiInterface,
                       OwnEngine *ownEngine)
{
   m_ownEngine = ownEngine;
   m_guiInterface = guiInterface;

   loadPlantLayout(plantInfo);
   loadLightpoints(plantInfo);

   emit plantLoaded(true);
}

void PlantLoader::unload()
{
   T_ASSERT( m_guiInterface != NULL);
   T_ASSERT( m_ownEngine != NULL);

   m_guiInterface->clear();
   m_ownEngine->clearPlant();

   emit plantLoaded(false);
}


void PlantLoader::loadPlantLayout(const PlantInfo& plantInfo)
{
   QFileInfo fileInfo(plantInfo.getPlantFilePath());

   // TODO exceptions should be an internal mechanism
   if (! fileInfo.exists())
   {
      throw QString("unable to load file: ") + fileInfo.absoluteFilePath();
   }

   m_guiInterface->setPlantLayoutImagePath( fileInfo.absoluteFilePath());
   m_guiInterface->setPlantLabel( plantInfo.getPlantLabel());
}


void PlantLoader::loadLightpoints(const PlantInfo& plantInfo)
{
   /* lights are loaded to engine only */
   foreach (const LightPoint * light, plantInfo.getLightPoints())
   {
      m_ownEngine->addLightPoint( *light);
   }
}

