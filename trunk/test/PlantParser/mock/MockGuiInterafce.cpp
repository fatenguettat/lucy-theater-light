#include "MockGuiInterafce.h"

//#include <QGraphicsPixmapItem.h>

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

void MockGuiInterafce::showAsTurnedOn(int /*ownAddress*/)
{
}

void MockGuiInterafce::showAsTurnedOff(int /*ownAddress*/)
{
}
