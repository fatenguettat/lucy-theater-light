#pragma once

#include <QString>

class QSettings;


class ApplicationSettings
{
public:
   ApplicationSettings();
   ~ApplicationSettings();

   void setLastPlantPath( const QString & plantPath);
   QString getLastPlantPath();

private:
   QSettings *m_setting;
};

