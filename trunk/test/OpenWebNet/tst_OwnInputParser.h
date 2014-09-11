#ifndef TST_OWNINPUTPARSER_H
#define TST_OWNINPUTPARSER_H

#include <QObject>

class OwnInputParser;



class tst_OwnInputParser : public QObject
{
   Q_OBJECT
public:
   explicit tst_OwnInputParser(QObject *parent = 0);

public slots:
   void init();
   void cleanup();

private Q_SLOTS:
   void testInit();
   void testFullMessage();
   void testUncompleteMessage();
   void testSplitInTwo();
   void testTwoMessagesInOneCall();
   void testOverlappingMessages();
   void testIllegalSymbols();

private:
   OwnInputParser *m_parser;
};

#endif // TST_OWNINPUTPARSER_H
