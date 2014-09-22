#include "OwnEngine.h"

#include "GuiInterface_IF.h"
#include "NetworkUi_IF.h"
#include "OwnLink.h"
#include "OwnFormatter.h"


OwnEngine::OwnEngine(GuiInterface_IF & guiInterface, NetworkUi_IF & networkInterface,
                     OwnLink & ownLink, OwnFormatter & ownformatter,
                     QObject *parent) :
   QObject(parent),
   m_guiInterface(guiInterface),
   m_networkInterface(networkInterface),
   m_ownLink(ownLink),
   m_ownFormatter(ownformatter)
{
   connect( &m_guiInterface, SIGNAL(turnOnRequest(int)),
            this, SLOT(onLightPointRequestOn(int)) );
   connect( &m_guiInterface, SIGNAL(turnOffRequest(int)),
            this, SLOT(onLightPointRequestOff(int)) );
}

void OwnEngine::onLightPointRequestOn(int ownAddress)
{
   QString message = m_ownFormatter.lightOn(ownAddress);
   m_ownLink.triggerSendMessage( message);

   // TODO this is not correct: light status should change after notification
   //  (also for onLightPointRequestOff)
   m_guiInterface.showAsTurnedOn( ownAddress);
}

void OwnEngine::onLightPointRequestOff(int ownAddress)
{
   QString message = m_ownFormatter.lightOff(ownAddress);
   m_ownLink.triggerSendMessage( message);

   m_guiInterface.showAsTurnedOff( ownAddress);
}
