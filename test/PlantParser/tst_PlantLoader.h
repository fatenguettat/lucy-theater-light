#ifndef PLANTLOADERTEST_H
#define PLANTLOADERTEST_H

#include <QObject>

class PlantLoader;
class PlantInfo;
class OwnEngine;
class MockGuiInterafce;
class MockPlantFactory;



class PlantLoaderTest : public QObject
{
   Q_OBJECT
public:
   explicit PlantLoaderTest(QObject *parent = 0);


public slots:
   void init();
   void cleanup();

private Q_SLOTS:
   void testInit();
   void testPlantLayout();
   void testPlantLayoutInvalid();
   void testPlantLabel();
   void testLightPointsToEngine();
   void testLightGroupToEngine();
   void testScenarioToEngine();
   void testReload();
   void testUnload();
   void testLoadSignal();
   void testUnloadSignal();

private:
   PlantLoader *m_plantLoader;

   PlantInfo *m_plantInfo;
   OwnEngine *m_ownEngine;
   MockGuiInterafce *m_guiInterface;
   MockPlantFactory *m_plantFactory;
};

#endif // PLANTLOADERTEST_H
