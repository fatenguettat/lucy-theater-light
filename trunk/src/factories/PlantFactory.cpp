#include "PlantFactory.h"

#include <QApplication>

#include "OwnEngine.h"
#include "GuiInterfaceQt.h"
#include "PlantInfo.h"
#include "PlantView.h"
#include "LightPanel.h"
#include "CabledNetworkUI.h"
#include "OwnSocketTcp.h"
#include "OwnInputParser.h"
#include "ErrorNotifier_IF.h"
#include "OwnLink.h"
#include "OwnFormatter.h"


PlantFactory::PlantFactory(PlantView &view, ErrorNotifier_IF &errorNotifier):
   m_errorLogger(errorNotifier),
   m_view(view),
   m_panel(NULL)
{
}

PlantFactory::~PlantFactory()
{
   delete m_panel;
}

OwnEngine *PlantFactory::buildOwnEngine(const PlantInfo &plantInfo)
{
   QObject *parent = new QObject();

   CabledNetworkUI *network = new CabledNetworkUI( plantInfo.getGatewayIpAddress(),
                                                   plantInfo.getGatewayIpPort(), parent);
   OwnSocketTcp *socket = new OwnSocketTcp(parent);
   OwnInputParser *ownParser = new OwnInputParser(parent);
   OwnLink *ownLink = new OwnLink( *network, *socket, *ownParser, m_errorLogger, parent);
   OwnFormatter *formatter = new OwnFormatter();
   /* formatter is never distroyed, but it has only static members. */

   return  new OwnEngine( *network, *ownLink, *formatter, parent);
}

void PlantFactory::destroyOwnEngine(OwnEngine *ownEngine)
{
   /* this deletes all objects created with engine, that
    * are all children of the same parent. */
   delete ownEngine->parent();
   ownEngine = NULL;
}


GuiInterface_IF *PlantFactory::buildGuiInterafce( OwnEngine *engine)
{
   /* building the panel in constructor results in runtime error */
   if (m_panel)
   {
      delete m_panel;
      m_panel = NULL;
   }
   m_panel = new LightPanel(&m_view);

   return new GuiInterfaceQt( *engine, *m_view.scene(), m_view, *m_panel);
}

void PlantFactory::destroyGuiInterface(GuiInterface_IF *guiIf)
{
   guiIf->clear();
   delete guiIf;
}


