/* ===================================== 
 *	taskrepository.h
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */


#ifndef TASKS_TASKREPOSITORY_H_
#define TASKS_TASKREPOSITORY_H_

#include <QStringList>

#include "taskmodel.h"
#include "../common/listdata.h"

class TaskRepository
{
public:
	static void createStore();
	
	static QList<ListData> list(QString searchFor);
	static QList<ListData> list(int projectId);
	static QList<ListData> list(QList<int> projectIds);
	
	static TaskModel load(int id);
	
	static bool insert(TaskModel *model);
	static bool update(TaskModel *model);
	static bool activate(int id);
	static bool deactivate(int id);
};

#endif /* PROJECTS_PROJECTREPOSITORY_H_ */
