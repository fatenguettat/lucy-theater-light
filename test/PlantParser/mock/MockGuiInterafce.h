#ifndef MOCKGUIINTERAFCE_H
#define MOCKGUIINTERAFCE_H

#include <QList>
#include <QHash>
#include <QString>

#include "GuiInterface_IF.h"


class MockGuiInterafce : public GuiInterface_IF
{
public:
   typedef enum
   {
      LIGHT_NOT_SET = 0,
      LIGHT_ON,
      LIGHT_OFF,
      LIGHT_MID_LEVEL,
      LIGHT_UNKNOWN

   } LightStatus;

public:
   explicit MockGuiInterafce();
   ~MockGuiInterafce() {}

   // GuiInterface_IF interface
public:
   virtual void setPlantLayoutImagePath(const QString &fullPath);
   virtual void storeLightPoint( const LightPoint * lightPoint);
   virtual void showAsTurnedOn( const own::Where & ownAddress);
   virtual void showAsTurnedOff( const own::Where & ownAddress);
   virtual void showAsUnknownState( const own::Where & ownAddress);
   virtual void showAsLevel( const own::Where & ownAddress, own::LIGHT_LEVEL level);
   virtual void setPlantLabel( const QString & label);
   virtual void clear();

   // mock function
   QString mockGetPlantLayoutPath()
   {
      return m_layoutPath;
   }

   QList<LightPoint> & mockGetLightPointList()
   {
      return m_lightsList;
   }

   LightStatus mockGetLightStatus( const own::Where & ownAddress);

   QString getPlantLabel()
   {
      return m_layoutLabel;
   }

private:
   QString m_layoutPath;
   QString m_layoutLabel;
   QList<LightPoint> m_lightsList;
   QHash<const own::Where, LightStatus> m_lightStatusTable;
};

#endif // MOCKGUIINTERAFCE_H
