/* =====================================
 *	staffrepository.cpp
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */

#include "staffrepository.h"
#include "employeetype.hpp"
#include "staffmodel.h"

#include <QSqlQuery>

void StaffRepository::createStore() 
{
	QString sql = "CREATE TABLE IF NOT EXISTS staff (id INTEGER PRIMARY KEY, name VARCHAR(255), type INTEGER, "
					"charged_at INTEGER, active INTEGER);";
	QSqlQuery query;
	query.prepare(sql);
	query.exec();
}

QList<ListData> StaffRepository::list(QString searchFor, bool inactive) 
{ 
	QSqlQuery query;
	
	QString selectClause = "SELECT id, name FROM staff";
	QString orderClause = " ORDER BY name";
	QString whereClause = (searchFor == "") ? " WHERE active=?" :  " WHERE name LIKE ? AND active=?" ;

	query.prepare(selectClause + whereClause + orderClause);
	if (searchFor != "") {
		query.addBindValue("%" + searchFor.trimmed() + "%");
		query.addBindValue(!inactive);
	} else {
		query.addBindValue(!inactive);
	}
	
	query.exec();
	
	QList<ListData> staff;
	
	while (query.next()) {
		ListData data {query.value(0).toInt(), query.value(1).toString()};
		staff.push_back(data);
	}
	
	return staff; 
}

StaffModel StaffRepository::load(int id) 
{
	StaffModel model {};
	QSqlQuery query;
	
	query.prepare("SELECT * FROM staff WHERE id=?");
	query.addBindValue(id);
	
	if (query.exec() && query.next()) {
		model.id(query.value(0).toInt());
		model.name(query.value(1).toString());
		model.type(static_cast<EmployeeType>(query.value(2).toInt()));
		model.chargedAt(query.value(3).toInt());
		model.active(query.value(4).toInt());
	}
	
	return model; 
}

bool StaffRepository::insert(StaffModel *model) 
{ 
	QSqlQuery query;
	
	query.prepare("INSERT INTO staff(name, type, chargedAt, active) VALUES(?, ?, ?, ?, 1)");
	
	query.addBindValue(model->name());
	query.addBindValue(static_cast<int>(model->type()));
	query.addBindValue(model->chargedAt());
	
	return query.exec();
}

bool StaffRepository::update(StaffModel *model) 
{ 
	QSqlQuery query;

	query.prepare("UPDATE staff SET name=?, type=?, charged_at=? WHERE id=?");

	query.addBindValue(model->name());
	query.addBindValue(static_cast<int>(model->type()));
	query.addBindValue(model->chargedAt());
	query.addBindValue(model->id());

	return query.exec();
}

bool StaffRepository::activate(int id)
{
	QSqlQuery query;
	query.prepare("UPDATE staff SET active=1 WHERE id=?");
	query.addBindValue(id);
	return query.exec();
}

bool StaffRepository::deactivate(int id)
{
	QSqlQuery query;
	query.prepare("UPDATE staff SET active=0 WHERE id=?");
	query.addBindValue(id);
	return query.exec();
}
