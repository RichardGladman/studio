/*
 * settingsrepository.cpp
 *
 *  Created on: 6 May 2026
 *      Author: richard
 */

#include "settingsrepository.h"

#include <QSettings>

void SettingsRepository::load(SettingsModel *model)
{
    QSettings settings("TheFifthContinent", "Studio");

    settings.beginGroup("server");
    model->server(settings.value("server").toString());
    model->database(settings.value("database").toString());
    model->user(settings.value("user").toString());
    model->password(settings.value("password").toString());
    settings.endGroup();

    settings.beginGroup("Flags");
    model->showWarnings(settings.value("warnings").toBool());
    settings.endGroup();
}

void SettingsRepository::save(SettingsModel *model)
{
    QSettings settings("TheFifthContinent", "Studio");

    settings.beginGroup("server");
    settings.setValue("server", model->server());
    settings.setValue("database", model->database());
    settings.setValue("user", model->user());
    settings.setValue("password", model->password());
    settings.endGroup();

    settings.beginGroup("Flags");
    settings.setValue("warnings", model->showWarnings());
    settings.endGroup();
}
