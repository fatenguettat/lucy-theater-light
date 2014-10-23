#include "tst_PlantLoader.h"

#include <QtTest>

#include "PlantLoader.h"
#include "PlantInfo.h"
#include "OwnEngine.h"
#include "LightGroup.h"
#include "Scenario.h"
#include "MockGuiInterafce.h"
#include "MockPlantFactory.h"

Q_DECLARE_METATYPE(const LightGroup *)
Q_DECLARE_METATYPE(const LightPoint *)
Q_DECLARE_METATYPE(const Scenario *)


PlantLoaderTest::PlantLoaderTest(QObject *parent) :
   QObject(parent)
{
   qRegisterMetaType<const LightPoint *>("const LightPoint *");
   qRegisterMetaType<const LightGroup *>("const LightGroup *");
   qRegisterMetaType<const Scenario *>("const Scenario *");
}

void PlantLoaderTest::init()
{
   m_plantLoader = NULL;
   m_plantInfo = NULL;
   m_ownEngine = NULL;
   m_guiInterface = NULL;

   m_plantFactory = new MockPlantFactory();
   m_guiInterface = new MockGuiInterafce();
   m_plantLoader = new PlantLoader( this);
}

void PlantLoaderTest::cleanup()
{
   delete m_plantLoader;
   delete m_guiInterface;
   delete m_plantFactory;
}

void PlantLoaderTest::testInit()
{
   QVERIFY( m_plantLoader != NULL);
}

void PlantLoaderTest::testPlantLayout()
{
   QString filePath = PROJECT_PATH"res/plant.png";

   m_plantInfo = new PlantInfo( filePath, "test plant",
                                QList<const LightPoint *>(),
                                QList<const LightGroup *>(),
                                QList<const Scenario *>(),
                                "127.0.0.1", 20000);

   m_ownEngine = m_plantFactory->buildOwnEngine( *m_plantInfo);
   m_plantLoader->load( *m_plantInfo, m_guiInterface, m_ownEngine);

   QCOMPARE( m_guiInterface->mockGetPlantLayoutPath(), filePath);

   m_plantFactory->destroyOwnEngine( m_ownEngine);
   delete m_plantInfo;
}

void PlantLoaderTest::testPlantLayoutInvalid()
{
   bool exceptionRised = false;

   QString filePath = "C:/this/does/not/exist.png";

   m_plantInfo = new PlantInfo( filePath, "test plant",
                                QList<const LightPoint *>(),
                                QList<const LightGroup *>(),
                                QList<const Scenario *>(),
                                "127.0.0.1", 20000);

   m_ownEngine = m_plantFactory->buildOwnEngine( *m_plantInfo);

   try
   {
      m_plantLoader->load( *m_plantInfo, m_guiInterface, m_ownEngine);
   }
   catch (QString & errorMsg)
   {
      exceptionRised = true;
      QCOMPARE( errorMsg, QString("unable to load file: ") + filePath);
   }

   QVERIFY(exceptionRised);

   m_plantFactory->destroyOwnEngine( m_ownEngine);
   delete m_plantInfo;
}

void PlantLoaderTest::testPlantLabel()
{
   QString filePath = PROJECT_PATH"res/plant.png";

   m_plantInfo = new PlantInfo( filePath, "test plant description",
                                QList<const LightPoint *>(),
                                QList<const LightGroup *>(),
                                QList<const Scenario *>(),
                                "127.0.0.1", 20000);

   m_ownEngine = m_plantFactory->buildOwnEngine( *m_plantInfo);
   m_plantLoader->load( *m_plantInfo, m_guiInterface, m_ownEngine);

   QCOMPARE( m_guiInterface->getPlantLabel(), QString("test plant description"));

   m_plantFactory->destroyOwnEngine( m_ownEngine);
   delete m_plantInfo;

}

void PlantLoaderTest::testLightPointsToEngine()
{
   QList<const LightPoint *> lightSet;

   lightSet << new LightPoint("light 1", QPointF(0.1, 0.2), "11");
   lightSet << new LightPoint("light 2", QPointF(0.3, 0.4), "12");

   m_plantInfo = new PlantInfo( PROJECT_PATH"res/plant.png",  "test plant",
                                lightSet,
                                QList<const LightGroup *>(),
                                QList<const Scenario *>(),
                                "127.0.0.1", 20000);

   m_ownEngine = m_plantFactory->buildOwnEngine( *m_plantInfo);
   QSignalSpy addLightSpy( m_ownEngine, SIGNAL(lightPointAdded(const LightPoint*)) );

   m_plantLoader->load( *m_plantInfo, m_guiInterface, m_ownEngine);

   QCOMPARE( addLightSpy.size(), 2);
   const LightPoint *lightCheck = addLightSpy.at(0).at(0).value<const LightPoint *>();
   QCOMPARE( lightCheck->description(), QString("light 1") );
   QCOMPARE( lightCheck->ownAddress(), QString("11"));
   QCOMPARE( lightCheck->position(), QPointF(0.1, 0.2));

   lightCheck = addLightSpy.at(1).at(0).value<const LightPoint *>();
   QCOMPARE( lightCheck->description(), QString("light 2") );
   QCOMPARE( lightCheck->ownAddress(), QString("12"));
   QCOMPARE( lightCheck->position(), QPointF(0.3, 0.4));

   m_plantFactory->destroyOwnEngine( m_ownEngine);
   delete m_plantInfo;
   delete lightSet.at(1);
   delete lightSet.at(0);
}


void PlantLoaderTest::testLightGroupToEngine()
{
   QList<const LightGroup *> lightGroupSet;
   LightPoint node1("all hall", QPointF( .5, .5), "#1");
   LightPoint node2("all corners", QPointF( .3, .3), "#2");

   lightGroupSet << new LightGroup( node1, QList<own::Where>() << "11" << "12");
   lightGroupSet << new LightGroup( node2, QList<own::Where>() << "21" << "22" << "23");

   m_plantInfo = new PlantInfo( PROJECT_PATH"res/plant.png",  "test plant",
                                QList<const LightPoint *>(),
                                lightGroupSet,
                                QList<const Scenario *>(),
                                "127.0.0.1", 20000);

   m_ownEngine = m_plantFactory->buildOwnEngine( *m_plantInfo);
   QSignalSpy addGroupSpy( m_ownEngine, SIGNAL(lightGroupAdded(const LightGroup*)) );

   m_plantLoader->load( *m_plantInfo, m_guiInterface, m_ownEngine);

   QCOMPARE( addGroupSpy.size(), 2);
   QCOMPARE( addGroupSpy.at(0).at(0).value<const LightGroup*>()->getLightPointList().size(), 2);
   QCOMPARE( addGroupSpy.at(1).at(0).value<const LightGroup*>()->getLightPointList().size(), 3);
}

void PlantLoaderTest::testScenarioToEngine()
{
   QList<const Scenario *> scenarioSet;

   scenarioSet << new Scenario( "scenario 1");
   scenarioSet << new Scenario( "scenario 2");

   m_plantInfo = new PlantInfo( PROJECT_PATH"res/plant.png",  "test plant",
                                QList<const LightPoint *>(),
                                QList<const LightGroup *>(),
                                scenarioSet,
                                "127.0.0.1", 20000);

   m_ownEngine = m_plantFactory->buildOwnEngine( *m_plantInfo);
   QSignalSpy addScenarioSpy( m_ownEngine, SIGNAL(scenarioAdded(const Scenario*)) );

   m_plantLoader->load( *m_plantInfo, m_guiInterface, m_ownEngine);

   QCOMPARE( addScenarioSpy.size(), 2);
   QCOMPARE( addScenarioSpy.at(0).at(0).
             value<const Scenario*>()->getDescription(), QString("scenario 1"));
   QCOMPARE( addScenarioSpy.at(1).at(0).
             value<const Scenario*>()->getDescription(), QString("scenario 2"));
}

void PlantLoaderTest::testReload()
{
   QList<const LightPoint *> lightSet;

   lightSet << new LightPoint("light 1", QPointF(0.1, 0.2), "11");
   lightSet << new LightPoint("light 2", QPointF(0.3, 0.4), "12");

   m_plantInfo = new PlantInfo( PROJECT_PATH"res/plant.png",  "test plant",
                                lightSet,
                                QList<const LightGroup *>(),
                                QList<const Scenario *>(),
                                "127.0.0.1", 20000);

   m_ownEngine = m_plantFactory->buildOwnEngine( *m_plantInfo);
   QSignalSpy addLightSpy( m_ownEngine, SIGNAL(lightPointAdded(const LightPoint*)) );

   /* PlantLoader does not check for 'brand-new' GUI and engine */
   m_plantLoader->load( *m_plantInfo, m_guiInterface, m_ownEngine);
   m_plantLoader->load( *m_plantInfo, m_guiInterface, m_ownEngine);

   QCOMPARE( addLightSpy.size(), 4);

   m_plantFactory->destroyOwnEngine( m_ownEngine);
   delete m_plantInfo;
   delete lightSet.at(1);
   delete lightSet.at(0);
}

void PlantLoaderTest::testUnload()
{
   QList<const LightPoint *> lightSet;

   lightSet << new LightPoint("light 1", QPointF(0.1, 0.2), "11");
   lightSet << new LightPoint("light 2", QPointF(0.3, 0.4), "12");

   m_plantInfo = new PlantInfo( PROJECT_PATH"res/plant.png",  "test plant",
                                lightSet,
                                QList<const LightGroup *>(),
                                QList<const Scenario *>(),
                                "127.0.0.1", 20000);

   m_ownEngine = m_plantFactory->buildOwnEngine( *m_plantInfo);
   QSignalSpy clearSigSpy(m_ownEngine, SIGNAL(plantCleared()) );

   m_plantLoader->load( *m_plantInfo, m_guiInterface, m_ownEngine);
   m_plantLoader->unload();

   QCOMPARE( clearSigSpy.size(), 1);
   /* engine has no entries */
   QCOMPARE( m_ownEngine->getLightDescription("11"), QString());

   m_plantFactory->destroyOwnEngine( m_ownEngine);
   delete m_plantInfo;
   delete lightSet.at(1);
   delete lightSet.at(0);
}

void PlantLoaderTest::testLoadSignal()
{
   QString filePath = PROJECT_PATH"res/plant.png";

   m_plantInfo = new PlantInfo( filePath, "test plant description",
                                QList<const LightPoint *>(),
                                QList<const LightGroup *>(),
                                QList<const Scenario *>(),
                                "127.0.0.1", 20000);

   m_ownEngine = m_plantFactory->buildOwnEngine( *m_plantInfo);
   QSignalSpy loadSignal(m_plantLoader, SIGNAL(plantLoaded(bool)) );
   m_plantLoader->load( *m_plantInfo, m_guiInterface, m_ownEngine);

   QCOMPARE( loadSignal.size(), 1);
   QCOMPARE( loadSignal.at(0).at(0).toBool(), true);

   m_plantFactory->destroyOwnEngine( m_ownEngine);
   delete m_plantInfo;
}

void PlantLoaderTest::testUnloadSignal()
{
   QString filePath = PROJECT_PATH"res/plant.png";

   m_plantInfo = new PlantInfo( filePath, "test plant description",
                                QList<const LightPoint *>(),
                                QList<const LightGroup *>(),
                                QList<const Scenario *>(),
                                "127.0.0.1", 20000);

   m_ownEngine = m_plantFactory->buildOwnEngine( *m_plantInfo);
   QSignalSpy loadSignal(m_plantLoader, SIGNAL(plantLoaded(bool)) );

   m_plantLoader->load( *m_plantInfo, m_guiInterface, m_ownEngine);
   m_plantLoader->unload();

   QCOMPARE( loadSignal.size(), 2);
   QCOMPARE( loadSignal.at(0).at(0).toBool(), true);  /* load */
   QCOMPARE( loadSignal.at(1).at(0).toBool(), false); /* unload */

   m_plantFactory->destroyOwnEngine( m_ownEngine);
   delete m_plantInfo;
}
