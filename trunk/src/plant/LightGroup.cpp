#include "LightGroup.h"

LightGroup::LightGroup( const LightPoint & node,
                        const QList<own::Where> & lightPointList):
   m_node(node),
   m_lightPointList(lightPointList)
{
}

const LightPoint &LightGroup::node() const
{
   return m_node;
}

const QList<own::Where> &LightGroup::getLightPointList() const
{
   return m_lightPointList;
}
