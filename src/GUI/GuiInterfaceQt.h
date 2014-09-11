#ifndef GUIINTERFACEQT_H
#define GUIINTERFACEQT_H

#include "GuiInterface_IF.h"

class QGraphicsScene;
class QGraphicsView;


class GuiInterfaceQt : public GuiInterface_IF
{
public:
   GuiInterfaceQt( QGraphicsScene & scene, QGraphicsView & view);

   // GuiInterface_IF interface
public:
   virtual void setPlantLayoutImagePath(const QString &fullPath);
   virtual void addLightPoint(const GuiLightPoint &lightPoint);
   virtual void showAsTurnedOn(int ownAddress);
   virtual void showAsTurnedOff(int ownAddress);

private:
   QGraphicsScene & m_scene;
   QGraphicsView & m_view;
};

#endif // GUIINTERFACEQT_H
