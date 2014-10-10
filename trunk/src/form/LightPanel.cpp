#include "LightPanel.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsTextItem>
#include <QGraphicsGridLayout>
#include <QGridLayout>
#include <QPixmap>
#include <QApplication>
#include <QDesktopWidget>

#include "Button.h"
#include "Slider.h"
#include "testableAssert.h"


/** helper structured class to hold paths of icons */
class PrivatePanelIcons
{
public:
   PrivatePanelIcons():
      exitIconPath(":/images/images/panelDone.png"),
      onIconPath(":/images/images/lightOn.png"),
      offIconPath(":/images/images/lightOff.png"),
      applyLevelIconPath(":/images/images/apply.png")
   {
   }

   ~PrivatePanelIcons() {}

   QString exitIconPath;
   QString onIconPath;
   QString offIconPath;
   QString applyLevelIconPath;
};


LightPanel::LightPanel(QWidget *parent) :
   QDialog(parent),
   m_iconSet(new PrivatePanelIcons)
{
   T_ASSERT( parent != NULL);

   setWindowFlags(Qt::ToolTip);
   setWindowTitle(tr("Light Panel"));

   QSize size = choosePanelSize();

   QGraphicsScene *scene = new QGraphicsScene( 0, 0, size.width() / 2,
                                               size.height() / 2);
   QGraphicsView *view = new QGraphicsView( scene, this);

   this->setLayout(new QGridLayout(this));
   this->layout()->addWidget( view);

   m_root = new QGraphicsWidget(NULL);

   QGraphicsWidget *captionBox = new QGraphicsWidget(m_root);
   m_captionItem = new QGraphicsTextItem(captionBox);
   m_captionItem->setFont(QFont("MS Sans", 15));
   m_levelSlider = new Slider( own::LEVEL_20, 9, 1, m_root);

   QPixmap *exitIcon = new QPixmap(m_iconSet->exitIconPath);
   QPixmap *onIcon = new QPixmap(m_iconSet->onIconPath);
   QPixmap *offIcon = new QPixmap(m_iconSet->offIconPath);
   QPixmap *applyLevelIcon = new QPixmap(m_iconSet->applyLevelIconPath);

   Button *exitButton = new Button(m_root);
   Button *onButton = new Button(m_root);
   Button *offButton = new Button(m_root);
   Button *applyLevelButton = new Button(m_root);

   exitButton->setDefaultIcon( exitIcon);
   onButton->setDefaultIcon( onIcon);
   offButton->setDefaultIcon( offIcon);
   applyLevelButton->setDefaultIcon( applyLevelIcon);

   scene->addItem(captionBox);
   scene->addItem(m_levelSlider);
   scene->addItem(exitButton);
   scene->addItem(onButton);
   scene->addItem(offButton);
   scene->addItem(applyLevelButton);

   exitButton->setSize( size.height()/7);
   onButton->setSize( size.height()/7);
   offButton->setSize( size.height()/7);
   applyLevelButton->setSize( size.height()/7);

   QGraphicsGridLayout *layout = new QGraphicsGridLayout;
   layout->addItem(captionBox, 0, 0, 1, 3);
   layout->addItem(exitButton, 0, 3, 1, 1);
   layout->addItem(m_levelSlider, 1, 0, 1, 3);
   layout->addItem(applyLevelButton, 1, 3, 1, 1);
   layout->addItem(onButton, 2, 1, 1, 1);
   layout->addItem(offButton, 2, 2, 1, 1);

   QGraphicsWidget *form = new QGraphicsWidget(m_root);
   form->setGeometry( scene->sceneRect());
   form->setLayout(layout);
   scene->addItem(form);

   connect (exitButton, SIGNAL(hit()), this, SLOT(onExitButtonClicked()) );
   connect (onButton, SIGNAL(hit()), this, SIGNAL(requestTurnOn()) );
   connect (offButton, SIGNAL(hit()), this, SIGNAL(requestTurnOff()) );
   connect (applyLevelButton, SIGNAL(hit()), this, SLOT(onApplyLevelButtonClicked()) );

}

LightPanel::~LightPanel()
{
   delete m_root;
}

QSize LightPanel::choosePanelSize()
{
   QSize size = QApplication::desktop()->size();

   if (size.width() > 700)
   {
      size.setWidth(700);
   }

   if (size.height() > 500)
   {
      size.setHeight(500);
   }

   return size;
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
   emit requestSetLevel( (own::LIGHT_LEVEL)m_levelSlider->value());
}


