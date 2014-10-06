#include "LightPanel.h"

//#include <QCommonStyle>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <QGraphicsGridLayout>
#include <QGridLayout>

#include "Button.h"
#include "Slider.h"


LightPanel::LightPanel(QWidget *parent) :
   QDialog(parent)
{
   // TODO !!!!   qui non va bene un cazzo.
   //    Gli oggetti creati vanno distrutti correttamente.
   setWindowFlags(Qt::ToolTip);
   setWindowTitle(tr("Light Panel"));

   QGraphicsScene *scene = new QGraphicsScene( 0, 0, 400., 300.);
   QGraphicsView *view = new QGraphicsView( scene, this);

   this->setLayout(new QGridLayout(this));
   this->layout()->addWidget( view);

   QGraphicsWidget *captionBox = new QGraphicsWidget(NULL);
   m_captionItem = new QGraphicsTextItem(captionBox);
   Slider *levelSlider = new Slider(NULL);
   Button *exitButton = new Button(NULL);
   Button *onButton = new Button(NULL);
   Button *offButton = new Button(NULL);
   Button *applyLevelButton = new Button(NULL);
   scene->addItem(captionBox);
   scene->addItem(levelSlider);
   scene->addItem(exitButton);
   scene->addItem(onButton);
   scene->addItem(offButton);
   scene->addItem(applyLevelButton);

   setHtmlLabel("<h1>ciao</h1><h2>ciao</h2><h3>ciao</h3>");

   QGraphicsGridLayout *layout = new QGraphicsGridLayout;
   layout->addItem(captionBox, 0, 0, 1, 3);
   layout->addItem(exitButton, 1, 0, 1, 1);
   layout->addItem(onButton, 1, 1, 1, 1);
   layout->addItem(offButton, 2, 0, 1, 1);
   layout->addItem(applyLevelButton, 2, 1, 1, 1);
   layout->addItem(levelSlider, 3, 0, 1, 3);

   QGraphicsWidget *form = new QGraphicsWidget;
   form->setLayout(layout);
   scene->addItem(form);

   connect (exitButton, SIGNAL(hit()), this, SLOT(onExitButtonClicked()) );
   connect (onButton, SIGNAL(hit()), this, SIGNAL(requestTurnOn()) );
   connect (offButton, SIGNAL(hit()), this, SIGNAL(requestTurnOff()) );
   connect (applyLevelButton, SIGNAL(hit()), this, SLOT(onApplyLevelButtonClicked()) );

   initLevelMap();
}

LightPanel::~LightPanel()
{
   //   delete ui;
}

void LightPanel::setHtmlLabel(const QString &label)
{
   m_captionItem->setHtml(label);
}

void LightPanel::onExitButtonClicked()
{
   done(0);
}

void LightPanel::onApplyLevelButtonClicked()
{
   // TODO read value from slider and send it
   own::LIGHT_LEVEL level = own::LEVEL_30;
   emit requestSetLevel( level);
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

