#include "tst_OwnEngine.h"
#include "QtTest"

#include <QSignalSpy>

#include "LightPoint.h"
#include "OwnEngine.h"
#include "OwnConstants.h"
#include "MockNetworkUi.h"
#include "MockOwnSocket.h"
#include "OwnInputParser.h"
#include "MockErrorNotifier.h"
#include "OwnLink.h"
#include "OwnFormatter.h"



tst_OwnEngine::tst_OwnEngine(QObject *parent) :
   QObject(parent)
{
}

void tst_OwnEngine::init()
{
   m_network = new MockNetworkUi( this);
   m_socket = new MockOwnSocket();
   m_parser = new OwnInputParser(this);
   m_errorNotifier = new MockErrorNotifier();
   m_ownLink = new OwnLink( *m_network, *m_socket,
                            *m_parser, *m_errorNotifier, this);
   m_formatter = new OwnFormatter();

   m_ownEngine = new OwnEngine( *m_network, *m_ownLink, *m_formatter);
}

void tst_OwnEngine::cleanup()
{
   delete m_ownEngine;
   delete m_formatter;
   delete m_ownLink;
   delete m_errorNotifier;
   delete m_parser;
   delete m_socket;
   delete m_network;
}

void tst_OwnEngine::testInit()
{
   QVERIFY( m_ownEngine != NULL);
}

void tst_OwnEngine::testAddPoint()
{
   QSignalSpy addSignalSpy( m_ownEngine, SIGNAL(lightPointAdded(const LightPoint*)) );
   LightPoint *light = new LightPoint("light 1", QPointF(0.1,0.1), 11);
   m_ownEngine->addLightPoint( *light);

   QCOMPARE( addSignalSpy.size(), 1);
}

void tst_OwnEngine::testTurnOnSingleLight()
{
   QSignalSpy turnOnSpy( m_ownEngine, SIGNAL(lightOnRequestStarted(int)) );

   LightPoint *light = new LightPoint("light 1", QPointF(0.1,0.1), 11);
   m_ownEngine->addLightPoint( *light);
   m_ownEngine->lightPointRequestOn( 11);

   QCOMPARE( turnOnSpy.size(), 1);
   QCOMPARE( turnOnSpy.at(0).at(0).toInt(), 11);

   // TODO voglio anche verificare cosa ha mandato al link

   delete light;
}

void tst_OwnEngine::testTurnOffSingleLight()
{
   QSignalSpy turnOffSpy( m_ownEngine, SIGNAL(lightOffRequestStarted(int)) );

   LightPoint *light = new LightPoint("light 1", QPointF(0.1,0.1), 11);
   m_ownEngine->addLightPoint( *light);
   m_ownEngine->lightPointRequestOff( 11);

   QCOMPARE( turnOffSpy.size(), 1);
   QCOMPARE( turnOffSpy.at(0).at(0).toInt(), 11);

   delete light;
}


void tst_OwnEngine::testRequestStatus()
{
   QSignalSpy statusRequestSpy( m_ownEngine, SIGNAL(lightStatusRequestStarted(int)) );

   LightPoint *light = new LightPoint("light 1", QPointF(0.1,0.1), 11);
   m_ownEngine->addLightPoint( *light);
   m_ownEngine->lightPointProbeStatus( 11);

   QCOMPARE( statusRequestSpy.size(), 1);
   QCOMPARE( statusRequestSpy.at(0).at(0).toInt(), 11);

   delete light;
}

void tst_OwnEngine::testTurnOffAll()
{
   QSignalSpy turnOffSpy( m_ownEngine, SIGNAL(lightOffRequestStarted(int)) );

   LightPoint light1( "light 1", QPointF(0.1, 0.1), 11);
   LightPoint light2( "light 2", QPointF(0.1, 0.1), 12);

   m_ownEngine->addLightPoint( light1);
   m_ownEngine->addLightPoint( light2);

   m_ownEngine->lightPointRequestOff( 0);

   QCOMPARE( turnOffSpy.size(), 2);
   QCOMPARE( turnOffSpy.at(0).at(0).toInt(), 11);
   QCOMPARE( turnOffSpy.at(1).at(0).toInt(), 12);
}

void tst_OwnEngine::testTurnOnAll()
{
   QSignalSpy turnOnSpy( m_ownEngine, SIGNAL(lightOnRequestStarted(int)) );

   LightPoint light1( "light 1", QPointF(0.1, 0.1), 11);
   LightPoint light2( "light 2", QPointF(0.1, 0.1), 12);

   m_ownEngine->addLightPoint( light1);
   m_ownEngine->addLightPoint( light2);

   m_ownEngine->lightPointRequestOn( 0);

   QCOMPARE( turnOnSpy.size(), 2);
   QCOMPARE( turnOnSpy.at(0).at(0).toInt(), 11);
   QCOMPARE( turnOnSpy.at(1).at(0).toInt(), 12);
}

void tst_OwnEngine::testSequenceCompleteForOn()
{
   QSignalSpy sequenceOnAckSpy( m_ownEngine, SIGNAL(lightOnAcked(int)));
   LightPoint light1( "light 1", QPointF(0.1, 0.1), 11);

   m_ownEngine->addLightPoint( light1);

   m_ownEngine->lightPointRequestOn( 11);
   /* suppose sequence completes well */
   emit m_ownLink->sequenceComplete();

   QCOMPARE(sequenceOnAckSpy.size(), 1);
   QCOMPARE(sequenceOnAckSpy.at(0).at(0).toInt(), 11);
}

void tst_OwnEngine::testSequenceCompleteForOff()
{
   QSignalSpy sequenceOffAckSpy( m_ownEngine, SIGNAL(lightOffAcked(int)));
   LightPoint light1( "light 1", QPointF(0.1, 0.1), 13);

   m_ownEngine->addLightPoint( light1);

   m_ownEngine->lightPointRequestOff( 13);
   /* suppose sequence completes well */
   emit m_ownLink->sequenceComplete();

   QCOMPARE(sequenceOffAckSpy.size(), 1);
   QCOMPARE(sequenceOffAckSpy.at(0).at(0).toInt(), 13);
}

void tst_OwnEngine::testSequenceCompleteForLevel()
{
   QSignalSpy sequenceLevelAckSpy( m_ownEngine, SIGNAL(lightLevelAcked(int, own::LIGHT_LEVEL)) );
   LightPoint light1( "light 1", QPointF(0.1, 0.1), 12);

   m_ownEngine->addLightPoint( light1);

   m_ownEngine->lightPointRequestLevel( 12, own::LEVEL_40);
   /* suppose sequence completes well */
   emit m_ownLink->sequenceComplete();

   QCOMPARE(sequenceLevelAckSpy.size(), 1);
   QCOMPARE(sequenceLevelAckSpy.at(0).at(0).toInt(), 12);
   /* own::LIGHT_LEVEL is converted bad in QVariant */
}

// TODO test probe status
