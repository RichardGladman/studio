/* =====================================
 *	customermodel.cpp
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */

#include "customermodel.h"
#include "customerrepository.h"

QList<ListData> CustomerModel::list(QString searchFor, bool inactive)
{
    return CustomerRepository::list(searchFor, inactive);
}

CustomerModel CustomerModel::load(int id)
{
    return CustomerRepository::load(id);
}

CustomerModel::CustomerModel(QString name, int chargedAt, bool active, int id) :
            mName {name}, mChargedAt {chargedAt}, mActive {active}, mId {id} {}
CustomerModel::CustomerModel() : mName {""}, mChargedAt {0}, mActive {1}, mId {0} {}

int CustomerModel::id() const
{
    return mId;
}

QString CustomerModel::name() const
{
    return mName;
}

int CustomerModel::chargedAt() const
{
    return mChargedAt;
}

bool CustomerModel::active() const
{
    return mActive;
}

void CustomerModel::id(int id)
{
    mId = id;
}

void CustomerModel::name(const QString name)
{
    mName = name;
}

void CustomerModel::chargedAt(int chargedAt)
{
    mChargedAt = chargedAt;
}

void CustomerModel::active(bool active)
{
    mActive = active;
}

bool CustomerModel::save()
{
    if (mId == 0) {
        return CustomerRepository::insert(this);
    } else {
        return CustomerRepository::update(this);
    }
}

bool CustomerModel::activate() 
{
    return CustomerRepository::activate(mId);
}

bool CustomerModel::deactivate()
{
    return CustomerRepository::deactivate(mId);
}
