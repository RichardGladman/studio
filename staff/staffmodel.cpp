/* =====================================
 *	staffmodel.cpp
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */

#include "staffmodel.h"
#include "employeetype.hpp"
#include "staffrepository.h"

QList<ListData> StaffModel::list(QString searchFor, bool inactive)
{
    return StaffRepository::list(searchFor, inactive);
}

StaffModel StaffModel::load(int id)
{
    return StaffRepository::load(id);
}

StaffModel::StaffModel(QString name, EmployeeType type, int chargedAt, bool active, int id) :
            mName {name}, mType {type}, mChargedAt {chargedAt}, mActive {active}, mId {id} {}
StaffModel::StaffModel() : mName {""}, mType {-1}, mChargedAt {0}, mActive {1}, mId {0} {}

int StaffModel::id() const
{
    return mId;
}

QString StaffModel::name() const
{
    return mName;
}

EmployeeType StaffModel::type() const
{
    return mType;
}

int StaffModel::chargedAt() const
{
    return mChargedAt;
}

bool StaffModel::active() const
{
    return mActive;
}

void StaffModel::id(int id)
{
    mId = id;
}

void StaffModel::name(const QString name)
{
    mName = name;
}

void StaffModel::type(EmployeeType type)
{
    mType = type;
}

void StaffModel::chargedAt(int chargedAt)
{
    mChargedAt = chargedAt;
}

void StaffModel::active(bool active)
{
    mActive = active;
}

bool StaffModel::save()
{
    if (mId == 0) {
        return StaffRepository::insert(this);
    } else {
        return StaffRepository::update(this);
    }
}

bool StaffModel::activate() 
{
    return StaffRepository::activate(mId);
}

bool StaffModel::deactivate()
{
    return StaffRepository::deactivate(mId);
}
