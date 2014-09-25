#include "LightButton.h"

/** this is a main value from which all dimensions are calculated */
#define SIZE   40

QPixmap *LightButton::m_pixmapOn = NULL;
QPixmap *LightButton::m_pixmapOff = NULL;
QPixmap *LightButton::m_pixmapUnknown = NULL;


LightButton::LightButton( int index, QGraphicsItem *parent)
   : QGraphicsWidget(parent),
     m_index(index),
     m_state(LIGHT_UNKNOWN)
{
   setAcceptHoverEvents(true);
   setCacheMode(DeviceCoordinateCache);
}

QRectF LightButton::boundingRect() const
{
   return QRectF(-SIZE, -SIZE, SIZE, SIZE);
}

QPainterPath LightButton::shape() const
{
   QPainterPath path;
   path.addEllipse(boundingRect());
   return path;
}

void LightButton::setState(LightState state)
{
   m_state = state;
   update();
}

void LightButton::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
{
   bool down = option->state & QStyle::State_Sunken;
   QRectF r = boundingRect();
   QLinearGradient grad(r.topLeft(), r.bottomRight());
   grad.setColorAt(down ? 1 : 0, option->state & QStyle::State_MouseOver ? Qt::white : Qt::lightGray);

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

   const QPixmap *pixmap;
   ensureIconsAreCreated();

   if (m_state == LIGHT_ON)
   {
      pixmap = m_pixmapOn;
   }
   else if (m_state == LIGHT_OFF)
   {
      pixmap = m_pixmapOff;
   }
   else
   {
      pixmap = m_pixmapUnknown;
   }

   painter->drawPixmap( -(SIZE/2) -(pixmap->width()/2),
                        -(SIZE/2) - (pixmap->height()/2), *pixmap);
}

void LightButton::mousePressEvent(QGraphicsSceneMouseEvent *)
{
   emit pressed(m_index);
   update();
}

void LightButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{
   update();
}

void LightButton::ensureIconsAreCreated()
{
   if (m_pixmapOn == NULL)
   {
      m_pixmapOn = new QPixmap(":/images/images/lightOn.png");
   }

   if (m_pixmapOff == NULL)
   {
      m_pixmapOff = new QPixmap(":/images/images/lightOff.png");
   }

   if (m_pixmapUnknown == NULL)
   {
      m_pixmapUnknown = new QPixmap(":/images/images/lightUnknown.png");
   }
}

