#ifndef LIGHT_BUTTON_H
#define LIGHT_BUTTON_H


#include "OwnTypes.h"
#include "Button.h"


class LightButton : public Button
{
   Q_OBJECT
public:
   typedef enum
   {
      LIGHT_UNKNOWN,
      LIGHT_ON,
      LIGHT_OFF
   } LightState;

public:
   LightButton( const own::Where & index, QGraphicsItem *parent = 0);
   ~LightButton() {}

   void setState(LightState state);
   virtual const QPixmap & getIcon();

signals:
   void hit(const own::Where &);

protected:
   virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *);

private:
   static QPixmap *m_pixmapOn;
   static QPixmap *m_pixmapOff;
   static QPixmap *m_pixmapUnknown;

   own::Where m_where;
   LightState m_state;

private:
   void ensureIconsAreCreated( void);
};


#endif // LIGHT_BUTTON_H
