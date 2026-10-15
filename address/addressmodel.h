/* =====================================
 *	addressmodel.h
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */

#pragma once

#include <QString>
#include <QtCore/qobject.h>

class AddressModel
{
public:
    AddressModel(QString streetAddress, QString area, QString town, QString county, QString postcode);
    AddressModel();

    QString streetAddress() const;
    QString area() const;
    QString town() const;
    QString county() const;
    QString postcode() const;

    void streetAddress(const QString streetAddress);
    void area(const QString area);
    void town(const QString town);
    void county(const QString county);
    void postcode(const QString postcode);

private:
    QString mStreetAddress;
    QString mArea;
    QString mTown;
    QString mCounty;
    QString mPostcode;
};