#pragma once

#include <QString>

class QSettings;


class ApplicationSettings
{
public:
   typedef enum
      {
         NATIVE = 0,
         LOCALE
      } Language;

public:
   ApplicationSettings();
   ~ApplicationSettings();

   /** @{ full path of last opened plant file */
   void setLastPlantPath( const QString & plantPath);
   QString getLastPlantPath();
   /** @} */

   /** @{ current language */
   void setLanguage(Language language);
   Language language();
   /** @} */

private:
   QSettings *m_setting;
};

