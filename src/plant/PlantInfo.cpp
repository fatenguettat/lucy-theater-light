#include "PlantInfo.h"


PlantInfo::PlantInfo( const QString &plantFilePath,
                      const QString &plantLabel,
                      QList<const LightPoint *> lightPoints,
                      QList<const LightGroup *> lightGroups,
                      QList<const Scenario *> scenarios,
                      QString gatewayIpAddress,
                      int gatewayPort):
   m_plantFilePath(plantFilePath),
   m_plantLabel(plantLabel),
   m_lightPoints(lightPoints),
   m_lightGroups(lightGroups),
   m_scenarios(scenarios),
   m_gatewayIpAddress(gatewayIpAddress),
   m_gatewayPort(gatewayPort)
{
}

PlantInfo::~PlantInfo()
{
}

QString PlantInfo::getPlantFilePath() const
{
   return m_plantFilePath;
}

QString PlantInfo::getPlantLabel() const
{
   return m_plantLabel;
}

QList<const LightPoint *> PlantInfo::getLightPoints() const
{
   return m_lightPoints;
}

QList<const LightGroup *> PlantInfo::getLightGroups() const
{
   return m_lightGroups;
}

QList<const Scenario *> PlantInfo::getScenarios() const
{
   return m_scenarios;
}

QString PlantInfo::getGatewayIpAddress() const
{
   return m_gatewayIpAddress;
}

int PlantInfo::getGatewayIpPort() const
{
   return m_gatewayPort;
}


