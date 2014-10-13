#pragma once

#include <QHash>
#include "OwnTypes.h"

/**
 * @brief The Scenario class is a structured class that defines a set
 * of pairs (light point ; command), with the command related to new
 * value for the light.
 * Note that, so far, there is no definition for the time to transit
 * to new value.
 */
class Scenario
{
public:
   Scenario(const QString & description);
   ~Scenario();

   /** insert a new WHAT for a WHERE in the scenario */
   void addWhereWhatPair(own::Where where, own::What what);

   /** return a hash map with 'What' (value) for given 'Where' (key) */
   const QHash< own::Where, own::What> & getScenarioTable() const;

   /** return scenario description */
   const QString & getDescription() const;

private:
   /** This is the main table that links a light point to
       a command (what to be applied) */
   QHash< own::Where, own::What> m_scenarioTable;

   QString m_description;
};

