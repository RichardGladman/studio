/* =====================================
 *	teamfrepository.cpp
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */

#include "teamrepository.h"
#include "qdebug.h"
#include "qsqlquery.h"
#include "teamdata.h"
#include "teammodel.h"

#include <QSqlQuery>

void TeamRepository::createStore()
{
    QString sql = "CREATE TABLE IF NOT EXISTS projects_staff ("
                    "id INTEGER PRIMARY KEY AUTO_INCREMENT,"
                    "staff_id INTEGER," 
                    "project_id INTEGER,"
                    "role INTEGER,"
                   " active INTEGER,"
                    "FOREIGN KEY (staff_id) REFERENCES staff(id),"
                    "FOREIGN KEY (project_id) REFERENCES projects(id)"
                ");";

    QSqlQuery query;
    query.prepare(sql);
    query.exec();
}

QList<TeamData> TeamRepository::list(int projectId, bool inactive)
{
    QString sql = "SELECT ps.id, s.id, s.name FROM staff s INNER JOIN projects_staff ps ON s.id = ps.staff_id "
                    "WHERE ps.project_id=? AND ps.active=? ORDER BY s.name";
    QSqlQuery query;

    query.prepare(sql);
    query.addBindValue(projectId);
    query.addBindValue(!inactive);

    query.exec();

    QList<TeamData> team;

    while (query.next()) {
        TeamData data { query.value(0).toInt(),query.value(1).toInt(), query.value(2).toString()};
        team.push_back(data);
    }

    return team;
}

TeamModel TeamRepository::load(int id)
{
    TeamModel model {};
    QSqlQuery query;

    query.prepare("SELECT * FROM projects_staff WHERE id=?");
    query.addBindValue(id);

    if (query.exec() && query.next()) {
        model.id(query.value(0).toInt());
        model.staffId(query.value(1).toInt());
        model.projectId(query.value(2).toInt());
        model.role(static_cast<StaffRole>(query.value(3).toInt()));
        model.active(query.value(4).toBool());
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

    qDebug() << sql << " " << QString::number(model->projectId()) << " " << QString::number(model->staffId()) << " " << QString::number(static_cast<int>(model->role()));

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
