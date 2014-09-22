#ifndef TST_CABLEDNETWORKUI_H
#define TST_CABLEDNETWORKUI_H

#include <QObject>

class CabledNetworkUI;


class tst_CabledNetworkUI : public QObject
{
   Q_OBJECT
public:
   explicit tst_CabledNetworkUI(QObject *parent = 0);

public slots:
   void init();
   void cleanup();

private Q_SLOTS:
   void testInit();
   void testGetInfo();
   void testGetInfoInvalid();

private:
   CabledNetworkUI *m_cabledNetworkUI;

};

#endif // TST_CABLEDNETWORKUI_H
