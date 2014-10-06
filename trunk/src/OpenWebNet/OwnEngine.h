#ifndef OWNENGINE_H
#define OWNENGINE_H

#include <QObject>
#include <QList>

#include "OwnTypes.h"


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
   void lightPointRequestOn( const own::Where & ownAddress);

   /**
    * @brief trigger a request to turn a light off
    * @param ownAddress
    */
   void lightPointRequestOff(const own::Where & ownAddress);

   /**
    * @brief trigger a request to set the level of a light
    * @param ownAddress
    * @param level (see type definition for details)
    */
   void lightPointRequestLevel(const own::Where & ownAddress, own::LIGHT_LEVEL level);

   /**
    * @brief trigger a request for a light status
    */
   void lightPointProbeStatus( const own::Where & ownAddress);

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
      ACTION_SET_LEVEL
   } Action;

private:
   NetworkUi_IF  & m_networkInterface;
   OwnLink  & m_ownLink;
   OwnFormatter  & m_ownFormatter;

   QList<const LightPoint *> m_lightTable;
   Action m_pendingAction;
   own::Where m_pendingActionWhere;
   own::LIGHT_LEVEL m_pendingActionLevel;

private:
   static const int OWN_GLOBAL_ADDRESS=0;

private slots:
   void onSequenceComplete();
};

#endif // OWNENGINE_H
