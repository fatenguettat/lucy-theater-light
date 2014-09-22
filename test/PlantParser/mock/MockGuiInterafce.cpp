#include "MockGuiInterafce.h"


MockGuiInterafce::MockGuiInterafce() :
   GuiInterface_IF()
{
}


void MockGuiInterafce::setPlantLayoutImagePath(const QString & fullPath)
{
   m_layoutPath = fullPath;
}

void MockGuiInterafce::addLightPoint( const GuiLightPoint & lightPoint)
{
   m_lightsList << lightPoint;
}

void MockGuiInterafce::showAsTurnedOn(int ownAddress)
{
   m_lightStatusTable[ownAddress] = LIGHT_ON;
}

void MockGuiInterafce::showAsTurnedOff(int ownAddress)
{
   m_lightStatusTable[ownAddress] = LIGHT_OFF;
}

MockGuiInterafce::LightStatus MockGuiInterafce::getLightStatus(int ownAddress)
{
   return m_lightStatusTable.value( ownAddress, LIGHT_NOT_SET);
}
