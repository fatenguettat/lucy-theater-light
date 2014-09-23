#ifndef ERRORNOTIFIERQT_H
#define ERRORNOTIFIERQT_H

#include "ErrorNotifier_IF.h"
#include "QStringList"

class QWidget;


/**
 * @brief The ErrorNotifierQt class implements a notification system tought
 *  not to disturb user that is not highly skilled with technical details,
 *  but allows the view of all logs, if desired.
 *
 * Blocking messages are implemented by usual message box.
 * All messages are stored in an inetrnal list that can be retrieved by user
 * when required, to be shown in a custom viewer.
 */
class ErrorNotifierQt : public ErrorNotifier_IF
{
public:
   ErrorNotifierQt( QWidget *parent);
   ~ErrorNotifierQt();

   // ErrorNotifier_IF interface
public:
   virtual void notifyError(const QString &error, LogType logType);

   /**
    * @brief show all messages in a cutom viewer
    */
   virtual void displayAllMessages();

   /** @brief remove all messages */
   virtual void clear();

   // constants
private:
   /** Max number of messages shown in viewer. If more are notified,
    * older messages are deleted. */
   static const int MAX_MESSAGES_SHOWN = 300;

private:
   /** reference window to display message boxes */
   QWidget *m_parentWindow;

   /** list of all messages (if they are too many,
    * oler are deleted) */
   QStringList m_messageList;
};

#endif // ERRORNOTIFIERQT_H
