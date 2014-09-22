#include "CabledNetworkUI.h"

CabledNetworkUI::CabledNetworkUI( QString ipAddress, quint16 port,
                                  QObject *parent) :
   NetworkUi_IF(parent),
   m_ipAddress(ipAddress),
   m_port(port)
{
}


QString CabledNetworkUI::getHostIpAddress()
{
   return m_ipAddress;
}

quint16 CabledNetworkUI::getPortNumber()
{
   return m_port;
}

void CabledNetworkUI::setAsConnected(bool /*isConnected*/)
{
}

