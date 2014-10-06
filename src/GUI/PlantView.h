#ifndef PLANTVIEW_H
#define PLANTVIEW_H

#include <QGraphicsView>

class QGestureEvent;
class QPlainTextEdit;
class QWheelEvent;
class QTouchEvent;


class PlantView : public QGraphicsView
{
   Q_OBJECT
public:
   explicit PlantView(QGraphicsScene  *scene);

protected:
   virtual bool viewportEvent(QEvent *event);

private:
   qreal m_totalScaleFactor;

private:
   bool onWheelEvent( const QWheelEvent *wheelEvent);
   bool onTouchEvent( const QTouchEvent *touchEvent);
};

#endif // PLANTVIEW_H
