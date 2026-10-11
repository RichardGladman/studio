/* =====================================
 *	teamfmodel.h
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */

#pragma once

#include <QString>
#include <QStringList>

#include "../staff/staffrole.h"

class TeamModel
{
public:
	static TeamModel load(int staffId, int projectId);

	TeamModel(int staffId, int projectId, StaffRole role, int active);
	TeamModel();

	int staffId() const;
    int projectId() const;
	StaffRole role() const;
	bool active() const;

	void staffId(const int staffId);
    void projectId(const int projectId);
	void role(const StaffRole role);
	void active(bool active);

	bool save();
	bool activate();
	bool deactivate();

private:
	int mStaffId;
	int mProjectId;
	StaffRole mRole;
	int mActive;
};