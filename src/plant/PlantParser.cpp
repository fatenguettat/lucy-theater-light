#include "PlantParser.h"

#include <QStringList>
#include <QTextStream>
#include <QFileInfo>
#include <QRegExp>

#include "PlantInfo.h"
#include "LightGroup.h"
#include "Scenario.h"

// TODO this file has grown rather big. Consider subclasses.

const char PlantParser::TAG_OPEN_PlantFile[] = "<!--PLANT_IMAGE>";
const char PlantParser::TAG_CLOSE_PlantFile[] = "<PLANT_IMAGE-->";
const char PlantParser::TAG_OPEN_PlantLabel[] = "<!--PLANT_NAME>";
const char PlantParser::TAG_CLOSE_PlantLabel[] = "<PLANT_NAME-->";
const char PlantParser::TAG_OPEN_LightPoints[] = "<!--LIGHT_POINTS>";
const char PlantParser::TAG_CLOSE_LightPoints[] = "<LIGHT_POINTS-->";
const char PlantParser::TAG_OPEN_LightGroups[] = "<!--LIGHT_GROUPS>";
const char PlantParser::TAG_CLOSE_LightGroups[] = "<LIGHT_GROUPS-->";
const char PlantParser::TAG_OPEN_Scenarios[] = "<!--SCENARIOS>";
const char PlantParser::TAG_CLOSE_Scenarios[] = "<SCENARIOS-->";
const char PlantParser::TAG_OPEN_GatewayAddress[] = "<!--MH200N_ADDRESS>";
const char PlantParser::TAG_CLOSE_GatewayAddress[] = "<MH200N_ADDRESS-->";



PlantParser::PlantParser() :
   m_plantInfo(NULL),
   m_currentLineNumber(0),
   m_content(NULL),
   m_gatewayPort(0)
{
}

PlantParser::~PlantParser()
{
   if (m_plantInfo != NULL)
   {
      delete m_plantInfo;
      m_plantInfo = NULL;
   }
}

const PlantInfo * PlantParser::parse(QTextStream & content)
{
   clearParseData();

   m_content = &content;

   while (! m_content->atEnd())
   {
      /* if-else cascade is ugly, but nothing better has proved to work */
      QString line = readNextLine();

      if (line == QString(TAG_OPEN_PlantFile))
      {
         readPlantFilePath();
      }
      else if (line == QString(TAG_OPEN_PlantLabel))
      {
         readPlantLabel();
      }
      else if (line == QString(TAG_OPEN_LightPoints))
      {
         readLightPoints();
      }
      else if (line == QString(TAG_OPEN_LightGroups))
      {
         readLightGroups();
      }
      else if (line == QString(TAG_OPEN_Scenarios))
      {
         readScenarios();
      }
      else if (line == QString(TAG_OPEN_GatewayAddress))
      {
         readGatewayAddress();
      }
   }

   /* create structure with newly parsed data */
   createInfoStructure();

   return m_plantInfo;
}

void PlantParser::clearParseData()
{
   m_errorList.clear();
   m_currentLineNumber = 0;

   for (int i=0; i < m_lightPoints.size(); i++)
   {
      delete m_lightPoints.at(i);
   }
   m_lightPoints.clear();

   for (int i=0; i < m_lightGroups.size(); i++)
   {
      delete m_lightGroups.at(i);
   }
   m_lightGroups.clear();

   for (int i=0; i < m_scenarios.size(); i++)
   {
      delete m_scenarios.at(i);
   }
   m_scenarios.clear();
}

void PlantParser::createInfoStructure()
{
   // TODO is there an alternative to this?
   if (m_plantInfo != NULL)
   {
      delete m_plantInfo;
      m_plantInfo = NULL;
   }

   m_plantInfo = new PlantInfo( m_plantFilePath, m_plantLabel,
                                m_lightPoints, m_lightGroups,
                                m_scenarios, m_gatewayIpAddress,
                                m_gatewayPort);
}

QStringList & PlantParser::getErrors()
{
   return m_errorList;
}

/* this function assumes to be called just after finding the opening
 * tag for plant image. File path should be in following line.
 * Following line should be enclosing tag: if it's not, this is notified
 * but plant file path remains valid
 */
void PlantParser::readPlantFilePath()
{
   m_plantFilePath = readNextLine();

   QFileInfo fileInfo( m_plantFilePath);
   if (! fileInfo.exists())
   {
      m_errorList << QObject::tr("line %1: File can't be found: %2").arg(m_currentLineNumber).arg(m_plantFilePath);
   }

   QString line = readNextLine();

   if (line != QString(TAG_CLOSE_PlantFile))
   {
      m_errorList << QObject::tr("line %1: missing closing tag for plant picture").arg(m_currentLineNumber);
   }
}

void PlantParser::readPlantLabel()
{
   m_plantLabel = readNextLine();

   QString line = readNextLine();

   if (line != QString(TAG_CLOSE_PlantLabel))
   {
      m_errorList << QObject::tr("line %1: missing closing tag for plant name").arg(m_currentLineNumber);
   }
}

/* this function assumes to be called just after finding the opening
 * tag for light points list. Following lines hold light descriptors,
 * one per line.
 * Lines are read until closing tag is found.
 */
void PlantParser::readLightPoints()
{
   bool endTagFound = false;

   while ((! m_content->atEnd()) && (! endTagFound))
   {
      QString line = readNextLine();

      if (line == QString(TAG_CLOSE_LightPoints))
      {
         /* end of light points */
         endTagFound = true;
      }
      else
      {
         /* this line should be a light point */
         createLightPoint( line);
      }
   }

   if (! endTagFound)
   {
      m_errorList << QObject::tr("line %1: missing closing tag for light points").arg(m_currentLineNumber);
   }
}


void PlantParser::createLightPoint(const QString &line)
{
   try
   {
      m_lightPoints << parseLightPointLine(line);
   }
   catch(QString & error)
   {
      /* 'line' has wrong syntax */
      m_errorList << QString( error + " [" + line + "]");
   }
}

/* read \p line and extract light point info.
 * Expected format:
 * "name" x y OWN_ADDR
 * Example:
 * "the name" 0.3 0.7 11
 */
const LightPoint * PlantParser::parseLightPointLine(const QString &line)
{
   QStringList lineFields, argumentList;
   lineFields = line.split(QChar('"'), QString::SkipEmptyParts);

   if (lineFields.length() < 2)
   {
      throw QObject::tr("line %1: Description or arguments missing").arg(m_currentLineNumber);
   }

   QString description = lineFields.at(0);
   argumentList = lineFields.at(1).split(QChar(' '), QString::SkipEmptyParts);

   if (argumentList.size() < 3)
   {
      throw QObject::tr("line %1: Not enough arguments for light point").arg(m_currentLineNumber);
   }

   QPointF pos(0,0);
   int ownAddr = 0;

   extractLightInfo( argumentList, &pos, &ownAddr);

   return new LightPoint( description, pos, QString("%1").arg(ownAddr));
}


void PlantParser::extractLightInfo(const QStringList & argumentList, QPointF *position, int *ownAddress)
{
   bool conversionOk = true;
   bool allConversionsOk = true;
   position->setX( argumentList.at(0).toDouble( &conversionOk) );
   allConversionsOk &= conversionOk;
   position->setY( argumentList.at(1).toDouble( &conversionOk) );
   allConversionsOk &= conversionOk;
   *ownAddress = argumentList.at(2).toInt( &conversionOk);
   allConversionsOk &= conversionOk;

   if (! allConversionsOk)
   {
      throw QObject::tr("One or more arguments are not valid numbers");
   }

   if ((position->x() < 0) || (position->x() > 1) || (position->y() < 0) || (position->y() > 1))
   {
      throw QObject::tr("line %1: Light coordinates are not in range (0,0) - (1,1)").arg(m_currentLineNumber);
   }
}

/* this function assumes to be called just after finding the opening
 * tag for light groups list. Following lines hold light group descriptors,
 * one per line.
 * Lines are read until closing tag is found.
 */
void PlantParser::readLightGroups()
{
   bool endTagFound = false;

   while ((! m_content->atEnd()) && (! endTagFound))
   {
      QString line = readNextLine();

      if (line == QString(TAG_CLOSE_LightGroups))
      {
         /* end of light points */
         endTagFound = true;
      }
      else
      {
         /* this line should be a light group */
         createLightGroup( line);
      }
   }

   if (! endTagFound)
   {
      m_errorList << QObject::tr("line %1: missing closing tag for light groups").arg(m_currentLineNumber);
   }
}


void PlantParser::createLightGroup( const QString & line)
{
   try
   {
      m_lightGroups << parseLightGroupLine(line);
   }
   catch(QString & error)
   {
      /* 'line' has wrong syntax */
      m_errorList << QString( error + " [" + line + "]");
   }
}


const LightGroup *PlantParser::parseLightGroupLine(const QString &line)
{
   QStringList lineFields, argumentList;
   lineFields = line.split(QChar('"'), QString::SkipEmptyParts);

   if (lineFields.length() < 2)
   {
      throw QObject::tr("line %1: Description or arguments missing").arg(m_currentLineNumber);
   }

   QString description = lineFields.at(0);
   argumentList = lineFields.at(1).split(QChar(' '), QString::SkipEmptyParts);

   if (argumentList.size() < 4)
   {
      /* bytes expected: x, y, #group, light1, ... */
      throw QObject::tr("line %1: Not enough arguments for light group").arg(m_currentLineNumber);
   }

   bool conversionOk = true;
   bool allConversionsOk = true;

   double posX = argumentList.at(0).toDouble(&conversionOk);
   allConversionsOk &= conversionOk;

   double posY = argumentList.at(1).toDouble(&conversionOk);
   allConversionsOk &= conversionOk;

   if (! allConversionsOk)
   {
      throw  QObject::tr("line %1: light group has invalid point").arg(m_currentLineNumber);
   }

   QString groupWhere = argumentList.at(2);
   if (! groupWhere.startsWith("#"))
   {
      throw QObject::tr("line %1: light group should start with '#'").arg(m_currentLineNumber);
   }

   LightPoint *base = new LightPoint( description, QPointF(posX, posY), groupWhere);

   return new LightGroup( *base, argumentList.mid(3));
}


void PlantParser::readScenarios()
{
   bool endTagFound = false;

   while ((! m_content->atEnd()) && (! endTagFound))
   {
      QString line = readNextLine();

      if (line == QString(TAG_CLOSE_Scenarios))
      {
         /* end of light points */
         endTagFound = true;
      }
      else
      {
         /* this line should be a scenario */
         createScenario( line);
      }
   }

   if (! endTagFound)
   {
      m_errorList << QObject::tr("line %1: missing closing tag for scenarios").arg(m_currentLineNumber);
   }
}


void PlantParser::createScenario(const QString &line)
{
   try
   {
      m_scenarios << parseScenarioLine(line);
   }
   catch(QString & error)
   {
      /* 'line' has wrong syntax */
      m_errorList << QString( error + " [" + line + "]");
   }
}


const Scenario *PlantParser::parseScenarioLine(const QString &line)
{
   QStringList lineFields, argumentList;
   lineFields = line.split(QChar('"'), QString::SkipEmptyParts);

   if (lineFields.length() < 2)
   {
      throw QObject::tr("line %1: Description or arguments missing").arg(m_currentLineNumber);
   }

   QString description = lineFields.at(0);
   /* each entry of 'argumentList' is in form WW,  */
   argumentList = lineFields.at(1).split(QChar(' '), QString::SkipEmptyParts);

   Scenario *scenario = new Scenario(description);

   QRegExp regExp("^(#?\\d+),(\\d+)");
   foreach (QString item, argumentList)
   {
      if (regExp.indexIn( item) != -1)
      {
         /* item mathces WHERE,WHAT format */
         scenario->addWhereWhatPair( regExp.cap(1), regExp.cap(2).toInt());
      }
      else
      {
         /* error in this line */
         delete scenario;
         throw QObject::tr("line %1: pair WHERE,WHAT has bad format").arg(m_currentLineNumber);
      }
   }

   return scenario;
}


void PlantParser::readGatewayAddress()
{
   QString line = readNextLine();

   QStringList arguments = line.split(' ', QString::SkipEmptyParts);

   try
   {
      extractGatewayArguments(arguments);
      checkGatewayIpAddress();

      /* closing tag should follow */
      line = readNextLine();
      checkGatewayClosingTag(line);
   }
   catch (QString & error)
   {
      /* 'gatewayLine' has wrong syntax */
      m_errorList << QString( error) + " [" + line + "]";
   }
}


void PlantParser::extractGatewayArguments(QStringList arguments)
{
   if (arguments.size() < 2)
   {
      throw QObject::tr("line %1: Not enough arguments for gateway address").arg(m_currentLineNumber);
   }

   bool convOk = false;
   m_gatewayIpAddress = arguments.at(0);
   m_gatewayPort = arguments.at(1).toInt(&convOk);

   if (! convOk)
   {
      throw QObject::tr("line %1: bad value for gateway port").arg(m_currentLineNumber);
   }
}


void PlantParser::checkGatewayIpAddress()
{
   bool convOk = false;

   QStringList ipFields = m_gatewayIpAddress.split('.');
   if (ipFields.size() != 4)
   {
      throw QObject::tr("line %1: Bad ip address").arg(m_currentLineNumber);
   }

   foreach (QString ipField, ipFields)
   {
      ipField.toInt( &convOk);

      if (! convOk)
      {
         throw QObject::tr("line %1: Bad ip address").arg(m_currentLineNumber);
      }
   }
}


void PlantParser::checkGatewayClosingTag( const QString & line)
{
   if (line != QString(TAG_CLOSE_GatewayAddress))
   {
      throw QObject::tr("line %1: Missing tag <MH200N_ADDRESS-->").arg(m_currentLineNumber);
   }
}


QString PlantParser::readNextLine()
{
   QString line = QString();

   if (! m_content->atEnd())
   {
      line = m_content->readLine();
      m_currentLineNumber++;
   }

   return line;
}
