#include "tst_OwnInputParser.h"

#include <QtTest>
#include <QSignalSpy>

#include "OwnInputParser.h"

tst_OwnInputParser::tst_OwnInputParser(QObject *parent) :
   QObject(parent),
   m_parser(NULL)
{
}

void tst_OwnInputParser::init()
{
   m_parser = new OwnInputParser( this);
}

void tst_OwnInputParser::cleanup()
{
   delete m_parser;
   m_parser = NULL;
}

void tst_OwnInputParser::testInit()
{
   QVERIFY( m_parser != NULL);
}

/** a compelte OWN message in one call */
void tst_OwnInputParser::testFullMessage()
{
   QSignalSpy  messageRxSpy( m_parser, SIGNAL(messageComplete(QString)) );

   m_parser->onDataReceived("*#*1##");

   QCOMPARE( messageRxSpy.size(), 1);
   QCOMPARE( messageRxSpy.at(0).at(0).toString(), QString("*#*1##"));
}

/** one call has a non complete own message */
void tst_OwnInputParser::testUncompleteMessage()
{
   QSignalSpy  messageRxSpy( m_parser, SIGNAL(messageComplete(QString)) );

   m_parser->onDataReceived("*#*");
   QCOMPARE( messageRxSpy.size(), 0);
}

/** a complete message is split in two calls */
void tst_OwnInputParser::testSplitInTwo()
{
   QSignalSpy  messageRxSpy( m_parser, SIGNAL(messageComplete(QString)) );

   m_parser->onDataReceived("*#*");
   m_parser->onDataReceived("1##");

   QCOMPARE( messageRxSpy.size(), 1);
   QCOMPARE( messageRxSpy.at(0).at(0).toString(), QString("*#*1##"));
}

/** a single call holds two complete messages */
void tst_OwnInputParser::testTwoMessagesInOneCall()
{
   QSignalSpy  messageRxSpy( m_parser, SIGNAL(messageComplete(QString)) );

   m_parser->onDataReceived("*1*1*0##*#*1##");

   QCOMPARE( messageRxSpy.size(), 2);
   QCOMPARE( messageRxSpy.at(0).at(0).toString(), QString("*1*1*0##"));
   QCOMPARE( messageRxSpy.at(1).at(0).toString(), QString("*#*1##"));
}

/** first call has one full message and half; second call completes the message */
void tst_OwnInputParser::testOverlappingMessages()
{
   QSignalSpy  messageRxSpy( m_parser, SIGNAL(messageComplete(QString)) );

   m_parser->onDataReceived("*1*1*0##*#");
   QCOMPARE( messageRxSpy.size(), 1);

   m_parser->onDataReceived("*1##");
   QCOMPARE( messageRxSpy.size(), 2);

   QCOMPARE( messageRxSpy.at(0).at(0).toString(), QString("*1*1*0##"));
   QCOMPARE( messageRxSpy.at(1).at(0).toString(), QString("*#*1##"));
}

/** a message with symbols not managed by OpenWebNet.
 * It is not responsibility of the parser to validate such symbols. */
void tst_OwnInputParser::testIllegalSymbols()
{
   QSignalSpy  messageRxSpy( m_parser, SIGNAL(messageComplete(QString)) );

   m_parser->onDataReceived("*abc YY##");
   QCOMPARE( messageRxSpy.size(), 1);

   QCOMPARE( messageRxSpy.at(0).at(0).toString(), QString("*abc YY##"));
}
