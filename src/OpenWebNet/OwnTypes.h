#pragma once

#include <QString>

namespace own
{
/** OWN protocol 'where' field */
typedef QString Where;

/** OWN protocol 'what' field */
typedef int What;

/** constants used for dimmerable lights */
typedef enum
{
   LEVEL_20 = 0,
   LEVEL_30,
   LEVEL_40,
   LEVEL_50,
   LEVEL_60,
   LEVEL_70,
   LEVEL_80,
   LEVEL_90,
   LEVEL_100

} LIGHT_LEVEL;
}
