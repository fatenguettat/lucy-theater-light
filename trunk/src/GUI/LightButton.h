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
      LIGHT_UNKNOWN = 0,
      LIGHT_ON,
      LIGHT_OFF,

      /** used for buttons that control other lights, without their own state */
      LIGHT_IS_HANDLER

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
   static QPixmap *m_pixmapHandler;

   own::Where m_where;
   LightState m_state;

private:
   void ensureIconsAreCreated( void);
};


#endif // LIGHT_BUTTON_H
