#include "GuiInterfaceQt.h"

#include <QGraphicsScene>
#include <QGraphicsView>

#include "Button.h"
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

   Button *lightOff = new Button( QPixmap(":/images/images/lightOff.png"), ownAddress);
   Button *lightOn = new Button( QPixmap(":/images/images/lightOn.png"), ownAddress);

   m_scene.addItem( lightOff);
   m_scene.addItem( lightOn);

   connect (lightOff, SIGNAL(pressed(int)), this, SIGNAL(turnOnRequest(int)) );
   connect (lightOn, SIGNAL(pressed(int)), this, SIGNAL(turnOffRequest(int)) );

   lightOff->moveBy( m_scene.width() * lightPoint.position.x(),
                     m_scene.height() * lightPoint.position.y());
   lightOn->moveBy( m_scene.width() * lightPoint.position.x(),
                    m_scene.height() * lightPoint.position.y());

   m_offButtonTable.insert( ownAddress, lightOff);
   m_onButtonTable.insert( ownAddress, lightOn);

   showAsTurnedOn( ownAddress);
}


void GuiInterfaceQt::showAsTurnedOn(int ownAddress)
{
   Button *lightOn = m_onButtonTable[ownAddress];
   Button *lightOff = m_offButtonTable[ownAddress];

   T_ASSERT( lightOn != NULL);
   T_ASSERT( lightOff != NULL);

   lightOn->setVisible( true);
   lightOff->setVisible( false);
}


void GuiInterfaceQt::showAsTurnedOff(int ownAddress)
{
   Button *lightOn = m_onButtonTable[ownAddress];
   Button *lightOff = m_offButtonTable[ownAddress];

   T_ASSERT( lightOn != NULL);
   T_ASSERT( lightOff != NULL);

   lightOn->setVisible( false);
   lightOff->setVisible( true);
}



