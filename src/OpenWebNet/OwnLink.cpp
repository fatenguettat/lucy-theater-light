#include "OwnLink.h"

#include <QHostAddress>

#include "OwnSocketTcp.h"
#include "OwnConstants.h"
#include "NetworkUi_IF.h"
#include "OwnInputParser.h"

#include "ErrorNotifier_IF.h"


OwnLink::OwnLink(NetworkUi_IF &networkUi,
                 OwnSocket_IF &socket,
                 OwnInputParser &inputParser,
                 ErrorNotifier_IF &logger,
                 QObject *parent) :
   QObject(parent),
   m_socket(socket),
   m_networkUi(networkUi),
   m_inputParser(inputParser),
   m_logger(logger)
{
   connect( &m_socket, SIGNAL(connected()),this, SLOT(onSocketConnected()));
   connect( &m_socket, SIGNAL(disconnected()),this, SLOT(onSocketDisconnected()));
   connect( &m_socket, SIGNAL(bytesWritten(qint64)),this, SLOT(onBytesWritten(qint64)));
   connect( &m_socket, SIGNAL(readyRead()),this, SLOT(onReadyRead()));
   connect( &m_socket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(onSocketError(QAbstractSocket::SocketError)) );

   connect( &m_inputParser, SIGNAL(messageComplete(QString)),
            this, SLOT(onOwnMessageReceived(QString)) );
}


void OwnLink::triggerSendMessage(QString &message)
{
   QStringList list = QStringList(message);
   triggerSendMessageList( list);
}


void OwnLink::triggerSendMessageList(QStringList & messages)
{
   QString ipAddress = m_networkUi.getHostIpAddress();
   int port = m_networkUi.getPortNumber();

   m_outputBuffer.append( own::COMMAND_SESSION_STRING);
   m_outputBuffer.append( messages);

   m_logger.notifyError( QString("connecting to %1 - port: %2").
                         arg(ipAddress).arg(port));
   m_socket.connectToHost( QHostAddress(ipAddress), port);
}


void OwnLink::onSocketConnected()
{
   m_logger.notifyError( "socket connected");

   /* now just wait for ack from server */
}


void OwnLink::onSocketDisconnected()
{
   m_logger.notifyError( "socket disconnected");
}


void OwnLink::onBytesWritten(qint64 numBytes)
{
   m_logger.notifyError( QString("written %1 bytes").arg(numBytes));
}


void OwnLink::onReadyRead()
{
   m_logger.notifyError("data available");

   while (! m_socket.atEnd())
   {
      m_inputParser.onDataReceived( m_socket.readAll());
   }
}


void OwnLink::onSocketError( QAbstractSocket::SocketError errCode)
{
   m_logger.notifyError( QString("Socket error: %1").arg(errCode));

   /* reset socket */
   m_socket.close();
}


void OwnLink::onOwnMessageReceived(QString message)
{
   m_logger.notifyError( QString("RX MSG: %1").arg(message));

   if (message == own::ACK_STRING)
   {
      sendNextMessage();
   }
   else
   {
      m_logger.notifyError( QString("received unexpected message: %1").arg(message));
   }
}


void OwnLink::sendNextMessage()
{
   if (! m_outputBuffer.isEmpty())
   {
      /* send oldest and pop it */
      QByteArray outMessage = m_outputBuffer.first().toLatin1();
      m_logger.notifyError( QString("sending: %1").arg(outMessage.constData()) );
      m_socket.write( outMessage);
      m_outputBuffer.removeFirst();
   }
   else
   {
      m_logger.notifyError("All strings sent. Disconnecting ... ");
      m_socket.disconnectFromHost();

      emit sequenceComplete();
   }
}
