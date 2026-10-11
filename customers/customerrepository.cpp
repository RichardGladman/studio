/* =====================================
 *	customerrepository.cpp
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */

#include "customerrepository.h"
#include "customermodel.h"

#include <QSqlQuery>

void CustomerRepository::createStore() 
{
	QString sql = "CREATE TABLE IF NOT EXISTS customers (id INTEGER PRIMARY KEY AUTO_INCREMENT, name VARCHAR(255), member_type INTEGER, "
					"charged_at INTEGER, active INTEGER);";
	QSqlQuery query;
	query.prepare(sql);
	query.exec();
}

QList<ListData> CustomerRepository::list(QString searchFor, bool inactive) 
{ 
	QSqlQuery query;
	
	QString selectClause = "SELECT id, name FROM customers";
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

CustomerModel CustomerRepository::load(int id) 
{
	CustomerModel model {};
	QSqlQuery query;
	
	query.prepare("SELECT * FROM customers WHERE id=?");
	query.addBindValue(id);
	
	if (query.exec() && query.next()) {
		model.id(query.value(0).toInt());
		model.name(query.value(1).toString());
		model.chargedAt(query.value(2).toInt());
		model.active(query.value(3).toInt());
	}
	
	return model; 
}

bool CustomerRepository::insert(CustomerModel *model) 
{ 
	QSqlQuery query;
	
	query.prepare("INSERT INTO customers(name, charged_at, active) VALUES(?, ?, ?, 1)");
	
	query.addBindValue(model->name());
	query.addBindValue(model->chargedAt());
	
	return query.exec();
}

bool CustomerRepository::update(CustomerModel *model) 
{ 
	QSqlQuery query;

	query.prepare("UPDATE customers SET name=?, charged_at=? WHERE id=?");

	query.addBindValue(model->name());
	query.addBindValue(model->chargedAt());
	query.addBindValue(model->id());

	return query.exec();
}

bool CustomerRepository::activate(int id)
{
	QSqlQuery query;
	query.prepare("UPDATE customers SET active=1 WHERE id=?");
	query.addBindValue(id);
	return query.exec();
}

bool CustomerRepository::deactivate(int id)
{
	QSqlQuery query;
	query.prepare("UPDATE customers SET active=0 WHERE id=?");
	query.addBindValue(id);
	return query.exec();
}
