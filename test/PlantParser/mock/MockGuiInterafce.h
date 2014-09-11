#ifndef MOCKGUIINTERAFCE_H
#define MOCKGUIINTERAFCE_H

#include <QList>
#include <QString>

#include "GuiInterface_IF.h"


class MockGuiInterafce : public GuiInterface_IF
{
public:
   explicit MockGuiInterafce();

   // GuiInterface_IF interface
public:
   virtual void setPlantLayoutImagePath(const QString &fullPath);
   virtual void addLightPoint( const GuiLightPoint & lightPoint);
   virtual void showAsTurnedOn( int ownAddress);
   virtual void showAsTurnedOff( int ownAddress);

   // mock function
   QString getPlantLayoutPath()
   {
      return m_layoutPath;
   }

   QList<GuiLightPoint> getLightPointList()
   {
      return m_lightsList;
   }

private:
   QString m_layoutPath;
   QList<GuiLightPoint> m_lightsList;
};

#endif // MOCKGUIINTERAFCE_H
