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

	StaffModel(QString name, EmployeeType type, double chargedAt, bool active, int id = 0);

	int id() const;
	QString name() const;
	EmployeeType type() const;
	double chargedAt() const;
	bool active() const;

	void id(const int id);
	void name(const QString name);
	void type(const EmployeeType type);
	void chargedAt(double chargedAt);
	void active(bool active);

	bool save();
	bool activate();
	bool deactivate();

private:
	int mId;
	QString mName;
	EmployeeType mType;
	double mChargedAt;
	bool mActive;
};