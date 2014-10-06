#include "LightButton.h"

#include <QPainter>

QPixmap *LightButton::m_pixmapOn = NULL;
QPixmap *LightButton::m_pixmapOff = NULL;
QPixmap *LightButton::m_pixmapUnknown = NULL;


LightButton::LightButton(const own::Where &index, QGraphicsItem *parent)
   : Button(parent),
     m_where(index),
     m_state(LIGHT_UNKNOWN)
{
   setAcceptHoverEvents(true);
   setCacheMode(DeviceCoordinateCache);
}

#if 0
QRectF LightButton::boundingRect() const
{
   return QRectF(-m_size, -m_size, m_size, m_size);
}

QPainterPath LightButton::shape() const
{
   QPainterPath path;
   path.addEllipse(boundingRect());
   return path;
}
#endif

void LightButton::setState(LightState state)
{
   m_state = state;
   update();
}

void LightButton::paint(QPainter *painter,
                        const QStyleOptionGraphicsItem *option, QWidget *widget)
{

   /* draw base of button */
   Button::paint( painter, option, widget);

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

   painter->drawPixmap( -(m_size/2) + (pixmap->width()*3./4.),
                        -(m_size/2) + (pixmap->height()*3./4.), *pixmap);
}


void LightButton::mouseReleaseEvent(QGraphicsSceneMouseEvent *ev)
{
   Button::mouseReleaseEvent( ev);

   /* hit is complete when user releases */
   emit hit(m_where);
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

