#include "settingsmodel.h"
#include "settingsrepository.h"

#include <QSettings>

SettingsModel::SettingsModel() : SettingsModel { "", true } {}

SettingsModel::SettingsModel(const QString &dataDirectory, const bool showWarnings) :
    mDataDirectory {dataDirectory}, mShowWarnings {showWarnings} {}

QString SettingsModel::dataDirectory()
{
    return mDataDirectory;
}

bool SettingsModel::showWarnings()
{
    return mShowWarnings;
}

void SettingsModel::dataDirectory(const QString &dataDirectory)
{
    mDataDirectory = dataDirectory;
}

void SettingsModel::showWarnings(bool showWarnings)
{
    mShowWarnings = showWarnings;
}

void SettingsModel::load()
{
    SettingsRepository::load(this);
}

void SettingsModel::save()
{
    SettingsRepository::save(this);
}
