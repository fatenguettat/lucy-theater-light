#include "Scenario.h"

Scenario::Scenario(const QString &description) :
   m_description(description)
{
}

Scenario::~Scenario()
{
   m_scenarioTable.clear();
}

void Scenario::addWhereWhatPair(own::Where where, own::What what)
{
   m_scenarioTable[where] = what;
}

const QHash<own::Where, own::What> & Scenario::getScenarioTable() const
{
   return m_scenarioTable;
}

const QString &Scenario::getDescription() const
{
   return m_description;
}
