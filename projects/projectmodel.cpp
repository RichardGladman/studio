/* ===================================== 
 *	projectmodel.cpp
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */

#include "projectmodel.h"
#include "projectrepository.h"

QList<ListData> ProjectModel::list(QString searchFor, bool inactive) 
{
	return ProjectRepository::list(searchFor, inactive);
}

ProjectModel ProjectModel::load(int id) 
{
	return ProjectRepository::load(id);
}

ProjectModel::ProjectModel(int id, QString name, QString description) : mId {id}, mName {name}, mDescription {description} {}
ProjectModel::ProjectModel(QString name, QString description) : ProjectModel {0, name, description} {}
ProjectModel::ProjectModel() : ProjectModel {0, "", ""} {}

int ProjectModel::id() const 
{
	return mId;
}

QString ProjectModel::name() const 
{
	return mName;
}

QString ProjectModel::description() const 
{
	return mDescription;
}

int ProjectModel::active() const 
{
	return mActive;
}

void ProjectModel::id(int id) 
{
	mId = id;
}

void ProjectModel::name(QString name) {
	mName = name;
}

void ProjectModel::description(QString description) 
{
	mDescription = description;
}

void ProjectModel::active(int active) 
{
	mActive = active;
}

bool ProjectModel::save() 
{
	if (mId == 0) {
		return ProjectRepository::insert(this);
	} else {
		return ProjectRepository::update(this);
	}
}

bool ProjectModel::activate() 
{
	return ProjectRepository::activate(mId);
}

bool ProjectModel::deactivate() 
{
	return ProjectRepository::deactivate(mId);
}
