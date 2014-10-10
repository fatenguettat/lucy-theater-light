#include "tst_plantparser.h"

#include <QString>
#include <QtTest>
#include <QTextStream>

#include "PlantParser.h"
#include "PlantInfo.h"
#include "LightGroup.h"


PlantParserTest::PlantParserTest()
{
}

void PlantParserTest::init()
{
   m_plantParser = new PlantParser();
}

void PlantParserTest::cleanup()
{
   delete m_plantParser;
}

/**
 * @brief an empty file does not generate errors, but simply
 *    a void output.
 */
void PlantParserTest::testEmptyFile()
{
   QVERIFY( m_plantParser != NULL);

   const PlantInfo *info;

   QTextStream emptyStream("");
   info = m_plantParser->parse( emptyStream);

   QStringList errors = m_plantParser->getErrors();
   QCOMPARE( errors.size(), 0);
   QVERIFY( info->getPlantFilePath() == QString());
}

/**
 * @brief in this version, file format is recognised but not used
 */
void PlantParserTest::testFileFormat()
{
   QTextStream stream("<!--PLANT_FILE_FORMAT>\n"\
                      "0.1\n"\
                      "<PLANT_FILE_FORMAT-->\n");

   m_plantParser->parse( stream);

   QStringList errors = m_plantParser->getErrors();
   QCOMPARE( errors.size(), 0);
}

/**
 * @brief read plant file name in a correct file.
 */
void PlantParserTest::testPlantFileName_valid()
{
   QTextStream stream("<!--PLANT_IMAGE>\n"\
                      PROJECT_PATH"/res/plant.png\n"\
                      "<PLANT_IMAGE-->\n");

   const PlantInfo *info;
   info = m_plantParser->parse( stream);

   QCOMPARE( info->getPlantFilePath(), QString(PROJECT_PATH"/res/plant.png"));

   QStringList errors = m_plantParser->getErrors();
   QCOMPARE( errors.size(), 0);
}

void PlantParserTest::testPlantFileName_invalidPlantImage()
{
   QTextStream stream("<!--PLANT_IMAGE>\n"\
                      PROJECT_PATH"/res/NotExists.png\n"\
                      "<PLANT_IMAGE-->\n");

   const PlantInfo *info;
   info = m_plantParser->parse( stream);

   /* path is saved, but error is notified */
   QCOMPARE( info->getPlantFilePath(), QString(PROJECT_PATH "/res/NotExists.png"));

   QStringList errors = m_plantParser->getErrors();
   QCOMPARE( errors.size(), 1);
   QCOMPARE( errors.at(0), QString("line 2: File can't be found: "PROJECT_PATH"/res/NotExists.png"));
}

void PlantParserTest::testPlantFileName_MissingClosingTag()
{
   QTextStream stream("<!--PLANT_IMAGE>\n"\
                      PROJECT_PATH"/res/plant.png\n");

   const PlantInfo *info;
   info = m_plantParser->parse( stream);

   QCOMPARE( info->getPlantFilePath(), QString(PROJECT_PATH"/res/plant.png"));

   QStringList errors = m_plantParser->getErrors();
   QCOMPARE( errors.size(), 1);
   QCOMPARE( errors.at(0), QString("line 2: missing closing tag for plant picture"));
}

void PlantParserTest::testPlantLabel_valid()
{
   QTextStream stream("<!--PLANT_NAME>\n"\
                      "A test plant. Version A.01\n"\
                      "<PLANT_NAME-->\n");

   const PlantInfo *info;
   info = m_plantParser->parse( stream);

   QCOMPARE( info->getPlantLabel(), QString( "A test plant. Version A.01"));

   QStringList errors = m_plantParser->getErrors();
   QCOMPARE( errors.size(), 0);
}

void PlantParserTest::testPlantLabel_MissingClosingTag()
{
   QTextStream stream("<!--PLANT_NAME>\n"\
                      "A test plant. Version A.01\n");

   const PlantInfo *info;
   info = m_plantParser->parse( stream);

   QCOMPARE( info->getPlantLabel(), QString( "A test plant. Version A.01"));

   QStringList errors = m_plantParser->getErrors();
   QCOMPARE( errors.size(), 1);
   QCOMPARE( errors.at(0), QString("line 2: missing closing tag for plant name"));
}

void PlantParserTest::testLighPoint_valid()
{
   QTextStream stream("<!--LIGHT_POINTS>\n"\
                      "\"Sala 01\" 0.3 0.5 11\n"\
                      "<LIGHT_POINTS-->\n");

   const PlantInfo *info;
   info = m_plantParser->parse( stream);

   QStringList errors = m_plantParser->getErrors();
   QCOMPARE( errors.size(), 0);

   QList<const LightPoint *> lightPoints = info->getLightPoints();
   QCOMPARE( lightPoints.size(), 1);
   QCOMPARE( lightPoints.at(0)->description(), QString("Sala 01"));
   QCOMPARE( lightPoints.at(0)->position(), QPointF( 0.3, 0.5));
   QCOMPARE( lightPoints.at(0)->ownAddress(), QString("11"));
}

void PlantParserTest::testLighPoint_threeValid()
{
   QTextStream stream("<!--LIGHT_POINTS>\n"\
                      "\"Sala 01\" 0.3 0.5 11\n"\
                      "\"Hall main\" 0.0   1    13\n"\
                      "\"Service room\" 0.0001 0.9999 99\n"\
                      "<LIGHT_POINTS-->\n");

   const PlantInfo *info;
   info = m_plantParser->parse( stream);

   QStringList errors = m_plantParser->getErrors();
   QCOMPARE( errors.size(), 0);

   QList<const LightPoint *> lightPoints = info->getLightPoints();
   QCOMPARE( lightPoints.size(), 3);
}

void PlantParserTest::testLighPoint_MissingClosingTag()
{
   QTextStream stream("<!--LIGHT_POINTS>\n"\
                      "\"Sala 01\" 0.3 0.5 11\n");

   m_plantParser->parse( stream);

   QStringList errors = m_plantParser->getErrors();
   QCOMPARE( errors.size(), 1);
   QCOMPARE( errors.at(0), QString("line 2: missing closing tag for light points"));
}

void PlantParserTest::testLighPoint_BadDescription()
{
   QTextStream stream("<!--LIGHT_POINTS>\n"\
                      "\"Missing quote 0.3 0.5 11\n"\
                      "<LIGHT_POINTS-->\n");

   m_plantParser->parse( stream);

   QStringList errors = m_plantParser->getErrors();
   QCOMPARE( errors.size(), 1);
   QCOMPARE( errors.at(0), QString("line 2: Description or arguments missing [\"Missing quote 0.3 0.5 11]"));
}

void PlantParserTest::testLighPoint_BadPositionHi()
{
   /* bad y coordinate */
   QTextStream stream("<!--LIGHT_POINTS>\n"\
                      "\"Sala 01\" 0.3 1.1 11\n"\
                      "<LIGHT_POINTS-->\n");

   m_plantParser->parse( stream);

   QStringList errors = m_plantParser->getErrors();
   QCOMPARE( errors.size(), 1);
   QCOMPARE( errors.at(0),
             QString("line 2: Light coordinates are not in range (0,0) - (1,1) [\"Sala 01\" 0.3 1.1 11]"));
}

void PlantParserTest::testLighPoint_BadPositionLow()
{
   /* bad x coordinate */
   QTextStream stream("<!--LIGHT_POINTS>\n"\
                      "\"Sala 01\" -0.1 0.5 11\n"\
                      "<LIGHT_POINTS-->\n");

   m_plantParser->parse( stream);

   QStringList errors = m_plantParser->getErrors();
   QCOMPARE( errors.size(), 1);
   QCOMPARE( errors.at(0),
             QString("line 2: Light coordinates are not in range (0,0) - (1,1) [\"Sala 01\" -0.1 0.5 11]"));
}

void PlantParserTest::testLighPoint_missingArgument()
{
   QTextStream stream("<!--LIGHT_POINTS>\n"\
                      "\"Sala 01\" 0.3 0.5\n"\
                      "<LIGHT_POINTS-->\n");

   m_plantParser->parse( stream);

   QStringList errors = m_plantParser->getErrors();
   QCOMPARE( errors.size(), 1);
   QCOMPARE( errors.at(0), QString("line 2: Not enough arguments for light point [\"Sala 01\" 0.3 0.5]"));
}

void PlantParserTest::testGroup_valid()
{
   QTextStream stream("<!--LIGHT_GROUPS>\n"\
                      "\"Tutta la sala\" 0.3 0.5 #1 31 32 33 61 62 63\n"\
                      "<LIGHT_GROUPS-->\n");

   const PlantInfo *info;
   info = m_plantParser->parse( stream);

   QCOMPARE( m_plantParser->getErrors().size(), 0);
   QCOMPARE( info->getLightGroups().size(), 1);

   const LightGroup *group = info->getLightGroups().at(0);
   QCOMPARE( group->node().description(), QString("Tutta la sala"));
   QCOMPARE( group->node().position(), QPointF( 0.3, 0.5));
   QCOMPARE( group->getLightPointList().size(), 6);
}

void PlantParserTest::testGroup_badDescription()
{
   /* missing closing quote */
   QTextStream stream("<!--LIGHT_GROUPS>\n"\
                      "\"Tutta la sala 0.3 0.5 #1 31 32 33\n"\
                      "<LIGHT_GROUPS-->\n");

   const PlantInfo *info;
   info = m_plantParser->parse( stream);

   QCOMPARE( m_plantParser->getErrors().size(), 1);
   QCOMPARE( m_plantParser->getErrors().at(0),
             QString("line 2: Description or arguments missing [\"Tutta la sala 0.3 0.5 #1 31 32 33]"));
}

void PlantParserTest::testGroup_missingPoint()
{
   /* missing point coordinates */
   QTextStream stream("<!--LIGHT_GROUPS>\n"\
                      "\"Tutta la sala\"  #1 31 32 33\n"\
                      "<LIGHT_GROUPS-->\n");

   const PlantInfo *info;
   info = m_plantParser->parse( stream);

   QCOMPARE( m_plantParser->getErrors().size(), 1);
   QCOMPARE( m_plantParser->getErrors().at(0),
             QString("line 2: light group has invalid point [\"Tutta la sala\"  #1 31 32 33]"));
}

void PlantParserTest::testGroup_missingGroupId()
{
   /* group misses '#' */
   QTextStream stream("<!--LIGHT_GROUPS>\n"\
                      "\"Tutta la sala\" 0.3 0.5 1 31 32 33\n"\
                      "<LIGHT_GROUPS-->\n");

   const PlantInfo *info;
   info = m_plantParser->parse( stream);

   QCOMPARE( m_plantParser->getErrors().size(), 1);
   QCOMPARE( m_plantParser->getErrors().at(0),
             QString("line 2: light group should start with '#' [\"Tutta la sala\" 0.3 0.5 1 31 32 33]"));
}

void PlantParserTest::testGateway_valid()
{
   QTextStream stream("<!--MH200N_ADDRESS>\n"\
                      "192.168.1.40   20000\n"\
                      "<MH200N_ADDRESS-->\n");

   const PlantInfo *info;
   info = m_plantParser->parse( stream);

   QStringList errors = m_plantParser->getErrors();
   QCOMPARE( errors.size(), 0);

   QString ipAddress = info->getGatewayIpAddress();
   int ipPort = info->getGatewayIpPort();

   QCOMPARE( ipAddress, QString("192.168.1.40"));
   QCOMPARE( ipPort, 20000);
}

void PlantParserTest::testGateway_MissingClosingTag()
{
   QTextStream stream("<!--MH200N_ADDRESS>\n"\
                      "192.168.1.40   20000\n");

   const PlantInfo *info;
   info = m_plantParser->parse( stream);

   QCOMPARE( info->getGatewayIpAddress(), QString("192.168.1.40"));

   QStringList errors = m_plantParser->getErrors();
   QCOMPARE( errors.size(), 1);
   QCOMPARE( errors.at(0), QString("line 2: Missing tag <MH200N_ADDRESS--> []"));
}


void PlantParserTest::testGateway_BadIpAddress()
{
   QTextStream stream("<!--MH200N_ADDRESS>\n"\
                      "192.168.1   20000\n"\
                      "<MH200N_ADDRESS-->\n");

   m_plantParser->parse( stream);

   QStringList errors = m_plantParser->getErrors();
   QCOMPARE( errors.size(), 1);
   QCOMPARE( errors.at(0), QString("line 2: Bad ip address [192.168.1   20000]"));
}

void PlantParserTest::testGateway_BadIpAddress2()
{
   QTextStream stream("<!--MH200N_ADDRESS>\n"\
                      "192.168.1.ss   20000\n"\
                      "<MH200N_ADDRESS-->\n");

   m_plantParser->parse( stream);

   QStringList errors = m_plantParser->getErrors();
   QCOMPARE( errors.size(), 1);
   QCOMPARE( errors.at(0), QString("line 2: Bad ip address [192.168.1.ss   20000]"));
}

void PlantParserTest::testGateway_MissingPort()
{
   QTextStream stream("<!--MH200N_ADDRESS>\n"\
                      "192.168.1.40   \n"\
                      "<MH200N_ADDRESS-->\n");

   m_plantParser->parse( stream);

   QStringList errors = m_plantParser->getErrors();
   QCOMPARE( errors.size(), 1);
   QCOMPARE( errors.at(0), QString("line 2: Not enough arguments for gateway address [192.168.1.40   ]"));
}

void PlantParserTest::testGateway_BadPort()
{
   QTextStream stream("<!--MH200N_ADDRESS>\n"\
                      "192.168.1.40   xxxx\n"\
                      "<MH200N_ADDRESS-->\n");

   m_plantParser->parse( stream);

   QStringList errors = m_plantParser->getErrors();
   QCOMPARE( errors.size(), 1);
   QCOMPARE( errors.at(0), QString("line 2: bad value for gateway port [192.168.1.40   xxxx]"));
}

void PlantParserTest::testTwoParseConsequtive()
{
   QString content("<!--LIGHT_POINTS>\n"\
                   "\"Sala 01\" 0.3 0.5 11\n"\
                   "\"Hall main\" 0.0   1    13\n"\
                   "\"Service room\" 0.0001 0.9999 99\n"\
                   "<LIGHT_POINTS-->\n");

   QTextStream stream1(&content);
   QTextStream stream2(&content);

   const PlantInfo *info;

   /* parse file twice. Second parse must reset the first */
   info = m_plantParser->parse( stream1);
   info = m_plantParser->parse( stream2);

   QStringList errors = m_plantParser->getErrors();
   QCOMPARE( errors.size(), 0);

   QList<const LightPoint *> lightPoints = info->getLightPoints();
   QCOMPARE( lightPoints.size(), 3);
}

