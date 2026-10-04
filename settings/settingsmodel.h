#ifndef SETTINGSMODEL_H
#define SETTINGSMODEL_H

#include <QString>

class SettingsModel
{
public:
    SettingsModel();
    SettingsModel(const QString &server, const QString &database, const QString &user, const QString &password, const bool showWarnings);

    QString server();
    QString database();
    QString user();
    QString password();
    bool showWarnings();

    void server(const QString server);
    void database(const QString database);
    void user(const QString user);
    void password(const QString password);
    void showWarnings(bool show_warnings);
	
    void load();
    void save();

private:
    QString mServer;
    QString mDatabase;
    QString mUser;
    QString mPassword;
    bool mShowWarnings;
};

#endif // SETTINGSMODEL_H
