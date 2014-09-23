#include "tst_OwnEngine.h"
#include "QtTest"

#include "OwnEngine.h"
#include "OwnConstants.h"
#include "MockGuiInterafce.h"
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
   m_mockGui = new MockGuiInterafce();
   m_network = new MockNetworkUi( this);
   m_socket = new MockOwnSocket();
   m_parser = new OwnInputParser(this);
   m_errorNotifier = new MockErrorNotifier();
   m_ownLink = new OwnLink( *m_network, *m_socket,
                            *m_parser, *m_errorNotifier, this);
   m_formatter = new OwnFormatter();

   m_ownEgine = new OwnEngine( *m_mockGui, *m_network, *m_ownLink, *m_formatter);
}

void tst_OwnEngine::cleanup()
{
   delete m_ownEgine;
   delete m_formatter;
   delete m_ownLink;
   delete m_errorNotifier;
   delete m_parser;
   delete m_socket;
   delete m_network;
   delete m_mockGui;
}

void tst_OwnEngine::testInit()
{
   QVERIFY( m_ownEgine != NULL);
}

void tst_OwnEngine::testTurnOnSingleLight()
{
   /* simulate signal from GUI */
   m_mockGui->turnOnRequest(11);

   // TODO this is already tested. OwnLink should be mocked
   /* verify sequence */
   try
   {
      QVERIFY( m_socket->isConnectionActive());
      m_socket->makeIncomingData(own::ACK_STRING);
      m_socket->verifyOutgoingData( own::COMMAND_SESSION_STRING);

      m_socket->makeIncomingData(own::ACK_STRING);
      m_socket->verifyOutgoingData( "*1*1*11##");

      m_socket->makeIncomingData(own::ACK_STRING);
      QVERIFY( ! m_socket->isConnectionActive());
   }
   catch( QString & error)
   {
      QFAIL(QString("Unexpected exception: %1").arg(error).toLatin1());
   }

   QCOMPARE( m_mockGui->getLightStatus(11), MockGuiInterafce::LIGHT_ON);
}

void tst_OwnEngine::testTurnOffSingleLight()
{
   /* simulate signal from GUI */
   m_mockGui->turnOffRequest(13);

   /* verify sequence */
   try
   {
      QVERIFY( m_socket->isConnectionActive());
      m_socket->makeIncomingData(own::ACK_STRING);
      m_socket->verifyOutgoingData( own::COMMAND_SESSION_STRING);

      m_socket->makeIncomingData(own::ACK_STRING);
      m_socket->verifyOutgoingData( "*1*0*13##");

      m_socket->makeIncomingData(own::ACK_STRING);
      QVERIFY( ! m_socket->isConnectionActive());
   }
   catch( QString & error)
   {
      QFAIL(QString("Unexpected exception: %1").arg(error).toLatin1());
   }

   QCOMPARE( m_mockGui->getLightStatus(13), MockGuiInterafce::LIGHT_OFF);
}
