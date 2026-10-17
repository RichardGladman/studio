/* =====================================
 *	staffmodel.h
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */

#pragma once

#include <QString>
#include <QStringList>

#include "../common/listdata.h"
#include "employeetype.hpp"

class StaffModel
{
public:
	static QList<ListData> list(QString searchFor, bool inactive);
	static StaffModel load(int id);

	StaffModel(QString name, QString email, QString password, bool changePassword, EmployeeType type, int chargedAt, bool active, int id = 0);
	StaffModel();

	int id() const;
	QString name() const;
	QString email() const;
	QString password() const;
	bool changePassword() const;
	EmployeeType type() const;
	int chargedAt() const;
	bool active() const;

	void id(const int id);
	void name(const QString name);
	void email(const QString email);
	void password(const QString password);
	void changePassword(const bool changePassword);
	void type(const EmployeeType type);
	void chargedAt(int chargedAt);
	void active(bool active);

	bool save();
	bool activate();
	bool deactivate();

private:
	int mId;
	QString mName;
	QString mEmail;
	QString mPassword;
	bool mChangePassword;
	EmployeeType mType;
	int mChargedAt;
	bool mActive;
};