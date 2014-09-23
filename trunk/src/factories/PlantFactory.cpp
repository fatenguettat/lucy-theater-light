#include "PlantFactory.h"

#include <QApplication>

#include "OwnEngine.h"
#include "GuiInterface_IF.h"
#include "PlantInfo.h"
#include "CabledNetworkUI.h"
#include "OwnSocketTcp.h"
#include "OwnInputParser.h"
#include "ErrorNotifier_IF.h"
#include "OwnLink.h"
#include "OwnFormatter.h"


PlantFactory::PlantFactory(GuiInterface_IF & guiInterface,
                           ErrorNotifier_IF &errorNotifier):
   m_guiInterface( guiInterface),
   m_errorLogger(errorNotifier),
   parent(new QObject())
{
}

OwnEngine *PlantFactory::buildOwnEngine(const PlantInfo & plantInfo)
{
   delete parent; /* this also deletes eventual children */
   parent = new QObject();

   CabledNetworkUI *network = new CabledNetworkUI( plantInfo.getGatewayIpAddress(),
                                                   plantInfo.getGatewayIpPort(), parent);
   OwnSocketTcp *socket = new OwnSocketTcp(parent);
   OwnInputParser *ownParser = new OwnInputParser(parent);
   OwnLink *ownLink = new OwnLink( *network, *socket, *ownParser, m_errorLogger, parent);
   OwnFormatter *formatter = new OwnFormatter();

   /* formatter is never distroyed, but it has only static members. */

   return  new OwnEngine( m_guiInterface, *network, *ownLink, *formatter);
}
