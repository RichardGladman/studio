/* ===================================== 
 *	projectrepository.h
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */


#ifndef PROJECTS_PROJECTREPOSITORY_H_
#define PROJECTS_PROJECTREPOSITORY_H_

#include <QStringList>

#include "projectmodel.h"
#include "../common/listdata.h"

class ProjectRepository
{
public:
	static void createStore();
	
	static QList<ListData> list(QString searchFor, bool inactive = false);
	static ProjectModel load(int id);
	
	static bool insert(ProjectModel *model);
	static bool update(ProjectModel *model);
	static bool activate(int id);
	static bool deactivate(int id);
};

#endif /* PROJECTS_PROJECTREPOSITORY_H_ */
