/* =====================================
 *	teamfmodel.h
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */

#pragma once

#include <QString>
#include <QStringList>

#include "teamdata.h"
#include "../staff/staffrole.h"

class TeamModel
{
public:
static QList<TeamData> list(int projectId, bool inactive);
	static TeamModel load(int id);

	TeamModel(int staffId, int projectId, StaffRole role, bool active, int id = 0);
	TeamModel();

	int id() const;
	int staffId() const;
    int projectId() const;
	StaffRole role() const;
	bool active() const;

	void id(const int id);
	void staffId(const int staffId);
    void projectId(const int projectId);
	void role(const StaffRole role);
	void active(bool active);

	bool save();
	bool activate();
	bool deactivate();

private:
	int mId;
	int mStaffId;
	int mProjectId;
	StaffRole mRole;
	int mActive;
};