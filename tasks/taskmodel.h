/* ===================================== 
 *	taskmodel.h
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */

#ifndef TASK_TASKMODEL_H_
#define TASK_TASKMODEL_H_

#include <QString>
#include <QStringList>

#include "../common/listdata.h"

class TaskModel
{
public:
	static QList<ListData> list(QString searchFor);
	static QList<ListData> list(int projectId);
	static QList<ListData> list(QList<int> projectIds);
	
	static TaskModel load(int id);

	TaskModel(int id, QString name, QString description, int projectId);
	TaskModel(QString name, QString description, int projectId);
	TaskModel();
	
	int id() const;
	QString name() const;
	QString description() const;
	int projectId() const;
	
	void id(int id);
	void name(QString name);
	void description(QString description);
	void projectId(int projectId);
	
	bool save();
	
private:
	int mId;
	QString mName;
	QString mDescription;
	int mProjectId;
};

#endif /* PROJECTS_PROJECTMODEL_H_ */
