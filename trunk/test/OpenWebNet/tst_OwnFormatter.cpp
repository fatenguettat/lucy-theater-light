#include "tst_OwnFormatter.h"

#include <QtTest>

#include "OwnFormatter.h"

tst_OwnFormatter::tst_OwnFormatter(QObject *parent) :
   QObject(parent)
{
}

void tst_OwnFormatter::init()
{
   m_formatter = new OwnFormatter();
}

void tst_OwnFormatter::cleanup()
{
   delete m_formatter;
   m_formatter = NULL;
}

void tst_OwnFormatter::testInit()
{
   QVERIFY (m_formatter != NULL);
}

void tst_OwnFormatter::testLight13On()
{
   QString format = m_formatter->lightOn( 13);
   QCOMPARE( format, QString("*1*1*13##"));
}

void tst_OwnFormatter::testLight13Off()
{
   QString format = m_formatter->lightOff( 13);
   QCOMPARE( format, QString("*1*0*13##"));
}

void tst_OwnFormatter::testLight15Level100()
{
   QString format = m_formatter->lightLevel( 15, OwnFormatter::LEVEL_100);
   QCOMPARE( format, QString("*1*10*15##"));
}

void tst_OwnFormatter::testLight16Level50()
{
   QString format = m_formatter->lightLevel( 16, OwnFormatter::LEVEL_50);
   QCOMPARE( format, QString("*1*5*16##"));
}

void tst_OwnFormatter::testLight17Level20()
{
   QString format = m_formatter->lightLevel( 17, OwnFormatter::LEVEL_20);
   QCOMPARE( format, QString("*1*2*17##"));
}

void tst_OwnFormatter::testLight13Level50slow()
{
   QString format = m_formatter->lightLevelSlow( 13, OwnFormatter::LEVEL_50);
   QCOMPARE( format, QString("*1*5#3*13##"));
}

void tst_OwnFormatter::testGroup1Level100()
{
   QString format = m_formatter->lightLevelGroup( 1, OwnFormatter::LEVEL_100);
   QCOMPARE( format, QString("*1*10*#1##"));
}

void tst_OwnFormatter::testGroup2Level50()
{
   QString format = m_formatter->lightLevelGroup( 2, OwnFormatter::LEVEL_50);
   QCOMPARE( format, QString("*1*5*#2##"));
}

void tst_OwnFormatter::testGroup3Level20()
{
   QString format = m_formatter->lightLevelGroup( 3, OwnFormatter::LEVEL_20);
   QCOMPARE( format, QString("*1*2*#3##"));
}

void tst_OwnFormatter::testGroup1Level50slow()
{
   QString format = m_formatter->lightLevelGroupSlow( 1, OwnFormatter::LEVEL_50);
   QCOMPARE( format, QString("*1*5#3*#1##"));
}



