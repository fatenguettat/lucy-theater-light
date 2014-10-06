#include "PlantView.h"

#include <QEvent>
#include <QWheelEvent>

#include <QScrollBar>


PlantView::PlantView(QGraphicsScene *scene) :
   QGraphicsView(scene),
   m_totalScaleFactor(1.0)
{
   viewport()->installEventFilter(this);
   setDragMode( QGraphicsView::ScrollHandDrag);
   setInteractive( true);
}


bool PlantView::viewportEvent(QEvent *event)
{
   bool consumeEvent = false;

   switch (event->type())
   {
   case QEvent::Wheel:
   {
      consumeEvent = onWheelEvent( dynamic_cast<QWheelEvent *>(event));
   }
      break;

   case QEvent::TouchBegin:
   case QEvent::TouchUpdate:
   case QEvent::TouchEnd:
   {
      consumeEvent = onTouchEvent( dynamic_cast<QTouchEvent *>(event));
   }
      break;

   default:
      break;
   }

   return (consumeEvent) ? true : QGraphicsView::viewportEvent(event);
}

bool PlantView::onWheelEvent(const QWheelEvent *wheelEvent)
{
   if (wheelEvent->angleDelta().y() > 0)
   {
      /* scroll up: zoom in */
      scale( 1.1, 1.1);
   }
   else
   {
      /* scroll down: zoom out */
      scale( 0.9, 0.9);
   }

   /* do not let this event propagate */
   return true;
}

bool PlantView::onTouchEvent( const QTouchEvent *touchEvent)
{
   QList<QTouchEvent::TouchPoint> touchPoints = touchEvent->touchPoints();
   if (touchPoints.count() == 2)
   {
      // determine scale factor
      const QTouchEvent::TouchPoint &touchPoint0 = touchPoints.first();
      const QTouchEvent::TouchPoint &touchPoint1 = touchPoints.last();
      qreal currentScaleFactor =
            QLineF(touchPoint0.pos(), touchPoint1.pos()).length()
            / QLineF(touchPoint0.startPos(), touchPoint1.startPos()).length();
      if (touchEvent->touchPointStates() & Qt::TouchPointReleased)
      {
         // if one of the fingers is released, remember the current scale
         // factor so that adding another finger later will continue zooming
         // by adding new scale factor to the existing remembered value.
         m_totalScaleFactor *= currentScaleFactor;
         currentScaleFactor = 1;
      }
      setTransform(QTransform().scale(m_totalScaleFactor * currentScaleFactor,
                                      m_totalScaleFactor * currentScaleFactor));
   }

   /* let this event propagate */
   return false;
}

