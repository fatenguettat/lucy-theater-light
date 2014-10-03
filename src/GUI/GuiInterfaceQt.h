#ifndef GUIINTERFACEQT_H
#define GUIINTERFACEQT_H

#include <QMap>

#include "GuiInterface_IF.h"

class QGraphicsScene;
class QGraphicsView;
class LightButton;
class LightPanel;
class OwnEngine;


class GuiInterfaceQt : public GuiInterface_IF
{
   Q_OBJECT
public:
   GuiInterfaceQt( OwnEngine &ownEngine,
                   QGraphicsScene &scene, QGraphicsView &view,
                   LightPanel & panel);
   ~GuiInterfaceQt() {}

   // GuiInterface_IF interface
public:
   virtual void setPlantLayoutImagePath(const QString &fullPath);
   virtual void setPlantLabel(const QString &label);
   virtual void clear();
public slots:
   virtual void addLightPoint(const LightPoint *lightPoint);
   virtual void showAsTurnedOn(int ownAddress);
   virtual void showAsTurnedOff(int ownAddress);
   virtual void showAsUnknownState( int ownAddress);
   virtual void showAsLevel( int ownAddress, own::LIGHT_LEVEL level);


public slots:
   /* callback from main plant */
   void onLightButtonPressed(int ownAddress);

private slots:
   /* callbacks from light panel */
   void onGuiRequestTurnOn();
   void onGuiRequestTurnOff();
   void onGuiRequestSetLevel(own::LIGHT_LEVEL level);

private:
   OwnEngine & m_ownEngine;
   QGraphicsScene & m_scene;
   QGraphicsView & m_view;
   LightPanel &m_lightPanel;

   /* OWN address for current operation */
   int m_currentOwnAddr;

   /* OWN address to graphic button */
   QMap< int, LightButton *> m_lightButtonTable;
};

#endif // GUIINTERFACEQT_H
