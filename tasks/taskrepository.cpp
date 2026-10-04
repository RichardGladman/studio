/* ===================================== 
 *	taskrepository.cpp
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */

#include "taskrepository.h"
#include "taskmodel.h"

#include <QSqlQuery>
#include <QSqlError>

void TaskRepository::createStore() 
{
	QString sql = "CREATE TABLE IF NOT EXISTS tasks (id INTEGER PRIMARY KEY, name VARCHAR(255), description TEXT, project_id INTEGER);";
	QSqlQuery query;
	query.prepare(sql);
	query.exec();
}

QList<ListData> TaskRepository::list(QString searchFor) 
{ 
	QSqlQuery query;
	
	QString selectClause = "SELECT id, name FROM tasks";
	QString orderClause = " ORDER BY name";
	QString whereClause = (searchFor == "") ? "" :  " WHERE name LIKE ?" ;

	query.prepare(selectClause + whereClause + orderClause);
	if (searchFor != "") {
		query.addBindValue("%" + searchFor.trimmed() + "%");
	}
	
	query.exec();
	
	QList<ListData> tasks;
	
	while (query.next()) {
		ListData data {query.value(0).toInt(), query.value(1).toString()};
		tasks.push_back(data);
	}
	
	return tasks; 
}

QList<ListData> TaskRepository::list(int projectId) 
{ 
	QSqlQuery query;
	
	QString selectClause = "SELECT id, name FROM tasks";
	QString orderClause = " ORDER BY name";
	QString whereClause = " WHERE project_id = ?" ;

	query.prepare(selectClause + whereClause + orderClause);
	query.addBindValue(projectId);
	
	query.exec();
	
	QList<ListData> tasks;
	
	while (query.next()) {
		ListData data {query.value(0).toInt(), query.value(1).toString()};
		tasks.push_back(data);
	}
	
	return tasks; 
}

QList<ListData> TaskRepository::list(QList<int> projectIds)
{
	QSqlQuery query;
	QString sql = "SELECT id, name FROM tasks WHERE project_id IN (";
	QString item = "?,";
	
	sql += item.repeated(projectIds.length());
	sql.chop(1);
	sql += ") ORDER BY name";
	
	query.prepare(sql);
		
	for (int i = 0; i < projectIds.length(); ++i) {
		query.addBindValue(projectIds.at(i));
	}
	
	if (!query.exec()) {
		qDebug() << "Query failed " << query.lastError();
	}
	
	QList<ListData> tasks;
	while (query.next()) {
		ListData data {query.value(0).toInt(), query.value(1).toString()};
		tasks.push_back(data);
	}
	
	return tasks; 
}

TaskModel TaskRepository::load(int id) 
{
	TaskModel model {};
	QSqlQuery query;
	
	query.prepare("SELECT * FROM tasks WHERE id=?");
	query.addBindValue(id);
	
	if (query.exec() && query.next()) {
		model.id(query.value(0).toInt());
		model.name(query.value(1).toString());
		model.description(query.value(2).toString());
	}
	
	return model; 
}

bool TaskRepository::insert(TaskModel *model) 
{ 
	QSqlQuery query;
	
	query.prepare("INSERT INTO tasks(name, description, project_id) VALUES(?, ?, ?)");
	
	query.addBindValue(model->name());
	query.addBindValue(model->description());
	query.addBindValue(model->projectId());
	
	return query.exec();
}

bool TaskRepository::update(TaskModel *model) 
{ 
	QSqlQuery query;

	query.prepare("UPDATE tasks SET name=?, description=?, project_id=? WHERE id=?");

	query.addBindValue(model->name());
	query.addBindValue(model->description());
	query.addBindValue(model->projectId());
	query.addBindValue(model->id());

	return query.exec();
}

