#include "MockPlantFactory.h"

#include <stdlib.h>

#include "PlantInfo.h"
#include "OwnEngine.h"
#include "OwnLink.h"
#include "OwnFormatter.h"
#include "OwnInputParser.h"
#include "MockNetworkUi.h"
#include "MockOwnSocket.h"
#include "MockErrorNotifier.h"
#include "MockGuiInterafce.h"


MockPlantFactory::MockPlantFactory()
{
}


OwnEngine *MockPlantFactory::buildOwnEngine(const PlantInfo & /*plantInfo*/)
{
   QObject *parent = new QObject();

   MockNetworkUi *network = new MockNetworkUi( parent);
   MockOwnSocket *socket = new MockOwnSocket(parent);
   OwnInputParser *ownParser = new OwnInputParser(parent);
   MockErrorNotifier *errorLogger = new MockErrorNotifier();
   OwnLink *ownLink = new OwnLink( *network, *socket, *ownParser, *errorLogger, parent);
   OwnFormatter *formatter = new OwnFormatter();
       /* formatter is never distroyed, but it has only static members. */

   return  new OwnEngine( *network, *ownLink, *formatter, parent);
}


void MockPlantFactory::destroyOwnEngine(OwnEngine * ownEngine)
{
   /* this deletes all objects created with engine, that
    * are all children of the same parent. */
   delete ownEngine->parent();
   ownEngine = NULL;
}


GuiInterface_IF *MockPlantFactory::buildGuiInterafce(OwnEngine *)
{
   return new MockGuiInterafce();
}


void MockPlantFactory::destroyGuiInterface(GuiInterface_IF *guiIf)
{
   delete guiIf;
}
