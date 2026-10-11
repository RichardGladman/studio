/* =====================================
 *	teamfrepository.cpp
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */

#include "teamrepository.h"
#include "qsqlquery.h"
#include "teammodel.h"

#include <QSqlQuery>

void TeamRepository::createStore()
{
    QString sql = "CREATE TABLE IF NOT EXISTS projects_staff ("
                    "staff_id INTEGER," 
                    "project_id INTEGER,"
                    "role INTEGER,"
                   " active INTEGER,"
                    "PRIMARY KEY(staff_id, project_id),"
                    "FOREIGN KEY (staff_id) REFERENCES staff(id),"
                    "FOREIGN KEY (project_id) REFERENCES projects(id)"
                ");";

    QSqlQuery query;
    query.prepare(sql);
    query.exec();
}

TeamModel TeamRepository::load(int staffId, int projectId)
{
    TeamModel model {};
    QSqlQuery query;

    query.prepare("SELECT * FROM projects_staff WHERE staff_id=? AND project_id=?");
    query.addBindValue(staffId);
    query.addBindValue(projectId);

    if (query.exec() && query.next()) {
        model.staffId(query.value(0).toInt());
        model.projectId(query.value(1).toInt());
        model.role(static_cast<StaffRole>(query.value(2).toInt()));
        model.active(query.value(3).toBool());
    }

    return model;
}

bool TeamRepository::insert(TeamModel *model)
{
    QString sql = "INSERT INTO projects_staff(project_id, staff_id, role, active) VALUES(?, ?, ?, 1)";
    QSqlQuery query;

    query.prepare(sql);

    query.addBindValue(model->projectId());
    query.addBindValue(model->staffId());
    query.addBindValue(static_cast<int>(model->role()));

    return query.exec();
}

bool TeamRepository::update(TeamModel *model)
{
    QString sql = "UPDATE projects_staff SET role=?, active=? WHERE project_id=? AND staff_id=?";
    QSqlQuery query;

    query.prepare(sql);

    query.addBindValue(static_cast<int>(model->role()));
    query.addBindValue(model->active());
    query.addBindValue(model->projectId());
    query.addBindValue(model->staffId());

    return query.exec();
}

bool TeamRepository::activate(int project_id, int staff_id)
{
	QSqlQuery query;
	query.prepare("UPDATE projects_staff SET active=1 WHERE project_id=? AND staff_id=?");
	query.addBindValue(project_id);
    query.addBindValue(staff_id);
	
    return query.exec();
}

bool TeamRepository::deactivate(int project_id, int staff_id)
{
	QSqlQuery query;
	query.prepare("UPDATE projects_staff SET active=0 WHERE project_id=? AND staff_id=?");
	query.addBindValue(project_id);
    query.addBindValue(staff_id);
	
    return query.exec();
}
