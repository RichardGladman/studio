/* =====================================
 *	tasktimerrepository.cpp
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */


#include "../tasktimer/tasktimerrepository.h"
#include "../tasktimer/tasktimermodel.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <qlogging.h>

void TaskTimerRepository::createStore() 
{
	QString sql = "CREATE TABLE IF NOT EXISTS tasktimings (id INTEGER PRIMARY KEY, task_id INTEGER, start INTEGER, stop INTEGER);";
	QSqlQuery query;
	query.prepare(sql);
	query.exec();
}

TaskTimerModel TaskTimerRepository::getRunningTask()
{
	TaskTimerModel model {-1, -1, -1, -1};
	QSqlQuery query;

	query.prepare("SELECT * FROM tasktimings WHERE stop=-1");

	if (query.exec() && query.next()) {
		model.id(query.value(0).toInt());
		model.taskId(query.value(1).toInt());
		model.starttime(query.value(2).toInt());
		model.stoptime(query.value(3).toInt());
	}

	return model; 
}

bool TaskTimerRepository::start(int taskId, qint64 starttime)
{
	QString sql = "INSERT INTO tasktimings (task_id, start, stop) VALUES(?, ?, -1)";
	QSqlQuery query;
	
	query.prepare(sql);
	query.addBindValue(taskId);
	query.addBindValue(starttime);
	
	return query.exec();
}

bool TaskTimerRepository::stop(qint64 stoptime)
{
	QString sql = "UPDATE tasktimings SET stop=? WHERE stop=-1";
	QSqlQuery query;
	
	query.prepare(sql);
	query.addBindValue(stoptime);
	
	return query.exec();
}

QList<ReportItem> TaskTimerRepository::list(QList<int> &taskIds)
{
	QString sql = "SELECT projects.name, tasks.name, tasktimings.start, tasktimings.stop FROM taskTimings "
					"INNER JOIN tasks ON tasktimings.task_id = tasks.id "
					"INNER JOIN projects ON tasks.project_id = projects.id "
					"WHERE tasktimings.stop != -1 AND tasktimings.task_id IN (";
	QString item = "?,";
	
	sql += item.repeated(taskIds.length());
	sql.chop(1);
	sql += ") ORDER BY projects.name, tasks.name";
	
	QSqlQuery query;
	query.prepare(sql);
	
	for (const int &id: taskIds) {
		query.addBindValue(id);
	}
	
	if (!query.exec()) {
		qDebug() << query.lastError();
	}
	
	QList<ReportItem> reportData;
	
	while(query.next()) {
		ReportItem reportItem {query.value(0).toString(),
								query.value(1).toString(),
								query.value(2).toLongLong(),
								query.value(3).toLongLong(),
								query.value(3).toLongLong() - query.value(2).toLongLong()};
		reportData.append(reportItem);
	}
	
	return reportData;
}

QList<ReportItem> TaskTimerRepository::list(QDateTime from, QDateTime to)
{
	QString sql = "SELECT projects.name, tasks.name, tasktimings.start, tasktimings.stop FROM taskTimings "
					"INNER JOIN tasks ON tasktimings.task_id = tasks.id "
					"INNER JOIN projects ON tasks.project_id = projects.id "
					"WHERE tasktimings.stop != -1 AND tasktimings.start BETWEEN ? AND ? ORDER BY projects.name, tasks.name";

	QSqlQuery query;
	query.prepare(sql);

	query.addBindValue(from.toMSecsSinceEpoch());
	query.addBindValue(to.toMSecsSinceEpoch());
	
	if (!query.exec()) {
		qDebug() << query.lastError();
		return QList<ReportItem> {};
	}

	QList<ReportItem> reportData;
	
	while(query.next()) {
		ReportItem reportItem {query.value(0).toString(),
								query.value(1).toString(),
								query.value(2).toLongLong(),
								query.value(3).toLongLong(),
								query.value(3).toLongLong() - query.value(2).toLongLong()};
		reportData.append(reportItem);
	}
	
	return reportData;
}
