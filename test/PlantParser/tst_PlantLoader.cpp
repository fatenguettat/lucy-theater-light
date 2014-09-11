#include "tst_PlantLoader.h"

#include <QtTest>

#include "PlantLoader.h"
#include "PlantInfo.h"
#include "MockGuiInterafce.h"


PlantLoaderTest::PlantLoaderTest(QObject *parent) :
   QObject(parent)
{
}

void PlantLoaderTest::init()
{
   m_guiInterface = new MockGuiInterafce();
   m_plantLoader = new PlantLoader( *m_guiInterface);
}

void PlantLoaderTest::cleanup()
{
   delete m_guiInterface;
   delete m_plantLoader;
}

void PlantLoaderTest::testInit()
{
   QVERIFY( m_plantLoader != NULL);
}

void PlantLoaderTest::testPlantLayout()
{
   QString filePath = PROJECT_PATH"res/plant.png";

   m_plantInfo = new PlantInfo( filePath,
                                QList<const LightPoint *>(),
                                "127.0.0.1", 20000);

   m_plantLoader->load( *m_plantInfo);

   QCOMPARE( m_guiInterface->getPlantLayoutPath(), filePath);

   delete m_plantInfo;
}

void PlantLoaderTest::testPlantLayoutInvalid()
{
   bool exceptionRised = false;

   QString filePath = "C:/this/does/not/exist.png";

   m_plantInfo = new PlantInfo( filePath,
                                QList<const LightPoint *>(),
                                "127.0.0.1", 20000);

   try
   {
      m_plantLoader->load( *m_plantInfo);
   }
   catch (QString & errorMsg)
   {
      exceptionRised = true;
      QCOMPARE( errorMsg, QString("unable to load file: ") + filePath);
   }

   QVERIFY(exceptionRised);

   delete m_plantInfo;
}

void PlantLoaderTest::testLightPoints()
{
   QList<const LightPoint *> lightSet;

   lightSet << new LightPoint("light 1", QPointF(0.1, 0.2), 11);
   lightSet << new LightPoint("light 2", QPointF(0.3, 0.4), 12);

   m_plantInfo = new PlantInfo( PROJECT_PATH"res/plant.png",
                                lightSet,
                                "127.0.0.1", 20000);

   m_plantLoader->load( *m_plantInfo);

   QCOMPARE( m_guiInterface->getLightPointList().size(), 2);
   QCOMPARE( m_guiInterface->getLightPointList().at(0).ownAddress, 11);
   QCOMPARE( m_guiInterface->getLightPointList().at(0).position, QPointF(0.1, 0.2));
   QCOMPARE( m_guiInterface->getLightPointList().at(1).ownAddress, 12);
   QCOMPARE( m_guiInterface->getLightPointList().at(1).position, QPointF(0.3, 0.4));

   lightSet.clear();

   delete m_plantInfo;
}
