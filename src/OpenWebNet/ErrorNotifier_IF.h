#ifndef ERRORNOTIFIER_IF_H
#define ERRORNOTIFIER_IF_H

class QString;

/**
 * @brief The ErrorNotifier_IF class provides an interface to
 *    treat error messages, (as strings).
 *
 * This file must be GUI independent.
 */
class ErrorNotifier_IF
{
public:
   typedef enum
   {
      /** the message will be shown to user in some way, but interface
       * is not blocked until user acks the message. */
      SilentLog = 0,

      /** this message blocks interface until user proves to have read
       * the message */
      BlockingLog

   } LogType;

public:
   ErrorNotifier_IF() {}
   virtual ~ErrorNotifier_IF() {}

   /**
    * @brief pure virtual function to show an error to user
    *    or log in in some way.
    * @param error is the error message
    * @param logType is the relevance of the message
    */
   virtual void notifyError(const QString & error, LogType logType = SilentLog) = 0;
};

#endif // ERRORNOTIFIER_IF_H
