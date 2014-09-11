#ifndef OWNSOCKETTCP_H
#define OWNSOCKETTCP_H

#include "OwnSocket_IF.h"

class QTcpSocket;


class OwnSocketTcp : public OwnSocket_IF
{
   Q_OBJECT
public:
   explicit OwnSocketTcp(QObject *parent = 0);
   ~OwnSocketTcp();

   // OwnSocket_IF interface
public:
   virtual void connectToHost(const QHostAddress &address, quint16 port);
   virtual void disconnectFromHost();
   virtual bool atEnd();
   virtual QByteArray readAll();
   virtual void write(QByteArray data);
   virtual void close();

private:
   QTcpSocket *m_socket;
};

#endif // OWNSOCKETTCP_H
