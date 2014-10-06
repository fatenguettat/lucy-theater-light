#ifndef GUIINTERFACE_IF_H
#define GUIINTERFACE_IF_H

#include <QPointF>
#include <QObject>

#include "OwnTypes.h"

class LightPoint;


/**
 * @brief The GuiInterface_IF class holds interfaces for all commands directed
 *   to GUI and signals incoming from user action through GUI.
 */
class  GuiInterface_IF : public QObject
{
   Q_OBJECT
public:
   GuiInterface_IF(QObject *parent = 0) : QObject(parent) {}

   /*!
    * \brief set the image shown as plant layout. It will be drown with the
    *    best possible fit (defined by derived classes).
    * \param fullPath is the full path of image to be shown. It should
    *    be in '.png' format.
    */
   virtual void setPlantLayoutImagePath( const QString & fullPath) = 0;

   /*!
    * \brief set a brief description of the plant that UI may show somewhere.
    *   Usually a version identification is included
    * \param label is a string
    */
   virtual void setPlantLabel( const QString & label) = 0;

public slots:
   /*!
    * \brief show light icon at given address as turned on.
    * \param ownAddress defines light point (Open Web Net address)
    */
   virtual void showAsTurnedOn( const own::Where & ownAddress) = 0;

   /*!
    * \brief show light icon at given address as turned off.
    * \param ownAddress defines light point (Open Web Net address)
    */
   virtual void showAsTurnedOff( const own::Where & ownAddress) = 0;

   /*!
    * \brief show light icon at given address as unknown. This is the normal
    *   state on startup and when a command has been issue but there is no feedback
    *   of result.
    * \param ownAddress defines light point (Open Web Net address)
    */
   virtual void showAsUnknownState( const own::Where & ownAddress) = 0;

   /*!
    * \brief show that a light point has been applied a given level
    * \param ownAddress defines light point (Open Web Net address)
    * \param level (see type for details)
    */
   virtual void showAsLevel( const own::Where & ownAddress, own::LIGHT_LEVEL level) = 0;

   /*!
    * \brief draw a lightpoint image at the given \p position. The image is drawn in turned-off,
    *   (use \a showAsTurnedOn or \a showAsTurnedOff to change display state).
    * \param GuilightPoint defines the light to be added
    */
   virtual void addLightPoint( const LightPoint * lightPoint) = 0;

public:
   /*!
    * \brief to be called when user wants to load another plant.
    *  All display data related to previous plant are deleted
    */
   // TODO plan to remove this if lifetime changes
   virtual void clear() = 0;

};

#endif // GUIINTERFACE_IF_H
