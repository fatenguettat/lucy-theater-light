#ifndef LIGHTGROUP_H
#define LIGHTGROUP_H

#include <QList>

#include "OwnTypes.h"
#include "LightPoint.h"

/**
 * @brief The LightGroup class is a structured class that extends the light point
 *   with a set of light points associated to its 'WHERE' address.
 * It is used to implement OWN group syntax #n, where n is group number.
 */
class LightGroup
{
public:
   LightGroup( const LightPoint & node,
               const QList<own::Where> & lightPointList);

   const LightPoint & node() const;
   const QList<own::Where> & getLightPointList() const;

private:
   LightPoint m_node;
   QList<own::Where> m_lightPointList;
};

Q_DECLARE_METATYPE(const LightGroup *)

#endif // LIGHTGROUP_H
