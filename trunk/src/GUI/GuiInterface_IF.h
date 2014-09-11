#ifndef GUIINTERFACE_IF_H
#define GUIINTERFACE_IF_H

#include <QPointF>


class  GuiInterface_IF
{
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
   GuiInterface_IF() {}

   /*!
    * \brief set the image shown as plant layout. It will be drown with the
    *    best possible fit (defined by derived classes).
    * \param fullPath is the full path of image to be shown. It should
    *    be in '.png' format.
    */
   virtual void setPlantLayoutImagePath( const QString & fullPath) = 0;

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

};

#endif // GUIINTERFACE_IF_H
