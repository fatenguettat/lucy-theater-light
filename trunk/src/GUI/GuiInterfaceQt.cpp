#include "GuiInterfaceQt.h"

#include <QGraphicsScene>
#include <QGraphicsView>

#include "Button.h"



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


void GuiInterfaceQt::addLightPoint(const GuiLightPoint & lightPoint)
{
   Button *lightOff = new Button( QPixmap(":/images/images/lightOff.png"));
   Button *lightOn = new Button( QPixmap(":/images/images/lightOn.png"));

   m_scene.addItem( lightOff);
   m_scene.addItem( lightOn);

   connect (lightOff, SIGNAL(pressed(int)), this, SIGNAL(turnOffRequest(int)) );
   connect (lightOff, SIGNAL(pressed(int)), this, SIGNAL(turnOffRequest(int)) );

   lightOff->moveBy( m_scene.width() * lightPoint.position.x(),
                     m_scene.height() * lightPoint.position.y());
   lightOn->moveBy( m_scene.width() * lightPoint.position.x(),
                    m_scene.height() * lightPoint.position.y());

   m_offButtonTable.insert( lightPoint.ownAddress, lightOff);
   m_onButtonTable.insert( lightPoint.ownAddress, lightOn);

   showAsTurnedOff( lightPoint.ownAddress);
}


void GuiInterfaceQt::showAsTurnedOn(int ownAddress)
{
   Button *lightOn = m_onButtonTable[ownAddress];
   Button *lightOff = m_offButtonTable[ownAddress];

   lightOn->setVisible( true);
   lightOff->setVisible( false);
}


void GuiInterfaceQt::showAsTurnedOff(int ownAddress)
{
   Button *lightOn = m_onButtonTable[ownAddress];
   Button *lightOff = m_offButtonTable[ownAddress];

   lightOn->setVisible( false);
   lightOff->setVisible( true);
}
