#include "LightPanel.h"
#include "ui_LightPanel.h"

#include <QCommonStyle>

LightPanel::LightPanel(QWidget *parent) :
   QDialog(parent),
   ui(new Ui::LightPanel)
{
   ui->setupUi(this);

   setWindowFlags(Qt::Tool);
   setWindowTitle(tr("Light Panel"));

   QCommonStyle style;
   ui->applyLevelButton->setIcon( style.standardIcon(QStyle::SP_ArrowRight));
   ui->onButton->setIcon( QPixmap(":/images/images/lightOn.png"));
   ui->offButton->setIcon( QPixmap(":/images/images/lightOff.png"));
   ui->doneButton->setIcon( QPixmap(":/images/images/panelDone.png"));

   initLevelMap();
}

LightPanel::~LightPanel()
{
   delete ui;
}

void LightPanel::on_applyLevelButton_clicked()
{
   own::LIGHT_LEVEL level = m_sliderToLevelTable.value( ui->levelSlider->value(), own::LEVEL_100);
   emit requestSetLevel( level);
}

void LightPanel::on_onButton_clicked()
{
   emit requestTurnOn();
}

void LightPanel::on_offButton_clicked()
{
   emit requestTurnOff();
}

void LightPanel::initLevelMap()
{
   m_sliderToLevelTable.insert(20, own::LEVEL_20);
   m_sliderToLevelTable.insert(30, own::LEVEL_30);
   m_sliderToLevelTable.insert(40, own::LEVEL_40);
   m_sliderToLevelTable.insert(50, own::LEVEL_50);
   m_sliderToLevelTable.insert(60, own::LEVEL_60);
   m_sliderToLevelTable.insert(70, own::LEVEL_70);
   m_sliderToLevelTable.insert(80, own::LEVEL_80);
   m_sliderToLevelTable.insert(90, own::LEVEL_90);
   m_sliderToLevelTable.insert(100, own::LEVEL_100);
}


void LightPanel::on_doneButton_clicked()
{
   done(0);
}
