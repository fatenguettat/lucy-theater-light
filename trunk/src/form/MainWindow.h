#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QGraphicsView;
class QTranslator;

class PlantLoader;
class PlantParser;
class PlantFactory;
class PlantView;
class ApplicationSettings;
class ErrorNotifier_IF;
class OwnEngine;
class GuiInterface_IF;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
   Q_OBJECT

public:
   explicit MainWindow(PlantParser &plantParser, PlantLoader & plantLoader,
                       PlantView &plantView, PlantFactory &plantFactory,
                       ApplicationSettings & settings,
                       ErrorNotifier_IF &errorNotifier, QWidget *parent = 0);
   ~MainWindow();

   // QWidget interface
protected:
   virtual void showEvent(QShowEvent *event);

private slots:
   void on_action_open_plant_file_triggered();
   void on_action_re_open_last_plant_triggered();
   void on_actionView_log_triggered();
   void on_action_Shut_everything_off_triggered();
   void on_action_Check_light_status_triggered();
   void on_action_Locale_triggered(bool checked);

private slots:
   /** called when a plant is loaded or unloaded */
   void onPlantLoaded(bool);

   void on_actionAbout_Lucy_triggered();

private:
   Ui::MainWindow *ui;
   QTranslator *m_translator;

   /* application lifetime objects */
   PlantLoader & m_plantLoader;
   PlantParser & m_plantParser;
   PlantFactory & m_plantFactory;
   ApplicationSettings & m_settings;
   ErrorNotifier_IF & m_messageLogger;

   /* plant lifetime objects */
   OwnEngine *m_ownEngine;
   GuiInterface_IF *m_guiInterface;

private:
   bool openPlantFile(const QString &fileName);
   void loadApplicationLanguage();
};

#endif // MAINWINDOW_H
