#ifndef PLANTVIEW_H
#define PLANTVIEW_H

#include <QGraphicsView>

class QGestureEvent;
class QPlainTextEdit;


class PlantView : public QGraphicsView
{
   Q_OBJECT
public:
   explicit PlantView(QGraphicsScene  *scene);

protected:
   virtual bool eventFilter(QObject *, QEvent *);
};

#endif // PLANTVIEW_H
