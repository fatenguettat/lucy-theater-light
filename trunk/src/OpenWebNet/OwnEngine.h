#ifndef OWNENGINE_H
#define OWNENGINE_H

#include <QObject>
#include <QHash>

#include "OwnTypes.h"


class NetworkUi_IF;
class OwnLink;
class OwnFormatter;
class LightPoint;
class LightGroup;
class Scenario;


class OwnEngine : public QObject
{
   Q_OBJECT
public:
   explicit OwnEngine( NetworkUi_IF & networkInterface,
                       OwnLink & ownLink, OwnFormatter & ownformatter,
                       QObject *parent = 0);
   ~OwnEngine() {}

   void addLightPoint( const LightPoint & point);
   void addLightGroup(const LightGroup & group);
   void addScenario(const Scenario & scenario);

public:
   /**
    * @brief trigger a request to turn a light on
    * @param ownAddress can be a lightpoint or a group
    */
   void lightRequestOn( const own::Where & ownAddress);

   /**
    * @brief trigger a request to turn a light off
    * @param ownAddress can be a lightpoint or a group
    */
   void lightRequestOff(const own::Where & ownAddress);

   /**
    * @brief trigger a request to set the level of a light
    * @param ownAddress can be a lightpoint or a group
    * @param level (see type definition for details)
    */
   void lightRequestLevel(const own::Where & ownAddress, own::LIGHT_LEVEL level);

   /**
    * @brief trigger a request to start a scenario.
    * @param description identifies the scenario frm its description
    */
   void scenarioRequest(const QString & description);

   /**
    * @brief trigger a request for a light status
    * @param ownAddress can be a lightpoint or a group
    */
   void lightProbeStatus( const own::Where & ownAddress);

   /**
    * @brief to be called when a new plant must be loaded,
    *  to clear current data
    */
   void clearPlant();

   /**
    * @return the description for a lightpoint, given it'a 'WHERE' param
    * @param ownAddress can be a lightpoint or a group
    */
   QString getLightDescription( const own::Where & ownAddress);

   QString getLightDescriptionForPoint(const own::Where &ownAddress);
signals:
   /**
    * @brief notification of a new light point loaded in plant
    * @param point describes light point
    */
   void lightPointAdded( const LightPoint * point );

   /**
    * @brief notification of a new light group loaded in plant
    * @param group describes the group
    */
   void lightGroupAdded(const LightGroup * group);

   /**
    * @brief notification of a new scenario loaded in plant
    * @param scenario describes a set of light and relevant values
    */
   void scenarioAdded(const Scenario * scenario);

   /** notification that request to turn on has been triggered */
   void lightOnRequestStarted( const own::Where & ownAddress) const;

   /** notification that sequence to turn on has completed succesfully */
   void lightOnAcked( const own::Where &  ownAddress) const;

   /** notification that request to turn off has been triggered */
   void lightOffRequestStarted( const own::Where &  ownAddress) const;

   /** notification that sequence to turn off has completed succesfully */
   void lightOffAcked( const own::Where &  ownAddress) const;

   /** notification that request to change level has been triggered */
   void lightLevelRequestStarted( const own::Where &  ownAddress) const;

   /** notification that sequence to change level has completed succesfully */
   void lightLevelAcked( const own::Where &  ownAddress, own::LIGHT_LEVEL level) const;

   /** notification that request to turn off has been triggered */
   void lightStatusRequestStarted( const own::Where &  ownAddress) const;

   /** notification that all current data about plant are outdated */
   void plantCleared();

private:
   typedef enum
   {
      ACTION_NONE = 0,
      ACTION_LIGHT_ON,
      ACTION_LIGHT_OFF,
      ACTION_SET_LEVEL,
      ACTION_SCENARIO
   } Action;

private:
   NetworkUi_IF  & m_networkInterface;
   OwnLink  & m_ownLink;
   OwnFormatter  & m_ownFormatter;

   QHash<own::Where, const LightPoint *> m_lightPointTable;
   QHash<own::Where, const LightGroup *> m_lightGroupTable;
   /* lookup scenarios by description */
   QHash<QString, const Scenario *> m_scenarioTable;
   Action m_pendingAction;
   own::Where m_pendingActionWhere;
   own::LIGHT_LEVEL m_pendingActionLevel;
   const Scenario *m_pendingScenario;

private:
   static const int OWN_GLOBAL_ADDRESS=0;

private slots:
   void onSequenceComplete();

private:
   QString getLightDescriptionForGroup(const own::Where &ownAddress);
   void onCompletedLightOn();
   void onCompletedLightOff();
   void onCompletedLightLevel();
   void notifyActionAcked( Action action);
   void notifyActionAckedToWhere( Action action, own::Where where);
   void notifyScenarioAcked();
   Action actionForWhat( const own::What what);
};

#endif // OWNENGINE_H
