#ifndef MESSAGEVIEWER_H
#define MESSAGEVIEWER_H

#include <QDialog>

namespace Ui {
class MessageViewer;
}

class QStringList;


class MessageViewer : public QDialog
{
   Q_OBJECT

public:
   explicit MessageViewer( const QStringList & messagelist, QWidget *parent = 0);
   ~MessageViewer();

private slots:
   void on_doneButton_clicked();

private:
   Ui::MessageViewer *ui;
};

#endif // MESSAGEVIEWER_H
