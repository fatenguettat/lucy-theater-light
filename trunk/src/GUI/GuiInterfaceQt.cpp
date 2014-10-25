#include "GuiInterfaceQt.h"

#include <QGraphicsScene>
#include <QGraphicsView>

#include "LightButton.h"
#include "LightPanel.h"
#include "LightPoint.h"
#include "LightGroup.h"
#include "testableAssert.h"
#include "OwnEngine.h"
#include "Scenario.h"
#include "ScenarioButton.h"


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
            this, SLOT(storeLightPoint(const LightPoint*)) );
   connect( &m_ownEngine, SIGNAL(lightGroupAdded(const LightGroup*)),
            this, SLOT(storeLightGroup(const LightGroup*)) );
   connect( &m_ownEngine, SIGNAL(lightOnAcked(own::Where)),
            this, SLOT(showAsTurnedOn(own::Where)) );
   connect( &m_ownEngine, SIGNAL(lightOffAcked(own::Where)),
            this, SLOT(showAsTurnedOff(own::Where)) );
   connect( &m_ownEngine, SIGNAL(lightLevelAcked(own::Where,own::LIGHT_LEVEL)),
            this, SLOT(showAsLevel(own::Where,own::LIGHT_LEVEL)) );
   connect( &m_ownEngine, SIGNAL(scenarioAdded(const Scenario*)),
            this, SLOT(storeScenario(const Scenario*)) );
}


void GuiInterfaceQt::setPlantLayoutImagePath(const QString &fullPath)
{
   QPixmap pixamp(fullPath);
   m_scene.addPixmap( pixamp);
   m_scene.setSceneRect( 0., 0., pixamp.width(), pixamp.height());
}


void GuiInterfaceQt::setPlantLabel(const QString &label)
{
   /* show plant label on window title (when available) */
   m_view.topLevelWidget()->setWindowTitle( label);
}


void GuiInterfaceQt::storeLightPoint(const LightPoint *lightPoint)
{
   own::Where ownAddress = lightPoint->ownAddress();

   LightButton *light = new LightButton( ownAddress);
   light->setState( LightButton::LIGHT_UNKNOWN);

   m_scene.addItem( light);

   connect (light, SIGNAL(hit(own::Where)), this, SLOT(onLightButtonPressed(own::Where)) );

   light->moveBy( m_scene.width() * lightPoint->position().x(),
                  m_scene.height() * lightPoint->position().y());

   m_lightButtonTable.insert( ownAddress, light);
}


void GuiInterfaceQt::storeLightGroup(const LightGroup *lightPoint)
{
   own::Where ownAddress = lightPoint->node().ownAddress();

   LightButton *button = new LightButton( ownAddress);
   button->setState( LightButton::LIGHT_IS_HANDLER);

   m_scene.addItem( button);

   connect (button, SIGNAL(hit(own::Where)), this, SLOT(onLightButtonPressed(own::Where)) );

   button->moveBy( m_scene.width() * lightPoint->node().position().x(),
                   m_scene.height() * lightPoint->node().position().y());

   m_groupButtonTable.insert( ownAddress, button);
}


void GuiInterfaceQt::storeScenario(const Scenario *scenario)
{
   T_ASSERT( scenario != NULL);

   ScenarioButton *button = new ScenarioButton( scenario);
   m_scene.addItem( button);

   connect (button, SIGNAL(hit(const Scenario *)),
            this, SLOT(onScenarioButtonPressed(const Scenario *)) );

   // TODO move by ...
   button->moveBy( 250, 5);
}

void GuiInterfaceQt::onScenarioButtonPressed(const Scenario *scenario)
{
   m_ownEngine.scenarioRequest( scenario->getDescription());
}


void GuiInterfaceQt::showAsTurnedOn( const own::Where & ownAddress)
{
   LightButton *light = m_lightButtonTable[ownAddress];
   T_ASSERT( light != NULL);

   light->setState(LightButton::LIGHT_ON);
}


void GuiInterfaceQt::showAsTurnedOff( const own::Where & ownAddress)
{
   LightButton *light = m_lightButtonTable[ownAddress];
   T_ASSERT( light != NULL);

   light->setState(LightButton::LIGHT_OFF);
}

void GuiInterfaceQt::showAsUnknownState( const own::Where &ownAddress)
{
   LightButton *light = m_lightButtonTable[ownAddress];
   T_ASSERT( light != NULL);

   light->setState(LightButton::LIGHT_UNKNOWN);
}

void GuiInterfaceQt::showAsLevel( const own::Where & ownAddress, own::LIGHT_LEVEL /*level*/)
{
   LightButton *light = m_lightButtonTable[ownAddress];
   T_ASSERT( light != NULL);

   // TODO maybe use icon overlay?
   light->setState(LightButton::LIGHT_ON);
}


void GuiInterfaceQt::clear()
{
   m_scene.clear();
   m_lightButtonTable.clear();
}

void GuiInterfaceQt::onLightButtonPressed( const own::Where & ownAddress)
{
   /* store OWN address to be used by callbacks from light panel */
   m_currentOwnAddr = ownAddress;

   QString label = QString("<b>%1: </b><br/>%2").
                   arg(ownAddress).arg(m_ownEngine.getLightDescription(ownAddress));
   m_lightPanel.setHtmlLabel(label);

   m_lightPanel.exec();
   m_currentOwnAddr= QString();
}


void GuiInterfaceQt::onGuiRequestTurnOn()
{
   T_ASSERT( m_currentOwnAddr != QString());
   m_ownEngine.lightRequestOn( m_currentOwnAddr);
}

void GuiInterfaceQt::onGuiRequestTurnOff()
{
   T_ASSERT( m_currentOwnAddr != QString());
   m_ownEngine.lightRequestOff( m_currentOwnAddr);
}

void GuiInterfaceQt::onGuiRequestSetLevel(own::LIGHT_LEVEL level)
{
   T_ASSERT( m_currentOwnAddr != QString());
   m_ownEngine.lightRequestLevel( m_currentOwnAddr, level);
}

