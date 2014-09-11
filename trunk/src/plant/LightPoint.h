#ifndef LIGHTPOINT_H
#define LIGHTPOINT_H

#include <QString>
#include <QPointF>

/**
 * @brief The LightPoint class is a structured class that holds
 * one light point in a plant graph.
 * The point is described by a label string, a position inside the plant
 * and an OpenWebNet address.
 */
class LightPoint
{
public:
   LightPoint( const QString & description,
               const QPointF & position,
               int ownAddress);

   ~LightPoint() {}

   QString description() const;
   QPointF position() const;
   int ownAddress() const;

private:
   QString m_description;
   QPointF m_position;
   int m_ownAddress;
};

#endif // LIGHTPOINT_H
