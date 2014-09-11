#ifndef OWNINPUTPARSER_H
#define OWNINPUTPARSER_H

#include <QObject>

/**
 * @brief The OwnInputParser class reads a stream of characters
 * one by one, and emits a message when a message is complete.
 */
class OwnInputParser : public QObject
{
   Q_OBJECT
public:
   explicit OwnInputParser(QObject *parent = 0);

   /**
    * @brief called when a number of bytes have been received
    *
    * @param inData is an array of bytes
    */
   void onDataReceived(QByteArray inData);

signals:
   /**
    * @brief emitted when a complete OWN message has been received.
    *
    * @param message is the OWN message received
    */
   void messageComplete(const QString & message);

private:
   /** cat of incoming bytes to build up an OWN message */
   QString m_incomingMessage;

private:
   /**
    * @brief if \p m_incomingMessage ends with '##', emits
    * a signal for message complete.
    */
   void checkForCompleteFrame();

};

#endif // OWNINPUTPARSER_H
