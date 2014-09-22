#include "MockNetworkUi.h"

MockNetworkUi::MockNetworkUi(QObject *parent) :
   NetworkUi_IF(parent),
   m_isConnected(false),
   m_hostIp(QString()),
   m_port(0)
{
}


QString MockNetworkUi::getHostIpAddress()
{
   return m_hostIp;
}

quint16 MockNetworkUi::getPortNumber()
{
   return m_port;
}

void MockNetworkUi::setAsConnected(bool isConnected)
{
   m_isConnected = isConnected;
}

void MockNetworkUi::setHostIpAddress(const QString &ipAddress)
{
   m_hostIp = ipAddress;
}

void MockNetworkUi::setPortNumber(quint16 port)
{
   m_port = port;
}
