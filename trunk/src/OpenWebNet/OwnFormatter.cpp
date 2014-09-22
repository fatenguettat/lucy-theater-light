#include "OwnFormatter.h"

const QMap<OwnFormatter::LIGHT_LEVEL, int> OwnFormatter::m_LevelLookupTable = initLevelTable();

OwnFormatter::OwnFormatter()
{
}

QString OwnFormatter::lightOn(int ownAddress)
{
   return QString("*1*1*%1##").arg( ownAddress);
}

QString OwnFormatter::lightOff(int ownAddress)
{
   return QString("*1*0*%1##").arg( ownAddress);
}

QString OwnFormatter::lightLevel(int ownAddress, OwnFormatter::LIGHT_LEVEL level)
{
   return QString("*1*%1*%2##").
         arg( m_LevelLookupTable[level]).
         arg(ownAddress);
}

QString OwnFormatter::lightLevelSlow(int ownAddress, OwnFormatter::LIGHT_LEVEL level)
{
   return QString("*1*%1#3*%2##").
         arg( m_LevelLookupTable[level]).
         arg(ownAddress);
}

QString OwnFormatter::lightLevelGroup(int group, OwnFormatter::LIGHT_LEVEL level)
{
   return QString("*1*%1*#%2##").
         arg( m_LevelLookupTable[level]).
         arg(group);
}

QString OwnFormatter::lightLevelGroupSlow(int group, OwnFormatter::LIGHT_LEVEL level)
{
   return QString("*1*%1#3*#%2##").
         arg( m_LevelLookupTable[level]).
         arg(group);
}

QMap<OwnFormatter::LIGHT_LEVEL, int> OwnFormatter::initLevelTable()
{
   QMap<LIGHT_LEVEL, int> levelTable;

   levelTable.insert( LEVEL_20, 2);
   levelTable.insert( LEVEL_30, 3);
   levelTable.insert( LEVEL_40, 4);
   levelTable.insert( LEVEL_50, 5);
   levelTable.insert( LEVEL_60, 6);
   levelTable.insert( LEVEL_70, 7);
   levelTable.insert( LEVEL_80, 8);
   levelTable.insert( LEVEL_90, 9);
   levelTable.insert( LEVEL_100, 10);

   return levelTable;
}
