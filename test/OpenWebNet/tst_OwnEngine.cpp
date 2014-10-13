#include "tst_OwnEngine.h"
#include "QtTest"

#include <QSignalSpy>

#include "LightPoint.h"
#include "LightGroup.h"
#include "OwnEngine.h"
#include "OwnConstants.h"
#include "MockNetworkUi.h"
#include "MockOwnSocket.h"
#include "OwnInputParser.h"
#include "MockErrorNotifier.h"
#include "OwnLink.h"
#include "OwnFormatter.h"

Q_DECLARE_METATYPE(own::LIGHT_LEVEL)
Q_DECLARE_METATYPE(const LightGroup *)
Q_DECLARE_METATYPE(const LightPoint *)


tst_OwnEngine::tst_OwnEngine(QObject *parent) :
   QObject(parent)
{
   qRegisterMetaType<const LightPoint *>("const LightPoint *");
   qRegisterMetaType<const LightGroup *>("const LightGroup *");
   qRegisterMetaType<own::LIGHT_LEVEL>("own::Where");
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
   LightPoint *light = new LightPoint("light 1", QPointF(0.1,0.1), "11");
   m_ownEngine->addLightPoint( *light);

   QCOMPARE( addSignalSpy.size(), 1);
   QCOMPARE( addSignalSpy.at(0).at(0).value<const LightPoint*>()->description(),
             QString("light 1") );

   delete light;
}

void tst_OwnEngine::testAddGroup()
{
   QSignalSpy addSignalSpy( m_ownEngine, SIGNAL(lightGroupAdded(const LightGroup*)) );

   LightPoint *light = new LightPoint("group 1", QPointF( 0.1, 0.1), "#1");
   LightGroup *group = new LightGroup( *light, QList<own::Where>() << "11" << "12");

   m_ownEngine->addLightGroup( *group);

   QCOMPARE( addSignalSpy.size(), 1);
   QCOMPARE( addSignalSpy.at(0).at(0).value<const LightGroup*>()->getLightPointList().size(), 2);

   delete group;
   delete light;
}

void tst_OwnEngine::testTurnOnSingleLight()
{
   QSignalSpy turnOnSpy( m_ownEngine, SIGNAL(lightOnRequestStarted(own::Where)) );

   LightPoint *light = new LightPoint("light 1", QPointF(0.1,0.1), "11");
   m_ownEngine->addLightPoint( *light);
   m_ownEngine->lightRequestOn( "11");

   QCOMPARE( turnOnSpy.size(), 1);
   QCOMPARE( turnOnSpy.at(0).at(0).toString(), QString("11"));

   // TODO voglio anche verificare cosa ha mandato al link

   delete light;
}

void tst_OwnEngine::testTurnOffSingleLight()
{
   QSignalSpy turnOffSpy( m_ownEngine, SIGNAL(lightOffRequestStarted(own::Where)) );

   LightPoint *light = new LightPoint("light 1", QPointF(0.1,0.1), "11");
   m_ownEngine->addLightPoint( *light);
   m_ownEngine->lightRequestOff( "11");

   QCOMPARE( turnOffSpy.size(), 1);
   QCOMPARE( turnOffSpy.at(0).at(0).toString(), QString("11"));

   delete light;
}


void tst_OwnEngine::testRequestStatus()
{
   QSignalSpy statusRequestSpy( m_ownEngine, SIGNAL(lightStatusRequestStarted(own::Where)) );

   LightPoint *light = new LightPoint("light 1", QPointF(0.1,0.1), "11");
   m_ownEngine->addLightPoint( *light);
   m_ownEngine->lightProbeStatus( "11");

   QCOMPARE( statusRequestSpy.size(), 1);
   QCOMPARE( statusRequestSpy.at(0).at(0).toString(), QString("11"));

   delete light;
}

void tst_OwnEngine::testTurnOffAll()
{
   QSignalSpy turnOffSpy( m_ownEngine, SIGNAL(lightOffRequestStarted(own::Where)) );

   LightPoint light1( "light 1", QPointF(0.1, 0.1), "11");
   LightPoint light2( "light 2", QPointF(0.1, 0.1), "12");

   m_ownEngine->addLightPoint( light1);
   m_ownEngine->addLightPoint( light2);

   m_ownEngine->lightRequestOff( own::GLOBAL_WHERE);

   QCOMPARE( turnOffSpy.size(), 2);
   QCOMPARE( turnOffSpy.at(0).at(0).toString(), QString("11"));
   QCOMPARE( turnOffSpy.at(1).at(0).toString(), QString("12"));
}

void tst_OwnEngine::testTurnOffAllAcked()
{
   QSignalSpy turnOffAckedSpy( m_ownEngine, SIGNAL(lightOffAcked(own::Where)) );

   LightPoint light1( "light 1", QPointF(0.1, 0.1), "11");
   LightPoint light2( "light 2", QPointF(0.1, 0.1), "12");

   m_ownEngine->addLightPoint( light1);
   m_ownEngine->addLightPoint( light2);

   m_ownEngine->lightRequestOff( own::GLOBAL_WHERE);
   /* suppose sequence completes well */
   emit m_ownLink->sequenceComplete();

   QCOMPARE( turnOffAckedSpy.size(), 2);
   QCOMPARE( turnOffAckedSpy.at(0).at(0).value<own::Where>(), QString("11"));
   QCOMPARE( turnOffAckedSpy.at(1).at(0).value<own::Where>(), QString("12"));
}

void tst_OwnEngine::testTurnOnAll()
{
   QSignalSpy turnOnSpy( m_ownEngine, SIGNAL(lightOnRequestStarted(own::Where)) );

   LightPoint light1( "light 1", QPointF(0.1, 0.1), "11");
   LightPoint light2( "light 2", QPointF(0.1, 0.1), "12");

   m_ownEngine->addLightPoint( light1);
   m_ownEngine->addLightPoint( light2);

   m_ownEngine->lightRequestOn( own::GLOBAL_WHERE);

   QCOMPARE( turnOnSpy.size(), 2);
   QCOMPARE( turnOnSpy.at(0).at(0).toString(), QString("11"));
   QCOMPARE( turnOnSpy.at(1).at(0).toString(), QString("12"));
}

void tst_OwnEngine::testTurnOnAllAcked()
{
   QSignalSpy turnOnAckedSpy( m_ownEngine, SIGNAL(lightOnAcked(own::Where)) );

   LightPoint light1( "light 1", QPointF(0.1, 0.1), "11");
   LightPoint light2( "light 2", QPointF(0.1, 0.1), "12");

   m_ownEngine->addLightPoint( light1);
   m_ownEngine->addLightPoint( light2);

   m_ownEngine->lightRequestOn( own::GLOBAL_WHERE);
   /* suppose sequence completes well */
   emit m_ownLink->sequenceComplete();

   QCOMPARE( turnOnAckedSpy.size(), 2);
   QCOMPARE( turnOnAckedSpy.at(0).at(0).value<own::Where>(), QString("11"));
   QCOMPARE( turnOnAckedSpy.at(1).at(0).value<own::Where>(), QString("12"));
}

void tst_OwnEngine::testTurnOnGroup()
{
   QSignalSpy sequenceOnAckSpy( m_ownEngine, SIGNAL(lightOnAcked(own::Where)) );

   LightPoint *light = new LightPoint("group 1", QPointF( 0.1, 0.1), "#1");
   LightGroup *group = new LightGroup( *light, QList<own::Where>() << "11" << "12" << "13");

   m_ownEngine->addLightGroup( *group);

   m_ownEngine->lightRequestOn("#1");
   /* suppose sequence completes well */
   emit m_ownLink->sequenceComplete();

   /* expected one ack for each light in group */
   QCOMPARE( sequenceOnAckSpy.size(), 3);
   QCOMPARE( sequenceOnAckSpy.at(0).at(0).toString(), QString("11"));
   QCOMPARE( sequenceOnAckSpy.at(1).at(0).toString(), QString("12"));
   QCOMPARE( sequenceOnAckSpy.at(2).at(0).toString(), QString("13"));

   delete light;
   delete group;
}

void tst_OwnEngine::testTurnOffGroup()
{
   QSignalSpy sequenceOffAckSpy( m_ownEngine, SIGNAL(lightOffAcked(own::Where)) );

   LightPoint *light = new LightPoint("group 1", QPointF( 0.1, 0.1), "#1");
   LightGroup *group = new LightGroup( *light, QList<own::Where>() << "11" << "12" << "13");

   m_ownEngine->addLightGroup( *group);

   m_ownEngine->lightRequestOff("#1");
   /* suppose sequence completes well */
   emit m_ownLink->sequenceComplete();

   /* expected one ack for each light in group */
   QCOMPARE( sequenceOffAckSpy.size(), 3);
   QCOMPARE( sequenceOffAckSpy.at(0).at(0).toString(), QString("11"));
   QCOMPARE( sequenceOffAckSpy.at(1).at(0).toString(), QString("12"));
   QCOMPARE( sequenceOffAckSpy.at(2).at(0).toString(), QString("13"));

   delete light;
   delete group;
}

void tst_OwnEngine::testSetLevelForGroup()
{
   QSignalSpy sequenceLevelAckSpy( m_ownEngine,
                                   SIGNAL(lightLevelAcked(own::Where,own::LIGHT_LEVEL)) );

   LightPoint *light = new LightPoint("group 1", QPointF( 0.1, 0.1), "#1");
   LightGroup *group = new LightGroup( *light, QList<own::Where>() << "11" << "12" << "13");

   m_ownEngine->addLightGroup( *group);

   m_ownEngine->lightRequestLevel("#1", own::LEVEL_60);
   /* suppose sequence completes well */
   emit m_ownLink->sequenceComplete();

   /* expected one ack for each light in group */
   QCOMPARE( sequenceLevelAckSpy.size(), 3);
   QCOMPARE( sequenceLevelAckSpy.at(0).at(0).toString(), QString("11"));
   QCOMPARE( sequenceLevelAckSpy.at(0).at(1).value<own::LIGHT_LEVEL>(), own::LEVEL_60);
   QCOMPARE( sequenceLevelAckSpy.at(1).at(0).toString(), QString("12"));
   QCOMPARE( sequenceLevelAckSpy.at(2).at(0).toString(), QString("13"));

   delete light;
   delete group;
}

void tst_OwnEngine::testSequenceCompleteForOn()
{
   QSignalSpy sequenceOnAckSpy( m_ownEngine, SIGNAL(lightOnAcked(own::Where)) );
   LightPoint light1( "light 1", QPointF(0.1, 0.1), "11");

   m_ownEngine->addLightPoint( light1);

   m_ownEngine->lightRequestOn( "11");
   /* suppose sequence completes well */
   emit m_ownLink->sequenceComplete();

   QCOMPARE(sequenceOnAckSpy.size(), 1);
   QCOMPARE(sequenceOnAckSpy.at(0).at(0).toString(), QString("11"));
}

void tst_OwnEngine::testSequenceCompleteForOff()
{
   QSignalSpy sequenceOffAckSpy( m_ownEngine, SIGNAL(lightOffAcked(own::Where)) );
   LightPoint light1( "light 1", QPointF(0.1, 0.1), "13");

   m_ownEngine->addLightPoint( light1);

   m_ownEngine->lightRequestOff( "13");
   /* suppose sequence completes well */
   emit m_ownLink->sequenceComplete();

   QCOMPARE(sequenceOffAckSpy.size(), 1);
   QCOMPARE(sequenceOffAckSpy.at(0).at(0).toString(), QString("13"));
}

void tst_OwnEngine::testSequenceCompleteForLevel()
{
   QSignalSpy sequenceLevelAckSpy( m_ownEngine,
                                   SIGNAL(lightLevelAcked(own::Where,own::LIGHT_LEVEL)) );
   LightPoint light1( "light 1", QPointF(0.1, 0.1), "12");

   m_ownEngine->addLightPoint( light1);

   m_ownEngine->lightRequestLevel( "12", own::LEVEL_40);
   /* suppose sequence completes well */
   emit m_ownLink->sequenceComplete();

   QCOMPARE( sequenceLevelAckSpy.size(), 1);
   QCOMPARE( sequenceLevelAckSpy.at(0).at(0).toString(), QString("12"));
   QCOMPARE( sequenceLevelAckSpy.at(0).at(1).value<own::LIGHT_LEVEL>(), own::LEVEL_40);
}

void tst_OwnEngine::testLightDescription()
{
   LightPoint light1( "light 1", QPointF(0.1, 0.1), "12");

   m_ownEngine->addLightPoint( light1);
   QCOMPARE( m_ownEngine->getLightDescription("12"), QString("light 1"));
}

void tst_OwnEngine::testLightDescriptionNotFound()
{
   /* no lights in engine */
   QCOMPARE( m_ownEngine->getLightDescription("12"), QString());
}

void tst_OwnEngine::testLightGroupDescription()
{
   LightPoint *light = new LightPoint("group 1", QPointF( 0.1, 0.1), "#1");
   LightGroup *group = new LightGroup( *light, QList<own::Where>() << "11" << "12" << "13");

   m_ownEngine->addLightGroup( *group);

   QCOMPARE( m_ownEngine->getLightDescription("#1"), QString("group 1"));
}

