#include "MessageViewer.h"
#include "ui_MessageViewer.h"

#include <QStringList>

MessageViewer::MessageViewer(const QStringList &messagelist, QWidget *parent) :
   QDialog(parent),
   ui(new Ui::MessageViewer)
{
   ui->setupUi(this);

   QString allMessageString = messagelist.join("\n");

   /* cat all messages and print them */
   ui->messagePad->setPlainText( allMessageString);
}

MessageViewer::~MessageViewer()
{
   delete ui;
}


void MessageViewer::on_doneButton_clicked()
{
   /* dismiss this window */
   close();
}
