#ifndef TST_OWNLINK_H
#define TST_OWNLINK_H


#include <QObject>

class OwnLink;

class OwnInputParser;
class NetworkUi_IF;
class MockOwnSocket;
class MockErrorNotifier;


class tst_OwnLink : public QObject
{
   Q_OBJECT
public:
   explicit tst_OwnLink(QObject *parent = 0);

public slots:
   /* called before every test case */
   void init();
   /* called after every test case */
   void cleanup();

private Q_SLOTS:
   void testInit();
   void sendTurnOn();
   void unexpectedMessage();

private:
   OwnLink *ownLink;

   OwnInputParser *m_parser;
   NetworkUi_IF *m_networkUserInterface;
   MockOwnSocket *m_socket;
   MockErrorNotifier *m_errorNotifier;
};

#endif // TST_OWNLINK_H
