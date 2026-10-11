/* =====================================
 *	customermodel.h
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */

#pragma once

#include <QString>
#include <QStringList>
#include <QtCore/qobject.h>

#include "../common/listdata.h"
#include "../common/address.h"

class CustomerModel
{
public:
	static QList<ListData> list(QString searchFor, bool inactive);
	static CustomerModel load(int id);

	CustomerModel(QString name, Address address, QString phoneNumber, QString email, bool active, int id = 0);
	CustomerModel();

	int id() const;
	QString name() const;
	Address address() const;
	QString phoneNumber() const;
	QString email() const;
	bool active() const;

	void id(const int id);
	void name(const QString name);
	void address(const Address address);
	void phoneNumber(const QString phoneNumber);
	void email(const QString email);
	void active(const bool active);

	bool save();
	bool activate();
	bool deactivate();

private:
	int mId;
	QString mName;
	Address mAddress;
	QString mPhoneNumber;
	QString mEmail;
	bool mActive;
};