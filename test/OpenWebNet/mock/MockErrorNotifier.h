#ifndef MOCKERRORNOTIFIER_H
#define MOCKERRORNOTIFIER_H

#include <QList>
#include <QString>
#include "ErrorNotifier_IF.h"


class MockErrorNotifier : public ErrorNotifier_IF
{
public:
   MockErrorNotifier();
   ~MockErrorNotifier();

   // ErrorNotifier_IF interface
public:
   /**
    * @brief check wether the notification was expected. In negative case,
    *    rise an exception.
    *
    * @param error is the string to be notified
    * @param logType is the severity of the error
    */
   virtual void notifyError(const QString &error, LogType logType);

   /**
    * @brief this implementation does nothing
    */
   virtual void displayAllMessages();

   /**
    * @brief clear last message
    */
   virtual void clear();

   /* mock functions */
   QString lastNotificationMessage() {
      return m_lastErrorMessage;
   }

   LogType lastLogType() {
      return m_lastType;
   }

private:
   QString m_lastErrorMessage;
   LogType m_lastType;
};

#endif // MOCKERRORNOTIFIER_H
