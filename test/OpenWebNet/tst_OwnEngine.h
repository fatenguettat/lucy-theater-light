#ifndef TST_OWNENGINE_H
#define TST_OWNENGINE_H

#include <QObject>


class OwnEngine;
class MockNetworkUi;
class MockOwnSocket;
class MockErrorNotifier;
class OwnInputParser;
class OwnLink;
class OwnFormatter;


class tst_OwnEngine : public QObject
{
   Q_OBJECT
public:
   explicit tst_OwnEngine(QObject *parent = 0);

public slots:
   void init();
   void cleanup();

private Q_SLOTS:
   void testInit();
   void testAddPoint();
   void testTurnOnSingleLight();
   void testTurnOffSingleLight();
   void testRequestStatus();
   void testTurnOffAll();
   void testTurnOnAll();
   void testSequenceCompleteForOn();
   void testSequenceCompleteForOff();
   void testSequenceCompleteForLevel();

private:
   OwnEngine *m_ownEngine;
   MockNetworkUi *m_network;
   MockOwnSocket *m_socket;
   MockErrorNotifier *m_errorNotifier;
   OwnInputParser *m_parser;
   OwnLink *m_ownLink;
   OwnFormatter *m_formatter;
};

#endif // TST_OWNENGINE_H
