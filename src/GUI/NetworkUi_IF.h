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
   NetworkUi_IF (QObject *parent = 0) : QObject(parent) {}
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
    * @param isConnected: true when connection is established.
    */
   virtual void setAsConnected(bool isConnected) = 0;
};

#endif // NETWORKUI_IF_H
