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


