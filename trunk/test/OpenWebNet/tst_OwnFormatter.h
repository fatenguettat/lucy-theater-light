#ifndef TST_OWNFORMATTER_H
#define TST_OWNFORMATTER_H

#include <QObject>

class OwnFormatter;

class tst_OwnFormatter : public QObject
{
   Q_OBJECT
public:
   explicit tst_OwnFormatter(QObject *parent = 0);

public slots:
   void init();
   void cleanup();

private Q_SLOTS:
   void testInit();

   void testLight13On();
   void testLight13Off();

   void testLight15Level100();
   void testLight16Level50();
   void testLight17Level20();
   void testLight13Level50slow();
   void testGroup1Level100();
   void testGroup2Level50();
   void testGroup3Level20();
   void testGroup1Level50slow();

   // TODO all tests for negative cases missing


private:
   OwnFormatter *m_formatter;
};

#endif // TST_OWNFORMATTER_H
