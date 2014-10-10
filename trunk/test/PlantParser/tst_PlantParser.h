#ifndef PlantParserTestTEST_H
#define PlantParserTestTEST_H

#include <QObject>

class PlantParser;

class PlantParserTest : public QObject
{
   Q_OBJECT

public:
   PlantParserTest();

public slots:
   void init();
   void cleanup();

private Q_SLOTS:
   void testEmptyFile();
   void testFileFormat();
   void testPlantFileName_valid();
   void testPlantFileName_invalidPlantImage();
   void testPlantFileName_MissingClosingTag();
   void testPlantLabel_valid();
   void testPlantLabel_MissingClosingTag();
   void testLighPoint_valid();
   void testLighPoint_threeValid();
   void testLighPoint_MissingClosingTag();
   void testLighPoint_BadDescription();
   void testLighPoint_BadPositionHi();
   void testLighPoint_BadPositionLow();
   void testLighPoint_missingArgument();
   void testGroup_valid();
   void testGroup_badDescription();
   void testGroup_missingPoint();
   void testGroup_missingGroupId();
   void testGateway_valid();
   void testGateway_MissingClosingTag();
   void testGateway_BadIpAddress();
   void testGateway_BadIpAddress2();
   void testGateway_MissingPort();
   void testGateway_BadPort();
   void testTwoParseConsequtive();

private:
   PlantParser *m_plantParser;
};

#endif // PlantParserTestTEST_H
