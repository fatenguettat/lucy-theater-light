#include "PlantParser.h"

#include <QStringList>
#include <QTextStream>
#include <QFileInfo>

#include "PlantInfo.h"


const char PlantParser::TAG_OPEN_PlantFile[] = "<!--PLANT_IMAGE>";
const char PlantParser::TAG_CLOSE_PlantFile[] = "<PLANT_IMAGE-->";
const char PlantParser::TAG_OPEN_LightPoints[] = "<!--LIGHT_POINTS>";
const char PlantParser::TAG_CLOSE_LightPoints[] = "<LIGHT_POINTS-->";
const char PlantParser::TAG_OPEN_GatewayAddress[] = "<!--MH200N_ADDRESS>";
const char PlantParser::TAG_CLOSE_GatewayAddress[] = "<MH200N_ADDRESS-->";


PlantParser::PlantParser() :
   m_currentLineNumber(0),
   m_plantInfo(NULL),
   m_content(NULL),
   m_gatewayPort(0)
{
}

const PlantInfo * PlantParser::parse(QTextStream & content)
{
   m_errorList.clear();
   m_currentLineNumber = 0;

   m_content = &content;

   while (! m_content->atEnd())
   {
      QString line = readNextLine();

      if (line == QString(TAG_OPEN_PlantFile))
      {
         readPlantFilePath();
      }
      else if (line == QString(TAG_OPEN_LightPoints))
      {
         readLightPoints();
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

void PlantParser::createInfoStructure()
{
   // TODO is there an alternative to this?
   if (m_plantInfo != NULL)
   {
      delete m_plantInfo;
      m_plantInfo = NULL;
   }

   m_plantInfo = new PlantInfo( m_plantFilePath, m_lightPoints,
                                m_gatewayIpAddress, m_gatewayPort);
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
      m_errorList << QObject::tr("line %1: Missing tag <PLANT_IMAGE-->").arg(m_currentLineNumber);
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
      m_lightPoints << parseLightPoint(line);
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
const LightPoint * PlantParser::parseLightPoint(const QString &line)
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

   return new LightPoint( description, pos, ownAddr);
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
