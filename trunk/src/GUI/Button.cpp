#include "Button.h"

#include <QStyleOptionGraphicsItem>
#include <QPainter>

#define DEFAULT_SIZE   40


Button::Button(QGraphicsItem *parent) :
   QGraphicsWidget(parent),
   m_size(DEFAULT_SIZE),
   m_icon(NULL)
{
   setAcceptHoverEvents(true);
   setCacheMode(DeviceCoordinateCache);
}

QRectF Button::boundingRect() const
{
   return QRectF( 0, 0, m_size, m_size);
}

QPainterPath Button::shape() const
{
   QPainterPath path;
   path.addEllipse(boundingRect());
   return path;
}

void Button::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
   bool down = option->state & QStyle::State_Sunken;
   QRectF r = boundingRect();
   QLinearGradient grad(r.topLeft(), r.bottomRight());
   grad.setColorAt(down ? 1 : 0,
                   option->state & QStyle::State_MouseOver ? Qt::white : Qt::lightGray);

   grad.setColorAt(down ? 0 : 0.5, Qt::darkGray);

   painter->setPen(Qt::darkGray);
   painter->setBrush(grad);
   painter->drawEllipse(r);
   grad.setColorAt(down ? 1 : 0, Qt::darkGray);
   grad.setColorAt(down ? 0 : 1, Qt::lightGray);
   painter->setPen(Qt::NoPen);
   painter->setBrush(grad);

   if (down)
   {
      painter->translate(2, 2);
   }
   painter->drawEllipse(r.adjusted(5, 5, -5, -5));

   // draw icon
   const QPixmap & icon = getIcon();

   // TODO scaling each time is waste of resources.
   //   Should be done on 'setSize' only.
   painter->drawPixmap( m_size*1/10, m_size*1/10, icon.scaledToHeight(m_size*8/10));
}

void Button::setSize(int size)
{
   m_size = size;
}

void Button::setDefaultIcon(const QPixmap *icon)
{
   m_icon = icon;
}

void Button::mousePressEvent(QGraphicsSceneMouseEvent *)
{
   update();
}

void Button::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{
   update();
   emit hit();
}

const QPixmap &Button::getIcon()
{
   /* ensure default object is created */
   static QPixmap *nullPixmap = NULL;
   if (nullPixmap == NULL)
   {
      nullPixmap = new QPixmap();
   }

   /* if set, return 'm_icon' */
   const QPixmap * pixmap = nullPixmap;
   if (m_icon != NULL)
   {
      pixmap = m_icon;
   }

   return *pixmap;
}

