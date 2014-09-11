#ifndef BUTTON_H
#define BUTTON_H

#include <QGraphicsWidget>
#include <QStyleOptionGraphicsItem>
#include <QPainter>

/** this is a main value from which all dimensions are calculated */
#define SIZE   40

class Button : public QGraphicsWidget
{
    Q_OBJECT
public:
    Button(const QPixmap &pixmap, QGraphicsItem *parent = 0)
        : QGraphicsWidget(parent), _pix(pixmap),
          _highlighted(false)
    {
        setAcceptHoverEvents(true);
        setCacheMode(DeviceCoordinateCache);
    }

    QRectF boundingRect() const
    {
        return QRectF(-SIZE, -SIZE, SIZE, SIZE);
    }

    QPainterPath shape() const
    {
        QPainterPath path;
        path.addEllipse(boundingRect());
        return path;
    }

    void setHighlighted(bool highlighted)
    {
       _highlighted = highlighted;
    }

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *)
    {
        bool down = option->state & QStyle::State_Sunken;
        QRectF r = boundingRect();
        QLinearGradient grad(r.topLeft(), r.bottomRight());
        grad.setColorAt(down ? 1 : 0, option->state & QStyle::State_MouseOver ? Qt::white : Qt::lightGray);

        if (_highlighted)
        {
           grad.setColorAt(down ? 0 : 0.5, Qt::yellow);
        }
        else
        {
           grad.setColorAt(down ? 0 : 0.5, Qt::darkGray);
        }
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
        painter->drawPixmap( -(SIZE/2) -(_pix.width()/2), -(SIZE/2) - (_pix.height()/2), _pix);
    }

signals:
    void pressed();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *)
    {
        emit pressed();
        update();
    }

    void mouseReleaseEvent(QGraphicsSceneMouseEvent *)
    {
        update();
    }

private:
    QPixmap _pix;
    bool _highlighted;
};

#endif // BUTTON_H
