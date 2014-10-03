#include "GuiInterfaceQt.h"

#include <QGraphicsScene>
#include <QGraphicsView>

#include "LightButton.h"
#include "LightPanel.h"
#include "LightPoint.h"
#include "testableAssert.h"
#include "OwnEngine.h"


GuiInterfaceQt::GuiInterfaceQt( OwnEngine &ownEngine,
                                QGraphicsScene &scene, QGraphicsView &view,
                                LightPanel & panel) :
   m_ownEngine(ownEngine),
   m_scene(scene),
   m_view(view),
   m_lightPanel(panel),
   m_currentOwnAddr(0xFF)
{
   /* connect light panel actions to signals  */
   connect( &m_lightPanel, SIGNAL(requestTurnOn()), this, SLOT(onGuiRequestTurnOn()) );
   connect( &m_lightPanel, SIGNAL(requestTurnOff()), this, SLOT(onGuiRequestTurnOff()) );
   connect( &m_lightPanel, SIGNAL(requestSetLevel(own::LIGHT_LEVEL)),
            this, SLOT(onGuiRequestSetLevel(own::LIGHT_LEVEL)) );

   /* listen for events from engine */
   connect( &m_ownEngine, SIGNAL(lightPointAdded(const LightPoint*)),
            this, SLOT(addLightPoint(const LightPoint*)) );
}


void GuiInterfaceQt::setPlantLayoutImagePath(const QString &fullPath)
{
   QPixmap pixamp(fullPath);
   m_scene.addPixmap( pixamp);
   m_scene.setSceneRect( 0., 0., pixamp.width(), pixamp.height());
}


void GuiInterfaceQt::setPlantLabel(const QString &label)
{
   //TODO on ANDROID this is lost
   m_view.topLevelWidget()->setWindowTitle( label);
}


void GuiInterfaceQt::addLightPoint(const LightPoint *lightPoint)
{
   int ownAddress = lightPoint->ownAddress();

   LightButton *light = new LightButton( ownAddress);
   light->setState( LightButton::LIGHT_UNKNOWN);

   m_scene.addItem( light);

   connect (light, SIGNAL(pressed(int)), this, SLOT(onLightButtonPressed(int)) );

   light->moveBy( m_scene.width() * lightPoint->position().x(),
                  m_scene.height() * lightPoint->position().y());

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

void GuiInterfaceQt::showAsUnknownState(int ownAddress)
{
   LightButton *light = m_lightButtonTable[ownAddress];
   T_ASSERT( light != NULL);

   light->setState(LightButton::LIGHT_UNKNOWN);
}


void GuiInterfaceQt::clear()
{
   m_scene.clear();
   m_lightButtonTable.clear();
}

void GuiInterfaceQt::onLightButtonPressed(int ownAddress)
{
   /* store OWN address to be used by callbacks from light panel */
   m_currentOwnAddr = ownAddress;

   /* position light control panel according to button */
   LightButton *button = m_lightButtonTable.value( ownAddress);
   T_ASSERT( button != NULL);

   m_lightPanel.setWindowTitle(tr("Light Point %1").arg(ownAddress));
   m_lightPanel.move(button->pos().toPoint());

   m_lightPanel.exec();
   m_currentOwnAddr = 0xFF;
}


void GuiInterfaceQt::onGuiRequestTurnOn()
{
   T_ASSERT( m_currentOwnAddr != 0xFF);
   m_ownEngine.lightPointRequestOn( m_currentOwnAddr);
}

void GuiInterfaceQt::onGuiRequestTurnOff()
{
   T_ASSERT( m_currentOwnAddr != 0xFF);
   m_ownEngine.lightPointRequestOff( m_currentOwnAddr);
}

void GuiInterfaceQt::onGuiRequestSetLevel(own::LIGHT_LEVEL level)
{
   T_ASSERT( m_currentOwnAddr != 0xFF);
   m_ownEngine.lightPointRequestLevel( m_currentOwnAddr, level);
}
