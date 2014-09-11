#include "OwnSocketTcp.h"

#include <QTcpSocket>

OwnSocketTcp::OwnSocketTcp(QObject *parent) :
   OwnSocket_IF(parent),
   m_socket(new QTcpSocket(this))
{
}

OwnSocketTcp::~OwnSocketTcp()
{
   delete m_socket;
}


void OwnSocketTcp::connectToHost(const QHostAddress &address, quint16 port)
{
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
   m_socket->close();
}
