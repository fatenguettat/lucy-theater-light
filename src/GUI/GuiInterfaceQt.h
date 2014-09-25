#ifndef GUIINTERFACEQT_H
#define GUIINTERFACEQT_H

#include <QMap>

#include "GuiInterface_IF.h"

class QGraphicsScene;
class QGraphicsView;
class LightButton;


class GuiInterfaceQt : public GuiInterface_IF
{
public:
   GuiInterfaceQt( QGraphicsScene & scene, QGraphicsView & view);

   // GuiInterface_IF interface
public:
   virtual void setPlantLayoutImagePath(const QString &fullPath);
   virtual void setPlantLabel(const QString &label);
   virtual void addLightPoint(const GuiLightPoint &lightPoint);
   virtual void showAsTurnedOn(int ownAddress);
   virtual void showAsTurnedOff(int ownAddress);
   virtual void clear();

private:
   QGraphicsScene & m_scene;
   QGraphicsView & m_view;

   /* OWN address to graphic button */
   QMap< int, LightButton *> m_lightButtonTable;
};

#endif // GUIINTERFACEQT_H
