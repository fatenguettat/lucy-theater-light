#ifndef OWNENGINE_H
#define OWNENGINE_H

#include <QObject>
#include <QList>

#include "OwnConstants.h"


class NetworkUi_IF;
class OwnLink;
class OwnFormatter;
class LightPoint;


class OwnEngine : public QObject
{
   Q_OBJECT
public:
   explicit OwnEngine( NetworkUi_IF & networkInterface,
                       OwnLink & ownLink, OwnFormatter & ownformatter,
                       QObject *parent = 0);
   ~OwnEngine() {}

   void addLightPoint( const LightPoint & point);

public:
   /**
    * @brief trigger a request to turn a light on
    * @param ownAddress
    */
   void lightPointRequestOn( int ownAddress);

   /**
    * @brief trigger a request to turn a light off
    * @param ownAddress
    */
   void lightPointRequestOff( int ownAddress);

   /**
    * @brief trigger a request to set the level of a light
    * @param ownAddress
    * @param level (see type definition for details)
    */
   void lightPointRequestLevel( int ownAddress, own::LIGHT_LEVEL level);

   /**
    * @brief trigger a request for a light status
    */
   void lightPointProbeStatus(int ownAddress);

   /**
    * @brief to be called when a new plant must be loaded,
    *  to clear current data
    */
   void clearPlant();

signals:
   /**
    * @brief notification of a new light point
    * @param point describes light point
    */
   void lightPointAdded( const LightPoint * point );

   /** notification that request to turn on has been triggered */
   void lightOnRequestStarted( int ownAddress);

   /** notification that sequence to turn on has completed succesfully */
   void lightOnAcked( int ownAddress);

   /** notification that request to turn off has been triggered */
   void lightOffRequestStarted( int ownAddress);

   /** notification that sequence to turn off has completed succesfully */
   void lightOffAcked( int ownAddress);

   /** notification that request to change level has been triggered */
   void lightLevelRequestStarted( int ownAddress);

   /** notification that sequence to change level has completed succesfully */
   void lightLevelAcked( int ownAddress, own::LIGHT_LEVEL level);

   /** notification that request to turn off has been triggered */
   void lightStatusRequestStarted( int ownAddress);

   /** notification that all current data about plant are outdated */
   void plantCleared();

private:
   typedef enum
   {
      ACTION_NONE = 0,
      ACTION_LIGHT_ON,
      ACTION_LIGHT_OFF,
      ACTION_SET_LEVEL
   } Action;

private:
   NetworkUi_IF  & m_networkInterface;
   OwnLink  & m_ownLink;
   OwnFormatter  & m_ownFormatter;

   QList<const LightPoint *> m_lightTable;
   Action m_pendingAction;
   int m_pendingActionWhere;
   own::LIGHT_LEVEL m_pendingActionLevel;

private:
   static const int OWN_GLOBAL_ADDRESS=0;

private slots:
   void onSequenceComplete();
};

#endif // OWNENGINE_H