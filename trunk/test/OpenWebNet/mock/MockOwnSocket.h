#ifndef MOCKTCPSOCKET_H
#define MOCKTCPSOCKET_H

#include "OwnSocket_IF.h"
#include <QByteArray>


class MockOwnSocket : public OwnSocket_IF
{
   Q_OBJECT
public:
   explicit MockOwnSocket(QObject *parent = 0);
   ~MockOwnSocket();

   // OwnSocket_IF interface
public:
   virtual void connectToHost(const QHostAddress &address, quint16 port);
   virtual void disconnectFromHost();
   virtual bool atEnd();
   virtual QByteArray readAll();
   virtual void write(QByteArray data);
   virtual void close();

   // mock functions
   void verifyOutgoingData(const char * data);
   void makeIncomingData(const char * data);
   bool isConnectionActive();

private:
   bool m_isConnectionActive;
   QByteArray m_lastTxFrame;
   QByteArray m_nextRxFrame;

};

#endif // MOCKTCPSOCKET_H
