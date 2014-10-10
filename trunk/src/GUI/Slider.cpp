#include "Slider.h"

#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QStyleOptionGraphicsItem>

Slider::Slider(int base, int numOfTicks, int interval, QGraphicsWidget *parent) :
   QGraphicsWidget(parent),
   m_height(50.),
   m_width(200.),
   m_baseValue(base),
   m_intervalValue(interval),
   m_numbOfTicks(numOfTicks),
   m_currentTick(0)
{
}

int Slider::value()
{
   return m_baseValue + (m_currentTick * m_intervalValue);
}


void Slider::paint(QPainter *painter, const QStyleOptionGraphicsItem * option, QWidget * /*widget*/)
{
   m_width = option->rect.width();
   m_height = option->rect.height();

   QRectF bound( 0., 3., m_width, m_height - 6.);
   QLinearGradient grad(bound.topLeft(), bound.bottomRight());
   grad.setColorAt( 0, Qt::black);
   grad.setColorAt( 0.8, Qt::yellow);

   painter->setPen(Qt::darkGray);
   painter->setBrush(grad);
   painter->drawRect( bound);

   // draw ticks
   for (int i=0; i < m_numbOfTicks; i++)
   {
      double xTick = i * (m_width / ((double)m_numbOfTicks));
      painter->setBrush(Qt::red);
      painter->drawRect( xTick - 1., 0, 2., m_height);
   }

   // draw active tick
   double xActTick = (m_currentTick + 0.5) * (m_width / ((double)m_numbOfTicks));

   painter->setBrush(Qt::blue);
   painter->drawRect( xActTick - 3., 0, 6., m_height);
}

void Slider::mousePressEvent(QGraphicsSceneMouseEvent * /*event*/)
{
}


void Slider::mouseReleaseEvent(QGraphicsSceneMouseEvent * event)
{
   double xPos = event->pos().x();
   m_currentTick = (int)((xPos / m_width) * (double)m_numbOfTicks);

   update();
}

void Slider::wheelEvent(QGraphicsSceneWheelEvent * /*event*/)
{
}
