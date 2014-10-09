#ifndef LIGHTPANEL_H
#define LIGHTPANEL_H

#include <QDialog>
#include <QMap>

#include "OwnTypes.h"

namespace Ui {
class LightPanel;
}

class QGraphicsTextItem;
class QGraphicsWidget;
class Slider;
class PrivatePanelIcons;


class LightPanel : public QDialog
{
   Q_OBJECT

public:
   explicit LightPanel(QWidget *parent = 0);
   ~LightPanel();

   /**
    * @brief set the label shown in upper part of panel
    * @param label (html form) should hold info of current light point
    */
   void setHtmlLabel(const QString & label);

signals:
   void requestTurnOn();
   void requestTurnOff();
   void requestSetLevel(own::LIGHT_LEVEL);

private:
   /** translate UI slider values into own levels */
   QMap<int, own::LIGHT_LEVEL> m_sliderToLevelTable;
   QGraphicsTextItem *m_captionItem;
   Slider *m_levelSlider;

   /** parent of all created objects. Kept to delate at the end. */
   QGraphicsWidget *m_root;

   PrivatePanelIcons *m_iconSet;

private slots:
   void onExitButtonClicked();
   void onApplyLevelButtonClicked();

private:
   void initLevelMap();
   QSize choosePanelSize();
};

#endif // LIGHTPANEL_H
