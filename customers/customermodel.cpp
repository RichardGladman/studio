/* =====================================
 *	customermodel.cpp
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */

#include "customermodel.h"
#include "customerrepository.h"
#include "../address/addressmodel.h"

QList<ListData> CustomerModel::list(QString searchFor, bool inactive)
{
    return CustomerRepository::list(searchFor, inactive);
}

CustomerModel CustomerModel::load(int id)
{
    return CustomerRepository::load(id);
}

CustomerModel::CustomerModel(QString name, AddressModel address, QString phoneNumber, QString email, bool active, int id) :
            mName(name), mAddress(address), mPhoneNumber(phoneNumber), mEmail(email), mActive(active), mId(id) {}
CustomerModel::CustomerModel() : CustomerModel("", address(), "", "", 1, 0) {}

int CustomerModel::id() const
{
    return mId;
}

QString CustomerModel::name() const
{
    return mName;
}

AddressModel CustomerModel::address() const
{
    return mAddress;
}

QString CustomerModel::phoneNumber() const 
{
    return mPhoneNumber;
}

QString CustomerModel::email() const
{
    return mEmail;
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

void CustomerModel::address(const Address address)
{
    mAddress = address;
}

void CustomerModel::phoneNumber(const QString phoneNumber)
{
    mPhoneNumber = phoneNumber;
}

void CustomerModel::email(const QString email)
{
    mEmail = email;
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
