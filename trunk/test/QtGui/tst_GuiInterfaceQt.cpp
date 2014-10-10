#include <QString>
#include <QtTest>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QCoreApplication>

#include "GuiInterfaceQt.h"
#include "OwnEngine.h"

#include "MockNetworkUi.h"
#include "MockOwnSocket.h"
#include "OwnInputParser.h"
#include "MockErrorNotifier.h"
#include "OwnLink.h"
#include "OwnFormatter.h"
#include "LightPoint.h"
#include "LightGroup.h"
#include "MockLightPanel.h"


class QtGuiTest : public QObject
{
   Q_OBJECT

public:
   QtGuiTest();

private slots:
   void init();
   void cleanup();

private Q_SLOTS:
   void testInit();
   void testLinkEngineGui();
   void testLinkGuiEngineOn();
   void testLinkGroup();

private:
   QGraphicsScene *m_scene;
   QGraphicsView *m_view;
   MockNetworkUi *m_network;
   MockOwnSocket *m_socket;
   OwnInputParser *m_parser;
   MockErrorNotifier *m_errorNotifier;
   OwnLink *m_ownLink;
   OwnFormatter *m_formatter;
   OwnEngine *m_ownEngine;
   MockLightPanel *m_panel;

   GuiInterfaceQt *m_gui;
};

Q_DECLARE_METATYPE(own::Where)

QtGuiTest::QtGuiTest()
{
   qRegisterMetaType<own::Where>("own::Where");
}


void QtGuiTest::init()
{
   m_scene = new QGraphicsScene();
   m_view = new QGraphicsView( m_scene);

   m_network = new MockNetworkUi( this);
   m_socket = new MockOwnSocket();
   m_parser = new OwnInputParser(this);
   m_errorNotifier = new MockErrorNotifier();
   m_ownLink = new OwnLink( *m_network, *m_socket,
                            *m_parser, *m_errorNotifier, this);
   m_formatter = new OwnFormatter();
   m_ownEngine = new OwnEngine( *m_network, *m_ownLink, *m_formatter);

   m_panel = new MockLightPanel(m_view);

   m_gui = new GuiInterfaceQt( *m_ownEngine, *m_scene, *m_view, *m_panel);
}

void QtGuiTest::cleanup()
{
   delete m_gui;
   delete m_panel;
   delete m_ownEngine;
   delete m_formatter;
   delete m_ownLink;
   delete m_errorNotifier;
   delete m_parser;
   delete m_socket;
   delete m_network;
   delete m_view;
   delete m_scene;
}

void QtGuiTest::testInit()
{
   QVERIFY( m_gui != NULL);
}


void QtGuiTest::testLinkEngineGui()
{
   LightPoint point("light 1", QPointF(0.1,0.1), "11");

   m_ownEngine->addLightPoint( point);

   try
   {
      /* if GUI received the notification of the new light,
       * no exception will be thrown. */
      m_gui->showAsTurnedOn( "11");
   }
   catch( QString & err)
   {
      QFAIL(err.toLatin1());
   }
}


void QtGuiTest::testLinkGuiEngineOn()
{
   try
   {
      QSignalSpy turnOnReqSpy( m_ownEngine, SIGNAL(lightOnRequestStarted(own::Where)) );

      LightPoint point("light 1", QPointF(0.1,0.1), "11");
      m_ownEngine->addLightPoint( point);

      m_panel->mockArmAction( MockLightPanel::ACTION_PUSH_ON);

      /* user presses light 11 button */
      m_gui->onLightButtonPressed( "11");

      QCOMPARE( turnOnReqSpy.size(), 1);
      QCOMPARE( turnOnReqSpy.at(0).at(0).toString(), QString("11"));
   }
   catch (QString &err)
   {
      QFAIL(err.toLatin1());
   }
}

void QtGuiTest::testLinkGroup()
{
   try
   {
      QSignalSpy turnOnReqSpy( m_ownEngine, SIGNAL(lightOnRequestStarted(own::Where)) );

      LightPoint node("group 1", QPointF(0.1,0.1), "#1");
      LightGroup group( node, QList<own::Where>() << "11" << "12" << "13");

      m_ownEngine->addLightGroup( group);
      m_panel->mockArmAction( MockLightPanel::ACTION_PUSH_ON);

      /* user presses light 11 button */
      m_gui->onLightButtonPressed( "#1");

      QCOMPARE( turnOnReqSpy.size(), 1);
      QCOMPARE( turnOnReqSpy.at(0).at(0).toString(), QString("#1"));
   }
   catch (QString &err)
   {
      QFAIL(err.toLatin1());
   }
}


QTEST_MAIN(QtGuiTest)

#include "tst_GuiInterfaceQt.moc"
