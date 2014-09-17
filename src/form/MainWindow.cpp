#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QGraphicsView>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

#include <QGestureEvent>

#include "PlantParser.h"
#include "PlantLoader.h"
#include "PlantView.h"

#include "QMessageBox"


MainWindow::MainWindow(PlantParser & plantParser, PlantLoader & plantLoader,
                       PlantView & plantView, QWidget *parent) :
   QMainWindow(parent),
   ui(new Ui::MainWindow),
   m_plantLoader(plantLoader),
   m_plantParser(plantParser)
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
   // TODO make apposite class
   QString fileName;

   fileName = QFileDialog::getOpenFileName( NULL, QObject::tr("Open plant file"),
                                            "c:\\", "plant files (*.lux)" );

   if (fileName != QString())
   {
      QFile plantFile(fileName);
      plantFile.open( QIODevice::ReadOnly );

      QTextStream stream( &plantFile);
      const PlantInfo * plantInfo = m_plantParser.parse( stream);

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
      }

      plantFile.close();
   }
}

