#ifndef OWNFORMATTER_H
#define OWNFORMATTER_H

#include <QString>
#include <QMap>

class OwnFormatter
{
public:

   typedef enum
   {
      LEVEL_20 = 0,
      LEVEL_30,
      LEVEL_40,
      LEVEL_50,
      LEVEL_60,
      LEVEL_70,
      LEVEL_80,
      LEVEL_90,
      LEVEL_100

   } LIGHT_LEVEL;

public:
   OwnFormatter();

   /**
    * @return the string to turn on a fixed light point
    * @param ownAddress is open web net address in range 11-99
    */
   QString lightOn(int ownAddress);

   /**
    * @return the string to turn off a fixed light point
    * @param ownAddress is open web net address in range 11-99
    */
   QString lightOff(int ownAddress);

   /**
    * @return open web net string to set the level of a light point
    * @param ownAddress is in range 11-99
    * @param level is ten based, from 20% to 100%
    */
   QString lightLevel( int ownAddress, LIGHT_LEVEL level);

   /**
    * @return open web net string to set the level of a light point with a
    *   transition as slow as possible.
    * @param ownAddress is in range 11-99
    * @param level is ten based, from 20% to 100%
    */
   QString lightLevelSlow( int ownAddress, LIGHT_LEVEL level);

   /**
    * @return open web net string to set the level of a group of lights
    * @param group is in range 1-9
    * @param level is ten based, from 20% to 100%
    */
   QString lightLevelGroup( int group, LIGHT_LEVEL level);

   /**
    * @return open web net string to set the level of a group of lights,
    *   with transition as slow as possible.
    * @param group is in range 1-9
    * @param level is ten based, from 20% to 100%
    */
   QString lightLevelGroupSlow( int group, LIGHT_LEVEL level);

private:
   /**
    * @brief map enumerated value for light level to OWN representation
    */
   static const QMap<LIGHT_LEVEL, int> m_LevelLookupTable;

   /** initialization of \a m_LevelLookupTable */
   static QMap<LIGHT_LEVEL, int> initLevelTable();
};

#endif // OWNFORMATTER_H
