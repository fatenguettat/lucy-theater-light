#include "tst_OwnLink.h"

#include <QtTest>
#include <QAbstractSocket>
#include <QSignalSpy>

#include "OwnConstants.h"
#include "OwnLink.h"
#include "OwnInputParser.h"
#include "MockOwnSocket.h"
#include "MockNetworkUi.h"
#include "MockErrorNotifier.h"


tst_OwnLink::tst_OwnLink(QObject *parent) :
   QObject(parent),
   m_ownLink(NULL),
   m_parser(NULL),
   m_networkUserInterface(NULL),
   m_socket(NULL),
   m_errorNotifier(NULL)
{
}

void tst_OwnLink::init()
{

   m_networkUserInterface = new MockNetworkUi(this);
   m_socket = new MockOwnSocket();
   m_parser = new OwnInputParser(this);
   m_errorNotifier = new MockErrorNotifier();

   m_ownLink = new OwnLink( *m_networkUserInterface, *m_socket,
                          *m_parser, *m_errorNotifier, this);
}

void tst_OwnLink::cleanup()
{
   delete m_ownLink;
   delete m_errorNotifier;
   delete m_parser;
   delete m_socket;
   delete m_networkUserInterface;

   m_ownLink = NULL;
   m_errorNotifier = NULL;
   m_parser = NULL;
   m_socket = NULL;
   m_networkUserInterface = NULL;
}

void tst_OwnLink::testInit()
{
   QVERIFY( m_ownLink != NULL);
}

/**
 * @brief send a message to turn on a light
 *
 *   THIS                 SERVER
 *   *99*0##      ->
 *                <-      *#*1##
 *   *1*1*0##     ->
 *                <-      *#*1##
 */
void tst_OwnLink::sendTurnOn()
{
   try
   {
      m_ownLink->triggerSendMessage(QString("*1*1*0##"));
      QVERIFY( m_socket->isConnectionActive());
      m_socket->makeIncomingData(own::ACK_STRING);
      m_socket->verifyOutgoingData( own::COMMAND_SESSION_STRING);

      m_socket->makeIncomingData(own::ACK_STRING);
      m_socket->verifyOutgoingData( "*1*1*0##");

      m_socket->makeIncomingData(own::ACK_STRING);
      QVERIFY( ! m_socket->isConnectionActive());
   }
   catch( QString & error)
   {
      QFAIL(error.toLatin1().constData());
   }
}

void tst_OwnLink::unexpectedMessage()
{
   m_ownLink->triggerSendMessage(QString("*1*1*0##"));
   m_socket->makeIncomingData(own::ACK_STRING);
   m_socket->verifyOutgoingData( own::COMMAND_SESSION_STRING);

   /* terminated unexpected message */
   m_socket->makeIncomingData("????##");
   QCOMPARE( m_errorNotifier->lastNotificationMessage(),
             QString("received unexpected message: ????##"));
   QCOMPARE( m_errorNotifier->lastLogType(), ErrorNotifier_IF::SilentLog);

   /* connection remains active */
   QVERIFY( m_socket->isConnectionActive());
}

void tst_OwnLink::messageOnSequenceComplete()
{
   QSignalSpy sequenceCompleteListener( m_ownLink, SIGNAL(sequenceComplete()) );

   m_ownLink->triggerSendMessage(QString("*1*1*0##"));
   m_socket->makeIncomingData(own::ACK_STRING);
   m_socket->verifyOutgoingData( own::COMMAND_SESSION_STRING);

   m_socket->makeIncomingData(own::ACK_STRING);
   m_socket->verifyOutgoingData( "*1*1*0##");

   m_socket->makeIncomingData(own::ACK_STRING);
   QCOMPARE( sequenceCompleteListener.size(), 1);
}

void tst_OwnLink::noMessageOnSequenceError()
{
   QSignalSpy sequenceCompleteListener( m_ownLink, SIGNAL(sequenceComplete()) );

   m_ownLink->triggerSendMessage(QString("*1*1*0##"));
   m_socket->makeIncomingData(own::ACK_STRING);
   m_socket->verifyOutgoingData( own::COMMAND_SESSION_STRING);

   /* terminated unexpected message */
   m_socket->makeIncomingData("????##");

   QCOMPARE( sequenceCompleteListener.size(), 0);
}



