#ifndef SLIDER_H
#define SLIDER_H

#include <QGraphicsWidget>

class Slider : public QGraphicsWidget
{
   Q_OBJECT
public:
   /**
    * @brief build a slider with given values
    * @param base is the value relevant to first tick
    * @param numOfTicks is the number of thicks shown in slider
    * @param interval is the difference of value between two consequtive ticks
    * @param parent is parent widget
    */
   explicit Slider( int base, int numOfTicks, int interval,
                    QGraphicsWidget *parent = 0);

public:
   /** @return current tick position */
   int value();

   // QGraphicsItem interface
public:
   virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
   virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
   virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
   virtual void wheelEvent(QGraphicsSceneWheelEvent *event);

private:
   /* configuration properties */
   double m_height;
   double m_width;
   int m_baseValue;
   int m_intervalValue;
   int m_numbOfTicks;

   /* usage properties */
   int m_currentTick;
};

#endif // SLIDER_H
