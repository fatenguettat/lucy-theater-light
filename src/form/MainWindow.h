#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QGraphicsView;
class PlantLoader;
class PlantParser;
class PlantView;
class ApplicationSettings;
class ErrorNotifier_IF;


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
   Q_OBJECT

public:
   explicit MainWindow(PlantParser &plantParser, PlantLoader & plantLoader,
                       PlantView &plantView, ApplicationSettings & settings,
                       ErrorNotifier_IF &errorNotifier, QWidget *parent = 0);
   ~MainWindow();

private slots:
   void on_action_open_plant_file_triggered();
   void on_action_re_open_last_plant_triggered();

   void on_actionView_log_triggered();

private:
   Ui::MainWindow *ui;

   PlantLoader & m_plantLoader;
   PlantParser & m_plantParser;
   ApplicationSettings & m_settings;
   ErrorNotifier_IF & m_messageLogger;

private:
   void openPlantFile(const QString &fileName);
};

#endif // MAINWINDOW_H
