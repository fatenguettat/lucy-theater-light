#include "LightButton.h"

#include <QPainter>

QPixmap *LightButton::m_pixmapOn = NULL;
QPixmap *LightButton::m_pixmapOff = NULL;
QPixmap *LightButton::m_pixmapUnknown = NULL;
QPixmap *LightButton::m_pixmapHandler = NULL;


LightButton::LightButton(const own::Where &index, QGraphicsItem *parent)
   : Button(parent),
     m_where(index),
     m_state(LIGHT_UNKNOWN)
{
   setAcceptHoverEvents(true);
   setCacheMode(DeviceCoordinateCache);
}

void LightButton::setState(LightState state)
{
   m_state = state;
   update();
}

const QPixmap & LightButton::getIcon()
{
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
   else if (m_state == LIGHT_IS_HANDLER)
   {
      pixmap = m_pixmapHandler;
   }
   else
   {
      pixmap = m_pixmapUnknown;
   }

   return *pixmap;
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

   if (m_pixmapHandler == NULL)
   {
      m_pixmapHandler = new QPixmap(":/images/images/lightHandler.png");
   }

   if (m_pixmapUnknown == NULL)
   {
      m_pixmapUnknown = new QPixmap(":/images/images/lightUnknown.png");
   }
}

