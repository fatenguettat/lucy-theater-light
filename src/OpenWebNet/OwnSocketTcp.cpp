#include "OwnSocketTcp.h"

#include <QTcpSocket>

OwnSocketTcp::OwnSocketTcp(QObject *parent) :
   OwnSocket_IF(parent),
   m_socket(new QTcpSocket(this))
{
   connect (m_socket, SIGNAL(connected()), this, SIGNAL(connected()) );
   connect (m_socket, SIGNAL(disconnected()), this, SIGNAL(disconnected()) );
   connect (m_socket, SIGNAL(bytesWritten(qint64)), this, SIGNAL(bytesWritten(qint64)) );
   connect (m_socket, SIGNAL(readyRead()), this, SIGNAL(readyRead()) );
   connect (m_socket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SIGNAL(error(QAbstractSocket::SocketError)) );
}


OwnSocketTcp::~OwnSocketTcp()
{
   delete m_socket;
}


void OwnSocketTcp::connectToHost(const QHostAddress &address, quint16 port)
{
   /* for sequential call, choke all previous pending operation */
   m_socket->abort();

   m_socket->connectToHost( address, port);
}

void OwnSocketTcp::disconnectFromHost()
{
   m_socket->disconnectFromHost();
}

bool OwnSocketTcp::atEnd()
{
   return m_socket->atEnd();
}

QByteArray OwnSocketTcp::readAll()
{
   return m_socket->readAll();
}

void OwnSocketTcp::write(QByteArray data)
{
   m_socket->write(data);
}

void OwnSocketTcp::close()
{
   m_socket->abort();
   m_socket->close();
}
