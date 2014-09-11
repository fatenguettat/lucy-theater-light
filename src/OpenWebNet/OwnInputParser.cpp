#include "OwnInputParser.h"

#include "configuration.h"

OwnInputParser::OwnInputParser(QObject *parent) :
   QObject(parent)
{
}

void OwnInputParser::onDataReceived(QByteArray inData)
{
   int dataSize = inData.size();

   for (int i=0; i < dataSize; i++)
   {
      char aByte = inData[i];
      m_incomingMessage.append( aByte);

      /* only a # character may determine a complete frame */
      if (aByte == '#')
      {
         checkForCompleteFrame();
      }
   }
}

void OwnInputParser::checkForCompleteFrame()
{
   /* frame is completed if it ends with '##' or if it's too long */
   if (m_incomingMessage.endsWith("##") || (m_incomingMessage.size() >= MAX_MESSAGE_SIZE))
   {
      emit messageComplete( m_incomingMessage);

      m_incomingMessage.clear();
   }
}
