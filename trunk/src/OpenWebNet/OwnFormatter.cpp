#include "OwnFormatter.h"

const QMap<own::LIGHT_LEVEL, int> OwnFormatter::m_LevelLookupTable = initLevelTable();

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

QString OwnFormatter::lightLevel(int ownAddress, own::LIGHT_LEVEL level)
{
   return QString("*1*%1*%2##").
         arg( m_LevelLookupTable[level]).
         arg(ownAddress);
}

QString OwnFormatter::lightLevelSlow(int ownAddress, own::LIGHT_LEVEL level)
{
   return QString("*1*%1#3*%2##").
         arg( m_LevelLookupTable[level]).
         arg(ownAddress);
}

QString OwnFormatter::lightLevelGroup(int group, own::LIGHT_LEVEL level)
{
   return QString("*1*%1*#%2##").
         arg( m_LevelLookupTable[level]).
         arg(group);
}

QString OwnFormatter::lightLevelGroupSlow(int group, own::LIGHT_LEVEL level)
{
   return QString("*1*%1#3*#%2##").
         arg( m_LevelLookupTable[level]).
         arg(group);
}

QString OwnFormatter::askForLightStatus(int ownAddress)
{
   return QString("*#1*%1##").arg( ownAddress);
}


QMap<own::LIGHT_LEVEL, int> OwnFormatter::initLevelTable()
{
   QMap<own::LIGHT_LEVEL, int> levelTable;

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
