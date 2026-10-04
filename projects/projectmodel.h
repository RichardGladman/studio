/* ===================================== 
 *	projectmodel.h
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */

#ifndef PROJECTS_PROJECTMODEL_H_
#define PROJECTS_PROJECTMODEL_H_

#include <QString>
#include <QStringList>

#include "../common/listdata.h"

class ProjectModel
{
public:
	static QList<ListData> list(QString searchFor, bool inactive);
	static ProjectModel load(int id);

	ProjectModel(int id, QString name, QString description);
	ProjectModel(QString name, QString description);
	ProjectModel();
	
	int id() const;
	QString name() const;
	QString description() const;
	int active() const;
	
	void id(int id);
	void name(QString name);
	void description(QString description);
	void active(int active);
	
	bool save();
	bool activate();
	bool deactivate();
	
private:
	int mId;
	QString mName;
	QString mDescription;
	int mActive;
};

#endif /* PROJECTS_PROJECTMODEL_H_ */
