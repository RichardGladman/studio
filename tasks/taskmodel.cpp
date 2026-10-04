/* ===================================== 
 *	taskmodel.cpp
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */

#include "taskmodel.h"
#include "taskrepository.h"

QList<ListData> TaskModel::list(QString searchFor) 
{
	return TaskRepository::list(searchFor);
}

QList<ListData> TaskModel::list(int projectId) 
{
	return TaskRepository::list(projectId);
}

QList<ListData> TaskModel::list(QList<int> projectIds)
{
	return TaskRepository::list(projectIds);
}

TaskModel TaskModel::load(int id) 
{
	return TaskRepository::load(id);
}

TaskModel::TaskModel(int id, QString name, QString description, int projectId) : 
		mId {id}, mName {name}, mDescription {description}, mProjectId {projectId} {}
TaskModel::TaskModel(QString name, QString description, int projectId) : TaskModel {0, name, description, projectId} {}
TaskModel::TaskModel() : TaskModel {0, "", "", 0} {}

int TaskModel::id() const 
{
	return mId;
}

QString TaskModel::name() const 
{
	return mName;
}

QString TaskModel::description() const 
{
	return mDescription;
}

int TaskModel::projectId() const
{
	return mProjectId;
}

void TaskModel::id(int id) 
{
	mId = id;
}

void TaskModel::name(QString name) {
	mName = name;
}

void TaskModel::description(QString description) 
{
	mDescription = description;
}

void TaskModel::projectId(int projectId) 
{
	mProjectId = projectId;
}

bool TaskModel::save() 
{
	if (mId == 0) {
		return TaskRepository::insert(this);
	} else {
		return TaskRepository::update(this);
	}
}

