/* =====================================
 *	addressmodel.cpp
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */

#include "addressmodel.h"

AddressModel::AddressModel(QString streetAddress, QString area, QString town, QString county, QString postcode):
                            mStreetAddress(streetAddress), mArea(area), mTown(town), mCounty(county), mPostcode(postcode) {}
AddressModel::AddressModel() : AddressModel("", "", "", "", "") {}

QString AddressModel::streetAddress() const 
{
    return mStreetAddress;
}

QString AddressModel::area() const 
{
    return mArea;
}

QString AddressModel::town() const
{
    return mTown;
}

QString AddressModel::county() const
{
    return mCounty;
}

QString AddressModel::postcode() const
{
    return mPostcode;
}

void AddressModel::streetAddress(const QString streetAddress)
{
    mStreetAddress = streetAddress;
}

void AddressModel::area(const QString area)
{
    mArea = area;
}

void AddressModel::town(const QString town)
{
    mTown = town;
}

void AddressModel::county(const QString county)
{
    mCounty = county;
}

void AddressModel::postcode(const QString postcode)
{
    mPostcode = postcode;
}
