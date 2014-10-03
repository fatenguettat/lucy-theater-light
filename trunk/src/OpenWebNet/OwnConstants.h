#ifndef OPENWEBNET_H
#define OPENWEBNET_H

namespace own
{
   /** OWN string to start a 'command' session */
   const char COMMAND_SESSION_STRING[] = "*99*0##";
   /** OWN string for ACK */
   const char ACK_STRING[] = "*#*1##";

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

   /** value of 'where' to indicate all addresses in system */
   const int GLOBAL_WHERE = 0;
}


#endif // OPENWEBNET_H
