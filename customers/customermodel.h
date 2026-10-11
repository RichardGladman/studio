/* =====================================
 *	customermodel.h
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */

#pragma once

#include <QString>
#include <QStringList>

#include "../common/listdata.h"

class CustomerModel
{
public:
	static QList<ListData> list(QString searchFor, bool inactive);
	static CustomerModel load(int id);

	CustomerModel(QString name, int chargedAt, bool active, int id = 0);
	CustomerModel();

	int id() const;
	QString name() const;
	int chargedAt() const;
	bool active() const;

	void id(const int id);
	void name(const QString name);
	void chargedAt(int chargedAt);
	void active(bool active);

	bool save();
	bool activate();
	bool deactivate();

private:
	int mId;
	QString mName;
	int mChargedAt;
	bool mActive;
};