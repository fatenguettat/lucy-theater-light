#include "MockNetworkUi.h"

MockNetworkUi::MockNetworkUi(QObject *parent) :
   NetworkUi_IF(parent),
   m_isConnected(false)
{
}


QString MockNetworkUi::getHostIpAddress()
{
   return QString();
}

quint16 MockNetworkUi::getPortNumber()
{
   return 0;
}

void MockNetworkUi::setAsConnected(bool isConnected)
{
   m_isConnected = isConnected;
}
