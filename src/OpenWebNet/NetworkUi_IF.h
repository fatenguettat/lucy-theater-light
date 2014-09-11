#ifndef NETWORKUI_IF_H
#define NETWORKUI_IF_H

#include <QObject>

/**
 * @brief The NetworkUi_IF class is a virtual class that exports methods
 * needed by underling logic to use a GUI control that selects a host on Network
 * (and check it's existence).
 *
 * This function is UI independent and can be compiled for unit tests.
 */
class NetworkUi_IF : public QObject
{
   Q_OBJECT
public:
   NetworkUi_IF (QObject *parent) : QObject(parent) {}
   virtual ~NetworkUi_IF () {}

public:
   /**
    * @return a string with host address (IPv4) edited by user.
    * There is absolutely no guarantee that user wrote a legal IP address,
    * (and less guarantee that such IP address is present on the network).
    */
   virtual QString getHostIpAddress() = 0;

   /**
    * @return the number of UDP port that will be used for transmission.
    */
   virtual quint16 getPortNumber() = 0;

public slots:
   /**
    * @brief enable/disable some UI widgets according to connection state
    * @param isConnected: if true, IP address can be edited and bound; when
    *    false, controls are disabled.
    */
   virtual void setAsConnected(bool isConnected) = 0;

signals:
   /**
    * @brief user requests to bind the socket to IP address
    *    edited in GUI.
    * @param ipAddress is in V4 format. It may be an illegal address
    *    or not referred to a reachable machine.
    */
   void bindRequest( const QString & ipAddress);
};

#endif // NETWORKUI_IF_H
