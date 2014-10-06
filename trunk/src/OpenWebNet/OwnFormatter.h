#ifndef OWNFORMATTER_H
#define OWNFORMATTER_H

#include <QString>
#include <QHash>

#include "OwnTypes.h"

class OwnFormatter
{
public:
   OwnFormatter();

   /**
    * @return the string to turn on a fixed light point
    * @param ownAddress is open web net address in range 11-99,
    *   or 0 for global.
    *   Group notation (#g) is supported
    */
   QString lightOn( const own::Where & ownAddress);

   /**
    * @return the string to turn off a fixed light point
    * @param ownAddress is open web net address in range 11-99,
    *   or 0 for global
    */
   QString lightOff( const own::Where ownAddress);

   /**
    * @return open web net string to set the level of a light point
    * @param ownAddress is in range 11-99, or 0 for global.
    *   Group notation (#g) is supported
    * @param level is ten based, from 20% to 100%
    */
   QString lightLevel(const own::Where & ownAddress, own::LIGHT_LEVEL level);

   /**
    * @return open web net string to set the level of a light point with a
    *   transition as slow as possible.
    * @param ownAddress is in range 11-99, or 0 for global
    * @param level is ten based, from 20% to 100%
    */
   QString lightLevelSlow( const own::Where & ownAddress, own::LIGHT_LEVEL level);

   /**
    * @brief request the status for a light point
    * @param ownAddress is in range 11-99, or 0 for global
    * @return
    */
   QString askForLightStatus(const own::Where & ownAddress);

private:
   /**
    * @brief map enumerated value for light level to OWN representation
    */
   static const QHash<own::LIGHT_LEVEL, int> m_LevelLookupTable;

private:
   /** initialization of \a m_LevelLookupTable */
   static QHash<own::LIGHT_LEVEL, int> initLevelTable();
};

#endif // OWNFORMATTER_H
