#ifndef PLANTINFO_H
#define PLANTINFO_H

#include <QList>
#include <QString>

#include "LightPoint.h"
class LightGroup;
class Scenario;

/**
 * @brief The PlantInfo class is a structured class that holds info about a
 *  plant configuration. Data are passed to constructor and can not be modified.
 */
class PlantInfo
{
public:

   /**
    * @brief build object with all fields
    * @param plantFilePath is the full path of layout image
    * @param lightPoints is a set of lights (with location and address)
    * @param lightGroups is a set of lights commanded together
    * @param scenarios is a set of scenarios, (each is a set of where-what pairs)
    * @param gatewayIpAddress refers to OpenWebNet server IP address
    * @param gatewayPort refers to OpenWebNet server IP port
    */
   PlantInfo( const QString & plantFilePath,
              const QString & plantLabel,
              QList<const LightPoint *> lightPoints,
              QList<const LightGroup *> lightGroups,
              QList<const Scenario *> scenarios,
              QString gatewayIpAddress,
              int gatewayPort);

   ~PlantInfo();

   /**
    * @return full path of image file of the plant, read from last call to \a parse
    */
   QString getPlantFilePath() const;

   /**
    * @return a string that identifies the name of the plant.
    *   Usually includes a version number.
    */
   QString getPlantLabel() const;

   /**
    * @return the list of light points read in the last call to \a parse
    */
   QList<const LightPoint *> getLightPoints() const;

   /**
    * @return the list of light groups read in the last call to \a parse
    */
   QList<const LightGroup *> getLightGroups() const;

   /**
    * @return the list of scenarios read in the last call to \a parse
    */
   QList<const Scenario *> getScenarios() const;

   /**
    * @return IP address for OWN gateway read on last call to \a parse
    */
   QString getGatewayIpAddress() const;

   /**
    * @return IP port for OWN gateway read on last call to \a parse
    */
   int getGatewayIpPort() const;

private:
   QString m_plantFilePath;
   QString m_plantLabel;
   QList<const LightPoint *> m_lightPoints;
   QList<const LightGroup *> m_lightGroups;
   QList<const Scenario *> m_scenarios;
   QString m_gatewayIpAddress;
   int m_gatewayPort;
};

#endif // PLANTINFO_H
