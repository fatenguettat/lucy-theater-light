#include "OwnEngine.h"

#include "OwnConstants.h"
#include "GuiInterface_IF.h"
#include "NetworkUi_IF.h"
#include "OwnLink.h"
#include "OwnFormatter.h"
#include "LightPoint.h"
#include "LightGroup.h"
#include "testableAssert.h"



OwnEngine::OwnEngine( NetworkUi_IF & networkInterface,
                      OwnLink & ownLink, OwnFormatter & ownformatter,
                      QObject *parent) :
   QObject(parent),
   m_networkInterface(networkInterface),
   m_ownLink(ownLink),
   m_ownFormatter(ownformatter),
   m_pendingAction(ACTION_NONE),
   m_pendingActionWhere(""),
   m_pendingActionLevel(own::LEVEL_100)
{
   connect( &m_ownLink, SIGNAL(sequenceComplete()),
            this, SLOT(onSequenceComplete()));
}

void OwnEngine::addLightPoint(const LightPoint & point)
{
   m_lightPointTable.insert( point.ownAddress(), &point);
   emit lightPointAdded( &point);
}

void OwnEngine::addLightGroup(const LightGroup & group)
{
   m_lightGroupTable.insert( group.node().ownAddress(), &group);
   emit lightGroupAdded( &group);
}


void OwnEngine::lightRequestOn(const own::Where & ownAddress)
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
      QHashIterator<own::Where, const LightPoint *> iter(m_lightPointTable);

      while (iter.hasNext())
      {
          iter.next();
          emit lightOnRequestStarted( iter.key());
      }
   }
}

void OwnEngine::lightRequestOff(const own::Where & ownAddress)
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
      QHashIterator<own::Where, const LightPoint *> iter(m_lightPointTable);

      while (iter.hasNext())
      {
          iter.next();
          emit lightOffRequestStarted( iter.key());
      }
   }
}

void OwnEngine::lightRequestLevel(const own::Where & ownAddress, own::LIGHT_LEVEL level)
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
      QHashIterator<own::Where, const LightPoint *> iter(m_lightPointTable);

      while (iter.hasNext())
      {
          iter.next();
          emit lightLevelRequestStarted( iter.key());
      }
   }
}

void OwnEngine::lightProbeStatus(const own::Where & ownAddress)
{
   QString message = m_ownFormatter.askForLightStatus( ownAddress);
   m_ownLink.triggerSendMessage( message);

   emit lightStatusRequestStarted( ownAddress);
}

void OwnEngine::clearPlant()
{
   /* delete all light points */
   m_lightPointTable.clear();
   emit plantCleared();
}


QString OwnEngine::getLightDescription(const own::Where &ownAddress)
{
   QString description;

   /* select lightpoint or group */
   if (ownAddress.startsWith('#'))
   {
      /* group */
      description = getLightDescriptionForGroup( ownAddress);
   }
   else
   {
      /* single light point */
      description = getLightDescriptionForPoint( ownAddress);
   }

   return description;
}


QString OwnEngine::getLightDescriptionForGroup(const own::Where &ownAddress)
{
   QString description("");

   const LightGroup *group = m_lightGroupTable.value( ownAddress, NULL);
   if (group != NULL)
   {
      description = group->node().description();
   }

   return description;
}


QString OwnEngine::getLightDescriptionForPoint(const own::Where &ownAddress )
{
   QString description("");

   const LightPoint *point = m_lightPointTable.value( ownAddress, NULL);
   if (point != NULL)
   {
      description = point->description();
   }

   return description;
}


void OwnEngine::onSequenceComplete()
{
   switch (m_pendingAction)
   {
   case ACTION_LIGHT_ON:
      notifyActionAcked( ACTION_LIGHT_ON);
      break;

   case ACTION_LIGHT_OFF:
      notifyActionAcked( ACTION_LIGHT_OFF);
      break;

   case ACTION_SET_LEVEL:
      notifyActionAcked( ACTION_SET_LEVEL);
      break;

   default:
   case ACTION_NONE:
      break;
   }

   m_pendingAction = ACTION_NONE;
   m_pendingActionWhere.clear();
}


void OwnEngine::notifyActionAcked( OwnEngine::Action action)
{
   if (m_pendingActionWhere.startsWith('#'))
   {
      /* ack all lights of the group. Get full group from node 'where' */
      const LightGroup *group = m_lightGroupTable.value( m_pendingActionWhere);
      T_ASSERT( group != NULL);

      foreach (own::Where where, group->getLightPointList())
      {
         notifyActionAckedToWhere( action, where);
      }
   }
   else if (m_pendingActionWhere == own::GLOBAL_WHERE)
   {
      /* ack all lights of the system */
      QHashIterator<own::Where, const LightPoint *> iter(m_lightPointTable);

      while (iter.hasNext())
      {
          iter.next();
          emit notifyActionAckedToWhere( action, iter.key());
      }
   }
   else
   {
      /* simple lightpoint */
      notifyActionAckedToWhere( action, m_pendingActionWhere);
   }
}


void OwnEngine::notifyActionAckedToWhere( OwnEngine::Action action, own::Where where)
{
   switch (action)
   {
   case ACTION_LIGHT_ON:
      emit lightOnAcked( where);
      break;

   case ACTION_LIGHT_OFF:
      emit lightOffAcked( where);
      break;

   case ACTION_SET_LEVEL:
      emit lightLevelAcked( where, m_pendingActionLevel);
      break;

   default:
   case ACTION_NONE:
      break;
   }
}
