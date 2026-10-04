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

    settings.beginGroup("Paths");
    model->dataDirectory(settings.value("datadir").toString());
    settings.endGroup();

    settings.beginGroup("Flags");
    model->showWarnings(settings.value("warnings").toBool());
    settings.endGroup();
}

void SettingsRepository::save(SettingsModel *model)
{
    QSettings settings("TheFifthContinent", "Studio");

    settings.beginGroup("Paths");
    settings.setValue("datadir", model->dataDirectory());
    settings.endGroup();

    settings.beginGroup("Flags");
    settings.setValue("warnings", model->showWarnings());
    settings.endGroup();
}
