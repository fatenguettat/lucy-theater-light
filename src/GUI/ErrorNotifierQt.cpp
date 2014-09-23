#include "ErrorNotifierQt.h"

#include <QMessageBox>

#include "MessageViewer.h"

ErrorNotifierQt::ErrorNotifierQt(QWidget *parent) :
   m_parentWindow(parent)
{
}

ErrorNotifierQt::~ErrorNotifierQt()
{
   m_messageList.clear();
}


void ErrorNotifierQt::notifyError(const QString &error, ErrorNotifier_IF::LogType logType)
{
   if (logType == BlockingLog)
   {
      QMessageBox::warning( m_parentWindow, QObject::tr("application warning"), error);
   }

   /* append error to list in any case. Check for message list size */
   m_messageList.append( error);

   if (m_messageList.size() > MAX_MESSAGES_SHOWN)
   {
      m_messageList.removeFirst();
   }
}

void ErrorNotifierQt::displayAllMessages()
{
   /* show messages in a big modal, copy-able window */
   MessageViewer viewer( m_messageList, m_parentWindow);
   viewer.setWindowState(Qt::WindowMaximized);

   viewer.exec();
}

void ErrorNotifierQt::clear()
{
   m_messageList.clear();
}


