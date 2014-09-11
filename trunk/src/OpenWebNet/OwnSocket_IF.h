#ifndef OWNSOCKET_IF_H
#define OWNSOCKET_IF_H

#include <QObject>
#include <QAbstractSocket>

class OwnSocket_IF : public QObject
{
   Q_OBJECT
public:
   explicit OwnSocket_IF(QObject *parent = 0) : QObject(parent) {}

   virtual void connectToHost(const QHostAddress &address, quint16 port) = 0;
   virtual void disconnectFromHost() = 0;
   virtual bool atEnd() = 0;
   virtual QByteArray readAll() = 0;
   virtual void write( QByteArray data) = 0;
   virtual void close() = 0;

signals:
   void connected();
   void disconnected();
   void bytesWritten(qint64);
   void readyRead();
   void error(QAbstractSocket::SocketError);

};

#endif // OWNSOCKET_IF_H
