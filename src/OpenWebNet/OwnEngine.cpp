#include "OwnEngine.h"

#include "GuiInterface_IF.h"
#include "NetworkUi_IF.h"
#include "OwnLink.h"
#include "OwnFormatter.h"
#include "LightPoint.h"


OwnEngine::OwnEngine( NetworkUi_IF & networkInterface,
                      OwnLink & ownLink, OwnFormatter & ownformatter,
                      QObject *parent) :
   QObject(parent),
   m_networkInterface(networkInterface),
   m_ownLink(ownLink),
   m_ownFormatter(ownformatter),
   m_pendingAction(ACTION_NONE),
   m_pendingActionWhere(-1),
   m_pendingActionLevel(own::LEVEL_100)
{
   connect( &m_ownLink, SIGNAL(sequenceComplete()),
            this, SLOT(onSequenceComplete()));
}

void OwnEngine::addLightPoint(const LightPoint & point)
{
   m_lightTable << &point;
   emit lightPointAdded( &point);
}


void OwnEngine::lightPointRequestOn(int ownAddress)
{
   m_pendingAction = ACTION_LIGHT_ON;
   m_pendingActionWhere = ownAddress;

   QString message = m_ownFormatter.lightOn(ownAddress);
   m_ownLink.triggerSendMessage( message);

   if (ownAddress != own::GLOBAL_WHERE)
   {
      emit lightOnRequestStarted( ownAddress);
   }
   else
   {
      foreach( const LightPoint *point, m_lightTable)
      {
         emit lightOnRequestStarted( point->ownAddress());
      }
   }
}

void OwnEngine::lightPointRequestOff(int ownAddress)
{
   m_pendingAction = ACTION_LIGHT_OFF;
   m_pendingActionWhere = ownAddress;

   QString message = m_ownFormatter.lightOff(ownAddress);
   m_ownLink.triggerSendMessage( message);

   if (ownAddress != own::GLOBAL_WHERE)
   {
      emit lightOffRequestStarted( ownAddress);
   }
   else
   {
      foreach( const LightPoint *point, m_lightTable)
      {
         emit lightOffRequestStarted( point->ownAddress());
      }
   }
}

void OwnEngine::lightPointRequestLevel(int ownAddress, own::LIGHT_LEVEL level)
{
   m_pendingAction = ACTION_SET_LEVEL;
   m_pendingActionWhere = ownAddress;
   m_pendingActionLevel = level;

   QString message = m_ownFormatter.lightLevel(ownAddress, level);
   m_ownLink.triggerSendMessage( message);

   if (ownAddress != own::GLOBAL_WHERE)
   {
      emit lightLevelRequestStarted( ownAddress);
   }
   else
   {
      foreach( const LightPoint *point, m_lightTable)
      {
         emit lightLevelRequestStarted( point->ownAddress());
      }
   }
}

void OwnEngine::lightPointProbeStatus(int ownAddress)
{
   QString message = m_ownFormatter.askForLightStatus( ownAddress);
   m_ownLink.triggerSendMessage( message);

   emit lightStatusRequestStarted( ownAddress);
}

void OwnEngine::clearPlant()
{
   /* delete all light points */
   m_lightTable.clear();
   emit plantCleared();
}

void OwnEngine::onSequenceComplete()
{
   switch (m_pendingAction)
   {
   case ACTION_LIGHT_ON:
      emit lightOnAcked( m_pendingActionWhere);
      break;

   case ACTION_LIGHT_OFF:
      emit lightOffAcked( m_pendingActionWhere);
      break;

   case ACTION_SET_LEVEL:
      emit lightLevelAcked( m_pendingActionWhere, m_pendingActionLevel);
      break;

   default:
   case ACTION_NONE:
      break;
   }

   m_pendingAction = ACTION_NONE;
   m_pendingActionWhere = -1;
}

