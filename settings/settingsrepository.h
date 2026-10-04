/*
 * settingsrepository.h
 *
 *  Created on: 6 May 2026
 *      Author: richard
 */

#ifndef SETTINGS_SETTINGSREPOSITORY_H_
#define SETTINGS_SETTINGSREPOSITORY_H_

#include "settingsmodel.h"

class SettingsRepository
{
public:
	static void load(SettingsModel *model);
	static void save(SettingsModel *model);
};

#endif /* SETTINGS_SETTINGSREPOSITORY_H_ */
