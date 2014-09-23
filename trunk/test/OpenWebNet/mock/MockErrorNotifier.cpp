#include "MockErrorNotifier.h"

MockErrorNotifier::MockErrorNotifier()
{
}

MockErrorNotifier::~MockErrorNotifier()
{
}

void MockErrorNotifier::notifyError(const QString &error, ErrorNotifier_IF::LogType logType)
{
   m_lastErrorMessage = QString(error);
   m_lastType = logType;
}

void MockErrorNotifier::displayAllMessages()
{
}

void MockErrorNotifier::clear()
{
   m_lastErrorMessage = QString();
   m_lastType = ErrorNotifier_IF::SilentLog;
}
