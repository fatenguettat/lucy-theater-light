#ifndef CABLEDNETWORKUI_H
#define CABLEDNETWORKUI_H

#include <QString>
#include "NetworkUi_IF.h"

/**
 * @brief The CabledNetworkUI class is a degenerated implementation of network UI where
 * actually user can not edit IP address and port, but they are rather passed in constructor
 * and read only.
 *
 * This object is usually created when a plant file is selected, (with router data inside)
 * and is alive as long as that plant file is used
 */
class CabledNetworkUI : public NetworkUi_IF
{
   Q_OBJECT
public:
   /**
    * @brief constructor. No check at all is performed on \p ipAddress \p and port,
    *  either about syntax or about host existing.
    * @param ipAddress is an IPV4 network address
    * @param port is transport layer port number.
    * @param parent is parent object
    */
   CabledNetworkUI( QString ipAddress, quint16 port, QObject *parent = 0);

   // NetworkUi_IF interface
public:
   /**
    * @return cabled IP address
    */
   virtual QString getHostIpAddress();

   /**
    * @return cabled port number
    */
   virtual quint16 getPortNumber();

public slots:
   /** this implementation does nothing */
   virtual void setAsConnected(bool isConnected);

private:
   QString m_ipAddress;
   quint16 m_port;
};

#endif // CABLEDNETWORKUI_H
