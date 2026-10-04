#ifndef SETTINGSMODEL_H
#define SETTINGSMODEL_H

#include <QString>

class SettingsModel
{
public:
    SettingsModel();
    SettingsModel(const QString &dataDirectory, const bool showWarnings);

    QString dataDirectory();
    bool showWarnings();

    void dataDirectory(const QString &dataDirectory);
    void showWarnings(bool show_warnings);
	
    void load();
    void save();

private:
    QString mDataDirectory;
    bool mShowWarnings;
};

#endif // SETTINGSMODEL_H
