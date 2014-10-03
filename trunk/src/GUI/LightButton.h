#ifndef LIGHT_BUTTON_H
#define LIGHT_BUTTON_H

#include <QGraphicsWidget>
#include <QStyleOptionGraphicsItem>
#include <QPainter>


class LightButton : public QGraphicsWidget
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
   LightButton( int index, QGraphicsItem *parent = 0);
   ~LightButton() {}

   QRectF boundingRect() const;
   QPainterPath shape() const;
   void setState(LightState state);
   void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *);

signals:
   void pressed(int);

protected:
   void mousePressEvent(QGraphicsSceneMouseEvent *);
   void mouseReleaseEvent(QGraphicsSceneMouseEvent *);

private:
   static QPixmap *m_pixmapOn;
   static QPixmap *m_pixmapOff;
   static QPixmap *m_pixmapUnknown;

   int m_index;  /** identifies this button when it's part of a group. */
   LightState m_state;

private:
   void ensureIconsAreCreated( void);
};


#endif // LIGHT_BUTTON_H
