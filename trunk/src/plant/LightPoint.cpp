#include "LightPoint.h"

LightPoint::LightPoint( const QString & description,
                        const QPointF & position,
                        int ownAddress) :
   m_description(description),
   m_position(position),
   m_ownAddress(ownAddress)
{
}

QString LightPoint::description() const
{
   return m_description;
}

QPointF LightPoint::position() const
{
   return m_position;
}

int LightPoint::ownAddress() const
{
   return m_ownAddress;
}
