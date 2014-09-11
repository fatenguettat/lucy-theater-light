#ifndef OWNLINK_H
#define OWNLINK_H

#include <QObject>
#include <QAbstractSocket>
#include <QStringList>

class OwnSocket_IF;
class NetworkUi_IF;
class OwnInputParser;
class ErrorNotifier_IF;

class OwnLink : public QObject
{
   Q_OBJECT
public:
   explicit OwnLink( NetworkUi_IF & networkUi, OwnSocket_IF &socket,
                     OwnInputParser & inputParser, ErrorNotifier_IF &logger,
                     QObject *parent = 0);

   /**
    * @brief start the sequence to send a OWN \p message over network
    * @param message is the pure OWN string
    */
   void triggerSendMessage( QString &message);

   /**
    * @brief start the sequence to send a list of OWN \p messages over network
    * @param messages is a list of pure OWN strings
    */
   void triggerSendMessageList( QStringList &messages);

signals:
   /**
    * @brief emitted when the sequence to send one or more messages has been completed.
    *   If \a triggerSendMessageList was called, this signal is emitted when all messages
    *   have been sent.
    */
   void messageSent();

   /**
    * @brief emitted when a message that is not managed internally is received
    *    from network. It does not apply to ACK for sent messages.
    */
   void messageReceived();

   /**
    * @brief emitted when the protocol to send a message did not complete, or a
    *    network error occurred.
    */
   void error();

private:
   OwnSocket_IF & m_socket;
   NetworkUi_IF & m_networkUi;
   OwnInputParser & m_inputParser;
   ErrorNotifier_IF & m_logger;

   /**
    * @brief this is where all string that must be sent are parked
    */
   QStringList m_outputBuffer;

private slots:
   void onSocketConnected();
   void onSocketDisconnected();
   void onBytesWritten(qint64);
   void onReadyRead();
   void onSocketError(QAbstractSocket::SocketError errCode);
   void onOwnMessageReceived(QString message);

private:
   void sendNextMessage();
};

#endif // OWNLINK_H
