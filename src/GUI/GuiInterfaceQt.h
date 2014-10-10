#ifndef GUIINTERFACEQT_H
#define GUIINTERFACEQT_H

#include <QHash>

#include "GuiInterface_IF.h"

class QGraphicsScene;
class QGraphicsView;
class LightButton;
class LightGroup;
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
   virtual void storeLightPoint( const LightPoint *lightPoint);
   virtual void storeLightGroup( const LightGroup *lightPoint);
   virtual void showAsTurnedOn( const own::Where &  ownAddress);
   virtual void showAsTurnedOff( const own::Where & ownAddress);
   virtual void showAsUnknownState( const own::Where & ownAddress);
   virtual void showAsLevel( const own::Where & ownAddress, own::LIGHT_LEVEL level);


public slots:
   /* callback from main plant */
   void onLightButtonPressed(const own::Where & ownAddress);

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
   own::Where m_currentOwnAddr;

   /* OWN address to graphic button */
   QHash< const own::Where, LightButton *> m_lightButtonTable;
   QHash< const own::Where, LightButton *> m_groupButtonTable;
};

#endif // GUIINTERFACEQT_H
