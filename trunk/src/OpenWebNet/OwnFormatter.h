#ifndef OWNFORMATTER_H
#define OWNFORMATTER_H

#include <QString>
#include <QMap>

#include "OwnConstants.h"

class OwnFormatter
{
public:
   OwnFormatter();

   /**
    * @return the string to turn on a fixed light point
    * @param ownAddress is open web net address in range 11-99,
    *   or 0 for global
    */
   QString lightOn(int ownAddress);

   /**
    * @return the string to turn off a fixed light point
    * @param ownAddress is open web net address in range 11-99,
    *   or 0 for global
    */
   QString lightOff(int ownAddress);

   /**
    * @return open web net string to set the level of a light point
    * @param ownAddress is in range 11-99, or 0 for global
    * @param level is ten based, from 20% to 100%
    */
   QString lightLevel( int ownAddress, own::LIGHT_LEVEL level);

   /**
    * @return open web net string to set the level of a light point with a
    *   transition as slow as possible.
    * @param ownAddress is in range 11-99, or 0 for global
    * @param level is ten based, from 20% to 100%
    */
   QString lightLevelSlow( int ownAddress, own::LIGHT_LEVEL level);

   /**
    * @return open web net string to set the level of a group of lights
    * @param group is in range 1-9
    * @param level is ten based, from 20% to 100%
    */
   QString lightLevelGroup( int group, own::LIGHT_LEVEL level);

   /**
    * @return open web net string to set the level of a group of lights,
    *   with transition as slow as possible.
    * @param group is in range 1-9
    * @param level is ten based, from 20% to 100%
    */
   QString lightLevelGroupSlow( int group, own::LIGHT_LEVEL level);

   /**
    * @brief request the status for a light point
    * @param ownAddress is in range 11-99, or 0 for global
    * @return
    */
   QString askForLightStatus( int ownAddress);

private:
   /**
    * @brief map enumerated value for light level to OWN representation
    */
   static const QMap<own::LIGHT_LEVEL, int> m_LevelLookupTable;

private:
   /** initialization of \a m_LevelLookupTable */
   static QMap<own::LIGHT_LEVEL, int> initLevelTable();
};

#endif // OWNFORMATTER_H
