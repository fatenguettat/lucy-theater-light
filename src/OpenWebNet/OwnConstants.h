#ifndef OPENWEBNET_H
#define OPENWEBNET_H


namespace own
{
/** OWN string to start a 'command' session */
const char COMMAND_SESSION_STRING[] = "*99*0##";
/** OWN string for ACK */
const char ACK_STRING[] = "*#*1##";

/** value of 'where' to indicate all addresses in system */
const char GLOBAL_WHERE[] = "0";
}


#endif // OPENWEBNET_H
