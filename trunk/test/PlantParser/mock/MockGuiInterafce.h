#ifndef MOCKGUIINTERAFCE_H
#define MOCKGUIINTERAFCE_H

#include <QList>
#include <QMap>
#include <QString>

#include "GuiInterface_IF.h"


class MockGuiInterafce : public GuiInterface_IF
{
public:
   typedef enum
   {
      LIGHT_NOT_SET = 0,
      LIGHT_ON,
      LIGHT_OFF

   } LightStatus;

public:
   explicit MockGuiInterafce();

   // GuiInterface_IF interface
public:
   virtual void setPlantLayoutImagePath(const QString &fullPath);
   virtual void addLightPoint( const GuiLightPoint & lightPoint);
   virtual void showAsTurnedOn( int ownAddress);
   virtual void showAsTurnedOff( int ownAddress);
   virtual void setPlantLabel( const QString & label);
   virtual void clear();

   // mock function
   QString getPlantLayoutPath()
   {
      return m_layoutPath;
   }

   QList<GuiLightPoint> getLightPointList()
   {
      return m_lightsList;
   }

   LightStatus getLightStatus( int ownAddress);

   QString getPlantLabel()
   {
      return m_layoutLabel;
   }

private:
   QString m_layoutPath;
   QString m_layoutLabel;
   QList<GuiLightPoint> m_lightsList;
   QMap<int, LightStatus> m_lightStatusTable;
};

#endif // MOCKGUIINTERAFCE_H
