#include "LightPoint.h"

LightPoint::LightPoint(const QString & description,
                        const QPointF & position,
                        const own::Where &ownAddress) :
   m_description(description),
   m_position(position),
   m_ownAddress(ownAddress)
{
}

LightPoint::LightPoint() :
   m_description("pippo"),
   m_position(QPointF(0.3,0.4)),
   m_ownAddress(55)
{

}

LightPoint::LightPoint(const LightPoint &other) :
   m_description(other.description()),
   m_position(other.position()),
   m_ownAddress(other.ownAddress())
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

own::Where LightPoint::ownAddress() const
{
   return m_ownAddress;
}
