#include "OwnFormatter.h"

/** const values of level to integer-identifier table */
const QHash<own::LIGHT_LEVEL, int> OwnFormatter::m_LevelLookupTable = initLevelTable();


OwnFormatter::OwnFormatter()
{
}

QString OwnFormatter::lightOn(const own::Where & ownAddress)
{
   return QString("*1*1*%1##").arg( ownAddress);
}

QString OwnFormatter::lightOff( const own::Where ownAddress)
{
   return QString("*1*0*%1##").arg( ownAddress);
}

QString OwnFormatter::lightLevel( const own::Where & ownAddress, own::LIGHT_LEVEL level)
{
   return QString("*1*%1*%2##").
         arg( m_LevelLookupTable[level]).
         arg(ownAddress);
}

QString OwnFormatter::lightLevelSlow(const own::Where & ownAddress, own::LIGHT_LEVEL level)
{
   return QString("*1*%1#3*%2##").
         arg( m_LevelLookupTable[level]).
         arg(ownAddress);
}

QString OwnFormatter::lightGenericCommand(const own::Where &ownAddress, const own::What &what)
{
   return QString("*1*%1*%2##").
         arg(what).
         arg(ownAddress);
}


QString OwnFormatter::askForLightStatus( const own::Where & ownAddress)
{
   return QString("*#1*%1##").arg( ownAddress);
}


QHash<own::LIGHT_LEVEL, int> OwnFormatter::initLevelTable()
{
   QHash<own::LIGHT_LEVEL, int> levelTable;

   levelTable.insert( own::LEVEL_20, 2);
   levelTable.insert( own::LEVEL_30, 3);
   levelTable.insert( own::LEVEL_40, 4);
   levelTable.insert( own::LEVEL_50, 5);
   levelTable.insert( own::LEVEL_60, 6);
   levelTable.insert( own::LEVEL_70, 7);
   levelTable.insert( own::LEVEL_80, 8);
   levelTable.insert( own::LEVEL_90, 9);
   levelTable.insert( own::LEVEL_100, 10);

   return levelTable;
}
