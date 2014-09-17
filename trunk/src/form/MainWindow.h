#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QGraphicsView;
class PlantLoader;
class PlantParser;
class PlantView;

///////////////////////
class QGestureEvent;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
   Q_OBJECT

public:
   explicit MainWindow(PlantParser &plantParser, PlantLoader & plantLoader,
                       PlantView &plantView, QWidget *parent = 0);
   ~MainWindow();

private slots:
   void on_action_open_plant_file_triggered();

private:
   Ui::MainWindow *ui;

   PlantLoader & m_plantLoader;
   PlantParser & m_plantParser;

private:
   bool gestureEvent(QGestureEvent *event);
};

#endif // MAINWINDOW_H
