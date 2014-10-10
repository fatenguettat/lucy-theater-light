#include "MockGuiInterafce.h"

#include "LightPoint.h"


MockGuiInterafce::MockGuiInterafce() :
   GuiInterface_IF()
{
}


void MockGuiInterafce::setPlantLayoutImagePath(const QString & fullPath)
{
   m_layoutPath = fullPath;
}


void MockGuiInterafce::storeLightPoint(const LightPoint *lightPoint)
{
   m_lightsList << *lightPoint;
}


void MockGuiInterafce::showAsTurnedOn(const own::Where & ownAddress)
{
   m_lightStatusTable.insert(ownAddress, LIGHT_ON);
}


void MockGuiInterafce::showAsTurnedOff(const own::Where & ownAddress)
{
   m_lightStatusTable.insert(ownAddress, LIGHT_OFF);
}


void MockGuiInterafce::showAsUnknownState(const own::Where & ownAddress)
{
   m_lightStatusTable.insert(ownAddress, LIGHT_UNKNOWN);
}

void MockGuiInterafce::showAsLevel(const own::Where &ownAddress, own::LIGHT_LEVEL /*level*/)
{
   m_lightStatusTable.insert(ownAddress, LIGHT_MID_LEVEL);
}


void MockGuiInterafce::setPlantLabel(const QString &label)
{
   m_layoutLabel = label;
}


MockGuiInterafce::LightStatus MockGuiInterafce::mockGetLightStatus(const own::Where &ownAddress)
{
   return m_lightStatusTable.value( ownAddress, LIGHT_NOT_SET);
}


void MockGuiInterafce::clear()
{
   m_layoutPath = QString();
   m_lightsList.clear();
}

