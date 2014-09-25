#include "GuiInterfaceQt.h"

#include <QGraphicsScene>
#include <QGraphicsView>

#include "LightButton.h"
#include "testableAssert.h"


GuiInterfaceQt::GuiInterfaceQt(QGraphicsScene &scene, QGraphicsView &view) :
   m_scene(scene),
   m_view(view)
{
}


void GuiInterfaceQt::setPlantLayoutImagePath(const QString &fullPath)
{
   QPixmap pixamp(fullPath);
   m_scene.addPixmap( pixamp);
   m_scene.setSceneRect( 0., 0., pixamp.width(), pixamp.height());
}


void GuiInterfaceQt::setPlantLabel(const QString &label)
{
   // on ANDROID this is lost
   m_view.topLevelWidget()->setWindowTitle( label);
}


void GuiInterfaceQt::addLightPoint(const GuiLightPoint & lightPoint)
{
   int ownAddress = lightPoint.ownAddress;

   LightButton *light = new LightButton( ownAddress);
   light->setState( LightButton::LIGHT_UNKNOWN);

   m_scene.addItem( light);

   // WARNING !!!!  make the correct request
   connect (light, SIGNAL(pressed(int)), this, SIGNAL(turnOnRequest(int)) );

   light->moveBy( m_scene.width() * lightPoint.position.x(),
                  m_scene.height() * lightPoint.position.y());

   m_lightButtonTable.insert( ownAddress, light);
}


void GuiInterfaceQt::showAsTurnedOn(int ownAddress)
{
   LightButton *light = m_lightButtonTable[ownAddress];
   T_ASSERT( light != NULL);

   light->setState(LightButton::LIGHT_ON);
}


void GuiInterfaceQt::showAsTurnedOff(int ownAddress)
{
   LightButton *light = m_lightButtonTable[ownAddress];
   T_ASSERT( light != NULL);

   light->setState(LightButton::LIGHT_OFF);
}


void GuiInterfaceQt::clear()
{
   m_scene.clear();
   m_lightButtonTable.clear();
}
