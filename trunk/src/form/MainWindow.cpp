#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QGraphicsView>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>


#include "PlantParser.h"
#include "PlantLoader.h"
#include "PlantView.h"
#include "PlantInfo.h"
#include "ErrorNotifier_IF.h"
#include "ApplicationSettings.h"

#include "QMessageBox"


MainWindow::MainWindow(PlantParser & plantParser, PlantLoader & plantLoader,
                       PlantView & plantView, ApplicationSettings &settings,
                       ErrorNotifier_IF &errorNotifier, QWidget *parent) :
   QMainWindow(parent),
   ui(new Ui::MainWindow),
   m_plantLoader(plantLoader),
   m_plantParser(plantParser),
   m_settings(settings),
   m_messageLogger(errorNotifier)
{
   ui->setupUi(this);
   setCentralWidget( &plantView);
}

MainWindow::~MainWindow()
{
   delete ui;
}


void MainWindow::on_action_open_plant_file_triggered()
{
   QString fileName;
   QString defaultPath = QFileInfo( m_settings.getLastPlantPath()).absolutePath();

   fileName = QFileDialog::getOpenFileName( NULL, QObject::tr("Open plant file"),
                                            defaultPath, "plant files (*.lux)" );

   if (fileName != QString())
   {
      openPlantFile(fileName);
   }
}


void MainWindow::on_action_re_open_last_plant_triggered()
{
   QString lastPlant = m_settings.getLastPlantPath();

   if (lastPlant != QString())
   {
      openPlantFile(lastPlant);
   }
   else
   {
      QMessageBox::warning( this, tr("can not re-open"),
                            tr("There is no plant in history.\nPlease select one."));
   }
}

void MainWindow::openPlantFile( const QString & fileName)
{
   // TODO make apposite class
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
      m_plantLoader.load( *plantInfo);
      m_settings.setLastPlantPath( fileName);
   }

   plantFile.close();
}

void MainWindow::on_actionView_log_triggered()
{
    m_messageLogger.displayAllMessages();
}
