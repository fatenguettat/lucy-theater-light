#include "PlantInfo.h"


PlantInfo::PlantInfo( const QString &plantFilePath,
                      const QString &plantLabel,
                      QList<const LightPoint *> lightPoints,
                      QString gatewayIpAddress,
                      int gatewayPort):
   m_plantFilePath(plantFilePath),
   m_plantLabel(plantLabel),
   m_lightPoints(lightPoints),
   m_gatewayIpAddress(gatewayIpAddress),
   m_gatewayPort(gatewayPort)
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

QString PlantInfo::getGatewayIpAddress() const
{
   return m_gatewayIpAddress;
}

int PlantInfo::getGatewayIpPort() const
{
   return m_gatewayPort;
}


