#ifndef BUTTON_H
#define BUTTON_H

#include <QGraphicsWidget>

class Button : public QGraphicsWidget
{
   Q_OBJECT
public:
   explicit Button(QGraphicsItem *parent = 0);

   QRectF boundingRect() const;
   QPainterPath shape() const;
   virtual void paint(QPainter *painter,
                      const QStyleOptionGraphicsItem *option, QWidget *);

   /* set the cardinal value for button size */
   void setSize(int size);

signals:
   void hit();

protected:
   virtual void mousePressEvent(QGraphicsSceneMouseEvent *);
   virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *);

   /**
    * @brief this function must be reimplemented by children to return correct icon.
    * @return a void pixmap in default implementation.
    */
   virtual const QPixmap & getIcon();

protected:
   /** this is a main value from which all dimensions are calculated */
   int m_size;
};

#endif // BUTTON_H
