#include "tst_CabledNetworkUI.h"

#include <QtTest>

#include "CabledNetworkUI.h"



tst_CabledNetworkUI::tst_CabledNetworkUI(QObject *parent) :
   QObject(parent)
{
}

void tst_CabledNetworkUI::init()
{
   /* each test case builds an object */
   m_cabledNetworkUI = NULL;
}

void tst_CabledNetworkUI::cleanup()
{
   QVERIFY( m_cabledNetworkUI != NULL);
   delete m_cabledNetworkUI;
}

void tst_CabledNetworkUI::testInit()
{
   m_cabledNetworkUI = new CabledNetworkUI("127.0.0.1", 20000);
   QVERIFY( m_cabledNetworkUI != NULL);
}

void tst_CabledNetworkUI::testGetInfo()
{
   m_cabledNetworkUI = new CabledNetworkUI("127.0.0.1", 20000);
   QCOMPARE( m_cabledNetworkUI->getHostIpAddress(), QString("127.0.0.1"));
   QCOMPARE( m_cabledNetworkUI->getPortNumber(), (quint16)20000);
}

void tst_CabledNetworkUI::testGetInfoInvalid()
{
   m_cabledNetworkUI = new CabledNetworkUI("999.0.foo.1", 20000);
   QCOMPARE( m_cabledNetworkUI->getHostIpAddress(), QString("999.0.foo.1"));
}


