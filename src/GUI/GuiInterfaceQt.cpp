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
   m_scene.addPixmap( QPixmap(fullPath));
}

void GuiInterfaceQt::addLightPoint(const GuiLightPoint & lightPoint)
{
   Button *lightOff = new Button( QPixmap(":/images/images/lightOff.png"));

   m_scene.addItem( lightOff);
   lightOff->setPos( m_scene.width() * lightPoint.position.x(),
                     m_scene.height() * lightPoint.position.y());
}

void GuiInterfaceQt::showAsTurnedOn(int /*ownAddress*/)
{
}

void GuiInterfaceQt::showAsTurnedOff(int /*ownAddress*/)
{
}
