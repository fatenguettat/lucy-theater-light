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

void MockGuiInterafce::setPlantLabel(const QString &label)
{
   m_layoutLabel = label;
}

MockGuiInterafce::LightStatus MockGuiInterafce::getLightStatus(int ownAddress)
{
   return m_lightStatusTable.value( ownAddress, LIGHT_NOT_SET);
}

void MockGuiInterafce::clear()
{
   m_layoutPath = QString();
   m_lightsList.clear();
}
