/* =====================================
 *	customerrepository.cpp
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */

#include "customerrepository.h"
#include "customermodel.h"
#include "../address/addressmodel.h"

#include <QSqlQuery>

void CustomerRepository::createStore() 
{
	QString sql = "CREATE TABLE IF NOT EXISTS customers (id INTEGER PRIMARY KEY AUTO_INCREMENT, name VARCHAR(255), street_address VARCHAR(255), "
					"area VARCHAR(255), town VARCHAR(255), county VARCHAR(50), postcode VARCHAR(10), phone_number VARCHAR(25), "
					"email VARCHAR(255), active INTEGER);";
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
	
	QList<ListData> customers;
	
	while (query.next()) {
		ListData data {query.value(0).toInt(), query.value(1).toString()};
		customers.push_back(data);
	}
	
	return customers; 
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
		AddressModel address { query.value(2).toString(), query.value(3).toString(), query.value(4).toString(),
								query.value(5).toString(), query.value(6).toString() };
		model.address(address);
		model.phoneNumber(query.value(7).toString());
		model.email(query.value(8).toString());
		model.active(query.value(3).toInt());
	}
	
	return model; 
}

bool CustomerRepository::insert(CustomerModel *model) 
{ 
	QSqlQuery query;
	
	query.prepare("INSERT INTO customers(name, street_address, area, town, county, postcode, phone_number, email, active) "
							"VALUES(?, ?, ?, ?, ?, ?, ?, ?, 1)");
	
	query.addBindValue(model->name());
	query.addBindValue(model->address().streetAddress());
	query.addBindValue(model->address().area());
	query.addBindValue(model->address().town());
	query.addBindValue(model->address().county());
	query.addBindValue(model->address().postcode());
	query.addBindValue(model->phoneNumber());
	query.addBindValue(model->email());
	
	return query.exec();
}

bool CustomerRepository::update(CustomerModel *model) 
{ 
	QSqlQuery query;

	query.prepare("UPDATE customers SET name=?, street_address=?, area=?, town=?, county=?, postcode=?, "
					"phone_number=?, email=? WHERE id=?");

	query.addBindValue(model->name());
	query.addBindValue(model->address().streetAddress());
	query.addBindValue(model->address().area());
	query.addBindValue(model->address().town());
	query.addBindValue(model->address().county());
	query.addBindValue(model->address().postcode());
	query.addBindValue(model->phoneNumber());
	query.addBindValue(model->email());
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
