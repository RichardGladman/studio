/* =====================================
 *	teammodel.cpp
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */
#include "teammodel.h"
#include "teamrepository.h"
#include "../staff/staffrole.h"

#include <QDebug>

QList<TeamData> TeamModel::list(int projectId, bool inactive)
{
    return TeamRepository::list(projectId, inactive);
}

TeamModel TeamModel::load(int id)
{
    return TeamRepository::load(id);
}

TeamModel::TeamModel(int staffId, int projectId, StaffRole role, bool active, int id):  
                        mStaffId(staffId), mProjectId(projectId), mRole(role), mActive(active), mId(id) {}
TeamModel::TeamModel(): TeamModel(0, 0, StaffRole::None, 1, 0) {}

int TeamModel::id() const{
    return mId;
}

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

void TeamModel::id(const int id)
{
    mId = id;
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
    qDebug() << QString::number(mProjectId) << " " << QString::number(mStaffId);
    if (mId == 0) {
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
