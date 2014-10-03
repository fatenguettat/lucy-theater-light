#ifndef LIGHTPANEL_H
#define LIGHTPANEL_H

#include <QDialog>
#include <QMap>

#include "OwnConstants.h"

namespace Ui {
class LightPanel;
}

class LightPanel : public QDialog
{
   Q_OBJECT

public:
   explicit LightPanel(QWidget *parent = 0);
   ~LightPanel();

signals:
   void requestTurnOn();
   void requestTurnOff();
   void requestSetLevel(own::LIGHT_LEVEL);

private slots:
   void on_applyLevelButton_clicked();
   void on_onButton_clicked();
   void on_offButton_clicked();
   void on_doneButton_clicked();

private:
   Ui::LightPanel *ui;
   /** translate UI slider values into own levels */
   QMap<int, own::LIGHT_LEVEL> m_sliderToLevelTable;

private:
   void initLevelMap();
};

#endif // LIGHTPANEL_H
