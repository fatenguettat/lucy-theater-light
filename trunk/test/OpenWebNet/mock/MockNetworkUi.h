#ifndef MOCKNETWORKUI_H
#define MOCKNETWORKUI_H

#include <QObject>
#include "NetworkUi_IF.h"


class MockNetworkUi : public NetworkUi_IF
{
   Q_OBJECT
public:
   explicit MockNetworkUi(QObject *parent = 0);

   // NetworkUi_IF interface
public:
   virtual QString getHostIpAddress();
   virtual quint16 getPortNumber();

public slots:
   virtual void setAsConnected(bool isConnected);

   // Mock functions
   void setHostIpAddress(const QString & ipAddress);
   void setPortNumber( quint16 port);

private:
   bool m_isConnected;
   QString m_hostIp;
   quint16 m_port;
};

#endif // MOCKNETWORKUI_H
