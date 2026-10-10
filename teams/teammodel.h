/* =====================================
 *	teamfmodel.h
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */

#pragma once

#include <QString>
#include <QStringList>

#include "../common/listdata.h"

class TeamModel
{
	static QList<ListData> list(QString searchFor, bool inactive);
	static TeamModel load(int id);

	TeamModel(int staffId, int proectId);
	TeamModel();

	int staffId() const;
    int projectId() const;

	void staffId(const int staffId);
    void projectId(const int projectId);

	bool save();
	bool activate();
	bool deactivate();

};