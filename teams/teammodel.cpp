/* =====================================
 *	teammodel.cpp
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */
#include "teammodel.h"
#include "teamrepository.h"
#include "../staff/staffrole.h"


TeamModel TeamModel::load(int staffId, int projectId)
{
    return TeamRepository::load(staffId, projectId);
}

TeamModel::TeamModel(int staffId, int projectId, StaffRole role, int active):  
                        mStaffId(staffId), mProjectId(projectId), mRole(role), mActive(active) {}
TeamModel::TeamModel(): TeamModel(0, 0, StaffRole::ProjectManager, 1) {}

int TeamModel::staffId() const
{
    return mStaffId;
}

int TeamModel::projectId() const
{
    return mProjectId;
}

StaffRole TeamModel::role() const
{
    return mRole;
}

bool TeamModel::active() const
{
    return mActive;
}


void TeamModel::staffId(const int staffId)
{
    mStaffId = staffId;
}

void TeamModel::projectId(const int projectId)
{
    mProjectId = projectId;
}

void TeamModel::role(const StaffRole role)
{
    mRole = role;
}

void TeamModel::active(bool active)
{
    mActive = active;
}

bool TeamModel::save()
{
    if (mStaffId == 0 && mProjectId == 0) {
        return TeamRepository::insert(this);
    } else {
        return TeamRepository::update(this);
    }
}

bool TeamModel::activate()
{
    return TeamRepository::activate(mProjectId, mStaffId);
}

bool TeamModel::deactivate()
{
    return TeamRepository::deactivate(mProjectId, mStaffId);
}
