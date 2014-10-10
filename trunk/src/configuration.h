#ifndef CONFIGURATION_H
#define CONFIGURATION_H

/** SW version tag */
#define SW_VERSION_TAG    "0.0.1 per registi"

#define ABOUT_MESSAGE   "<p><b>Lucy</b> <i>version" SW_VERSION_TAG "</i><p>"\
                        "This is free SW based on QT5."\

/**
 * max message that is built up searching for terminating '##'.
 * If more charcters arrive without termination, it it an error.
 */
#define  MAX_MESSAGE_SIZE    40


#endif // CONFIGURATION_H
