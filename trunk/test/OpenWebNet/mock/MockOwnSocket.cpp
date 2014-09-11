#include "MockOwnSocket.h"

#include <string.h>

MockOwnSocket::MockOwnSocket(QObject *parent) :
   OwnSocket_IF( parent),
   m_isConnectionActive(false)
{
   m_lastTxFrame.clear();
   m_nextRxFrame.clear();
}

MockOwnSocket::~MockOwnSocket()
{
}


void MockOwnSocket::verifyOutgoingData(const char * data)
{
   if (strcmp( m_lastTxFrame, data) != 0)
   {
      throw QString("last TX frame should be: %1, but was %2").
            arg(data).arg(m_lastTxFrame.constData());
   }
}


void MockOwnSocket::makeIncomingData(const char * data)
{
   m_nextRxFrame = data;
   emit readyRead();
}


void MockOwnSocket::connectToHost(const QHostAddress & /*address*/, quint16 /*port*/)
{
   emit connected();
   m_isConnectionActive = true;
}


void MockOwnSocket::disconnectFromHost()
{
   emit disconnected();
   m_isConnectionActive = false;
}


bool MockOwnSocket::isConnectionActive()
{
   return m_isConnectionActive;
}


bool MockOwnSocket::atEnd()
{
   return  m_nextRxFrame.isEmpty();
}


QByteArray MockOwnSocket::readAll()
{
   QByteArray frame = m_nextRxFrame;
   m_nextRxFrame.clear();
   return frame;
}


void MockOwnSocket::write(QByteArray data)
{
   m_lastTxFrame = data;
}


void MockOwnSocket::close()
{
   disconnectFromHost();
}
