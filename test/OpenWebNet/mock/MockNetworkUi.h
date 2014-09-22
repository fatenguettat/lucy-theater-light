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

private:
   bool m_isConnected;
};

#endif // MOCKNETWORKUI_H
