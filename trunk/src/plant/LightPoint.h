#ifndef LIGHTPOINT_H
#define LIGHTPOINT_H

#include <QString>
#include <QPointF>

#include <QObject>

#include "OwnTypes.h"

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
               const own::Where & ownAddress);

   /* These are needed for 'Q_DECLARE_METATYPE' macro,
    * but are highly deprecated. */
   LightPoint();
   LightPoint( const LightPoint &other);

   ~LightPoint() {}

   QString description() const;
   QPointF position() const;
   own::Where ownAddress() const;

private:
   QString m_description;
   QPointF m_position;
   own::Where m_ownAddress;
};

Q_DECLARE_METATYPE(const LightPoint *)

#endif // LIGHTPOINT_H
