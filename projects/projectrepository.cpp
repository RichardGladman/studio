/* ===================================== 
 *	projectrepository.cpp
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */

#include "projectrepository.h"
#include "projectmodel.h"

#include <QSqlQuery>

void ProjectRepository::createStore() 
{
	QString sql = "CREATE TABLE IF NOT EXISTS projects (id INTEGER PRIMARY KEY, name VARCHAR(255), description TEXT, active INTEGER);";
	QSqlQuery query;
	query.prepare(sql);
	query.exec();
}

QList<ListData> ProjectRepository::list(QString searchFor, bool inactive) 
{ 
	QSqlQuery query;
	
	QString selectClause = "SELECT id, name FROM projects";
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
	
	QList<ListData> projects;
	
	while (query.next()) {
		ListData data {query.value(0).toInt(), query.value(1).toString()};
		projects.push_back(data);
	}
	
	return projects; 
}

ProjectModel ProjectRepository::load(int id) 
{
	ProjectModel model {};
	QSqlQuery query;
	
	query.prepare("SELECT * FROM projects WHERE id=?");
	query.addBindValue(id);
	
	if (query.exec() && query.next()) {
		model.id(query.value(0).toInt());
		model.name(query.value(1).toString());
		model.description(query.value(2).toString());
	}
	
	return model; 
}

bool ProjectRepository::insert(ProjectModel *model) 
{ 
	QSqlQuery query;
	
	query.prepare("INSERT INTO projects(name, description, active) VALUES(?, ?, 1)");
	
	query.addBindValue(model->name());
	query.addBindValue(model->description());
	
	return query.exec();
}

bool ProjectRepository::update(ProjectModel *model) 
{ 
	QSqlQuery query;

	query.prepare("UPDATE projects SET name=?, description=? WHERE id=?");

	query.addBindValue(model->name());
	query.addBindValue(model->description());
	query.addBindValue(model->id());

	return query.exec();
}

bool ProjectRepository::activate(int id)
{
	QSqlQuery query;
	query.prepare("UPDATE projects SET active=1 WHERE id=?");
	query.addBindValue(id);
	return query.exec();
}

bool ProjectRepository::deactivate(int id)
{
	QSqlQuery query;
	query.prepare("UPDATE projects SET active=0 WHERE id=?");
	query.addBindValue(id);
	return query.exec();
}
