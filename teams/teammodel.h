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
public:
	static TeamModel load(int id);

	TeamModel(int staffId, int proectId);
	TeamModel();

	int staffId() const;
    int projectId() const;
	int role() const;
	bool active() const;

	void staffId(const int staffId);
    void projectId(const int projectId);
	void role(const int role);
	void active(bool active);

	bool save();
	bool activate();
	bool deactivate();

private:
	int mStaffId;
	int mProjectId;
	int mRole;
	int mActive;
};