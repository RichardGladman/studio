#include "settingsmodel.h"
#include "settingsrepository.h"

#include <QSettings>

SettingsModel::SettingsModel() : SettingsModel { "", "", "", "", true } {}

SettingsModel::SettingsModel(const QString &server, const QString &database, const QString &user, const QString &password, const bool showWarnings) :
    mServer {server}, mDatabase {database}, mUser {user}, mPassword {password}, mShowWarnings {showWarnings} {}

QString SettingsModel::server()
{
    return mServer;
}

QString SettingsModel::database()
{
    return mDatabase;
}

QString SettingsModel::user()
{
    return mUser;
}

QString SettingsModel::password()
{
    return mPassword;
}

bool SettingsModel::showWarnings()
{
    return mShowWarnings;
}

void SettingsModel::server(const QString server)
{
    mServer = server;
}

void SettingsModel::database(const QString database)
{
    mDatabase = database;
}

void SettingsModel::user(const QString user) 
{
    mUser = user;
}

void SettingsModel::password(const QString password)
{
    mPassword = password;
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
