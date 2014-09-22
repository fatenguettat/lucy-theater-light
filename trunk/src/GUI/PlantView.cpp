#include "PlantView.h"

#include <QEvent>
#include <QWheelEvent>

#include <QScrollBar>

#include "qdebug.h"

PlantView::PlantView(QGraphicsScene *scene) :
   QGraphicsView(scene)
{
   viewport()->installEventFilter(this);
   setDragMode( QGraphicsView::ScrollHandDrag);
   setInteractive( true);
}



bool PlantView::eventFilter(QObject *target, QEvent *event)
{
   bool filterOut = false;

   if (target == viewport())
   {
      QEvent::Type eventType = event->type();

      if (eventType == QEvent::Wheel)
      {
         filterOut = true;
         QWheelEvent *wheelEvent = dynamic_cast<QWheelEvent *>(event);

         if (wheelEvent->angleDelta().y() > 0)
         {
            scale( 1.1, 1.1);
         }
         else
         {
            scale( 0.9, 0.9);
         }
      }
      else
      {
         filterOut = QGraphicsView::eventFilter( target, event);
      }
   }

   return filterOut;
}

