#ifndef GUIINTERFACE_IF_H
#define GUIINTERFACE_IF_H

#include <QPointF>
#include <QObject>

class  GuiInterface_IF : public QObject
{
   Q_OBJECT
public:
   typedef struct
   {
      /*! location of light icon.
       * Must be in range (0,0) to (1,1) and located where the icon is drawn in
       * the plant. Point (0,0) is upper-left corner, (1,1) is lower right.*/
      QPointF position;

      /*! Open Web Net address associated with this light */
      int ownAddress;

   } GuiLightPoint;

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

   /*!
    * \brief draw a lightpoint image at the given \p position. The image is drawn in turned-off,
    *   (use \a showAsTurnedOn or \a showAsTurnedOff to change display state).
    * \param GuilightPoint defines the light to be added
    */
   virtual void addLightPoint( const GuiLightPoint & lightPoint) = 0;

   /*!
    * \brief show light icon at given address as turned on.
    * \param ownAddress defines light point (Open Web Net address)
    */
   virtual void showAsTurnedOn( int ownAddress) = 0;

   /*!
    * \brief show light icon at given address as turned off.
    * \param ownAddress defines light point (Open Web Net address)
    */
   virtual void showAsTurnedOff( int ownAddress) = 0;

   /*!
    * \brief to be called when user wants to load another plant.
    *  All display data related to previous plant are deleted
    */
   virtual void clear() = 0;

signals:
   /*!
    * \brief user wants to turn on a light.
    * \param ownAddress defines light point (Open Web Net address)
    */
   void turnOnRequest( int ownAddress);

   /*!
    * \brief user wants to turn ff a light.
    * \param ownAddress defines light point (Open Web Net address)
    */
   void turnOffRequest( int ownAddress);

};

#endif // GUIINTERFACE_IF_H
