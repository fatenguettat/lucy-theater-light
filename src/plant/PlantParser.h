#ifndef PLANTPARSER_H
#define PLANTPARSER_H

#include <QStringList>
#include <QMap>
#include "LightPoint.h"

class PlantInfo;
class QTextStream;
class LightGroup;
class Scenario;


class PlantParser
{
public:
   PlantParser();
   ~PlantParser();

   /**
    * @brief read the \p content of a text stream and extrapolates info
    *    out of that.
    * @param content is a text stream, genrally (but not necessarily) got
    *    from a file.
    *
    * @return a reference to a structure with parsed data.
    */
   const PlantInfo * parse( QTextStream & content);

   /**
    * @return a list of errors found during last parse operation. This function
    *    is usually called after \a parse function.
    * Every call to \a parse resets the errors related to previous call.
    */
   QStringList & getErrors();

   /* constants */
private:
   static const char TAG_OPEN_PlantFile[];
   static const char TAG_CLOSE_PlantFile[];
   static const char TAG_OPEN_PlantLabel[];
   static const char TAG_CLOSE_PlantLabel[];
   static const char TAG_OPEN_LightPoints[];
   static const char TAG_CLOSE_LightPoints[];
   static const char TAG_OPEN_LightGroups[];
   static const char TAG_CLOSE_LightGroups[];
   static const char TAG_OPEN_Scenarios[];
   static const char TAG_CLOSE_Scenarios[];
   static const char TAG_OPEN_GatewayAddress[];
   static const char TAG_CLOSE_GatewayAddress[];

private:
   /* output containers */
   QStringList m_errorList;
   PlantInfo * m_plantInfo;

   /* used to keep track of which line has an error */
   int m_currentLineNumber;

   /** stream actually being parsed */
   QTextStream * m_content;

   /* partial parsed data */
   QString m_plantFilePath;
   QString m_plantLabel;
   QList<const LightPoint *> m_lightPoints;
   QList<const LightGroup *> m_lightGroups;
   QList<const Scenario *> m_scenarios;
   QString m_gatewayIpAddress;
   int m_gatewayPort;

private:
   void clearParseData();
   void readPlantFilePath();
   void readPlantLabel();
   void readLightPoints();
   void readLightGroups();
   void readScenarios();
   void readGatewayAddress();
   void createLightPoint( const QString & line);
   void createLightGroup( const QString & line);
   void createScenario( const QString & line);
   const LightPoint * parseLightPointLine( const QString & line);
   const LightGroup * parseLightGroupLine( const QString & line);
   const Scenario * parseScenarioLine( const QString & line);
   void extractLightInfo( const QStringList & argumentList, QPointF *position, int *ownAddress);
   void createInfoStructure();
   void extractGatewayArguments(QStringList arguments);
   void checkGatewayIpAddress();
   void checkGatewayClosingTag(const QString & line);
   QString readNextLine();
};

#endif // PLANTPARSER_H
