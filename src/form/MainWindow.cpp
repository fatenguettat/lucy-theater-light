#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QGraphicsView>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QTranslator>
#include <QMessageBox>

#include "PlantParser.h"
#include "PlantLoader.h"
#include "PlantView.h"
#include "PlantInfo.h"

#include "PlantFactory.h"
#include "OwnEngine.h"
#include "GuiInterface_IF.h"

#include "ErrorNotifier_IF.h"
#include "ApplicationSettings.h"
#include "OwnConstants.h"

// TODO would be nice not to have plant factory here and delegate all to a specific class



MainWindow::MainWindow(PlantParser & plantParser, PlantLoader & plantLoader,
                       PlantView & plantView, PlantFactory & plantFactory,
                       ApplicationSettings &settings,
                       ErrorNotifier_IF &errorNotifier, QWidget *parent) :
   QMainWindow(parent),
   ui(new Ui::MainWindow),
   m_translator(new QTranslator(this)),
   m_plantLoader(plantLoader),
   m_plantParser(plantParser),
   m_plantFactory(plantFactory),
   m_settings(settings),
   m_messageLogger(errorNotifier),
   m_ownEngine(NULL),
   m_guiInterface(NULL)
{
   ui->setupUi(this);
   setCentralWidget( &plantView);

   /* these actions only apply when a plant is loaded */
   ui->action_Shut_everything_off->setEnabled( false);
   ui->action_Check_light_status->setEnabled( false);

   connect( &plantLoader, SIGNAL(plantLoaded(bool)),
            this, SLOT(onPlantLoaded(bool)) );

   qApp->installTranslator(m_translator);
   loadApplicationLanguage();
}

MainWindow::~MainWindow()
{
   delete ui;
}


void MainWindow::showEvent(QShowEvent *event)
{
   QMainWindow::showEvent( event);

   /* This seems to be the only way to open a plant on startup.
    * It is not really good */
   static bool firstTime = true;

   if (firstTime)
   {
      firstTime = false;

      /* On startup, load default plant */
      openPlantFile(":/defaultPlant/defaultPlant/defaultPlant.lux");
   }
}


void MainWindow::on_action_open_plant_file_triggered()
{
   QString fileName;
   QString defaultPath = QFileInfo( m_settings.getLastPlantPath()).absolutePath();

   fileName = QFileDialog::getOpenFileName( NULL, QObject::tr("Open plant file"),
                                            defaultPath, "plant files (*.lux)" );

   if (fileName != QString())
   {
      bool plantOpen;
      plantOpen = openPlantFile(fileName);

      if (plantOpen)
      {
         m_settings.setLastPlantPath( fileName);
      }
   }
}


void MainWindow::on_action_re_open_last_plant_triggered()
{
   QString lastPlant = m_settings.getLastPlantPath();
   bool loaded = false;

   if (lastPlant != QString())
   {
      loaded = openPlantFile(lastPlant);
   }

   if (lastPlant == QString() || (! loaded))
   {
      QMessageBox::warning( this, tr("can not re-open"),
                            tr("There is no plant in history.\nPlease select one."));
   }
}

bool MainWindow::openPlantFile( const QString & fileName)
{
   // TODO make apposite class
   bool loaded = false;
   QFile plantFile(fileName);
   plantFile.open( QIODevice::ReadOnly );

   QTextStream stream( &plantFile);
   const PlantInfo * plantInfo = m_plantParser.parse( stream);

   /* in case of any error, do not open plant file */
   if (m_plantParser.getErrors().size() > 0)
   {
      /* do not confuse symbol '<' with HTML tag */
      m_plantParser.getErrors().replaceInStrings("<", "&lt;");

      QMessageBox::warning( this,
                            tr("plant file errors"),
                            tr("<b>The following errors have been found in file:</b><br> %1<br><br>").
                            arg(fileName) + "<ul><li>" +
                            m_plantParser.getErrors().join("</li><li>") + "</ul>" +
                            tr("\n\nplease check file and reload"));
   }
   else
   {
      if (m_guiInterface)
      {
         m_plantFactory.destroyGuiInterface(m_guiInterface);
      }

      if (m_ownEngine)
      {
         m_plantFactory.destroyOwnEngine( m_ownEngine);
      }

      m_ownEngine = m_plantFactory.buildOwnEngine( *plantInfo);
      m_guiInterface = m_plantFactory.buildGuiInterafce( m_ownEngine);

      m_plantLoader.load( *plantInfo, m_guiInterface, m_ownEngine);
      loaded = true;
   }

   plantFile.close();

   return loaded;
}


void MainWindow::on_actionView_log_triggered()
{
   m_messageLogger.displayAllMessages();
}


void MainWindow::on_action_Shut_everything_off_triggered()
{
   if (m_ownEngine)
   {
      m_ownEngine->lightPointRequestOff( own::GLOBAL_WHERE);
   }
}


void MainWindow::on_action_Check_light_status_triggered()
{
   if (m_ownEngine)
   {
      m_ownEngine->lightPointProbeStatus( own::GLOBAL_WHERE);
   }
}


void MainWindow::loadApplicationLanguage()
{
   ApplicationSettings::Language storedLanguage;
   storedLanguage = m_settings.language();
   bool isLocaleSelected = (storedLanguage == ApplicationSettings::LOCALE);

   ui->action_Locale->setChecked( isLocaleSelected);
   on_action_Locale_triggered( isLocaleSelected);
}


void MainWindow::on_action_Locale_triggered(bool checked)
{
   if( checked )
   {
      // retranslate to local language
      m_translator->load( "lucy_it", ":/translations/translations" );
      m_settings.setLanguage( ApplicationSettings::LOCALE);
   }
   else
   {
      // retranslate to native language.
      m_translator->load( QString(), QString() );
      m_settings.setLanguage( ApplicationSettings::NATIVE);
   }

   ui->retranslateUi( this );
}

void MainWindow::onPlantLoaded(bool loadOk)
{
   ui->action_Shut_everything_off->setEnabled( loadOk);
   ui->action_Check_light_status->setEnabled( loadOk);

   if (!loadOk)
   {
      m_ownEngine = NULL;
   }
}

