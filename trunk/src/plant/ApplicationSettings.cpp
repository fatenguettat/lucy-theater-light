#include "ApplicationSettings.h"

#include <QSettings>
#include <QStandardPaths>

#include "testableAssert.h"

#define  COMPANY_TAG    "Me.Te.Or."
#define  PRODUCT_TAG    "Lucy"

#define LAST_FILE_TAG   "Last plant file"


ApplicationSettings::ApplicationSettings()
{
   m_setting = new QSettings( QString(COMPANY_TAG), QString(PRODUCT_TAG) );
   T_ASSERT( m_setting != NULL);
}

ApplicationSettings::~ApplicationSettings()
{
   delete m_setting;
}

void ApplicationSettings::setLastPlantPath(const QString &plantPath)
{
   m_setting->setValue( QString(LAST_FILE_TAG), plantPath);
}

QString ApplicationSettings::getLastPlantPath()
{
   QString defaultPath = QStandardPaths::standardLocations( QStandardPaths::DocumentsLocation).at(0);
   QString filePath = m_setting->value( LAST_FILE_TAG, defaultPath).toString();

   return filePath;
}

void ApplicationSettings::setLanguage(ApplicationSettings::Language language)
{
   QSettings setting( COMPANY_TAG, PRODUCT_TAG);
   setting.setValue( "language", language);
}

ApplicationSettings::Language ApplicationSettings::language()
{
   QSettings setting( COMPANY_TAG, PRODUCT_TAG);
   Language language = (Language)(setting.value( "language", NATIVE).toInt());

   return language;
}
