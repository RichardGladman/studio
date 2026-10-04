/* =====================================
 *	tasktimermodel.cpp
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */

#include "tasktimermodel.h"
#include "tasktimerrepository.h"

#include <QDateTime>
#include <QTime>

TaskTimerModel TaskTimerModel::getRunning()
{
	return TaskTimerRepository::getRunningTask();
}

QList<ReportItem> TaskTimerModel::list(QList<int> projectIds)
{
	return TaskTimerRepository::list(projectIds);
}
QList<ReportItem> TaskTimerModel::list(QDate from, QDate to)
{
	QDateTime fromTime = QDateTime(from, QTime(0, 0, 0, 0));
	QDateTime toTime = QDateTime(to, QTime(23, 59, 59, 999));

	return TaskTimerRepository::list(fromTime, toTime);
}

TaskTimerModel::TaskTimerModel(int id, int taskId, qint64 start, qint64 stop) :
								mId {id}, mTaskId {taskId}, mStarttime {start}, mStoptime {stop} {}							

int TaskTimerModel::id() const 
{
	return mId;
}

int TaskTimerModel::taskId() const
{
	return mTaskId;
}

qint64 TaskTimerModel::starttime() const
{
	return mStarttime;
}

qint64 TaskTimerModel::stoptime() const
{
	return mStoptime;
}

void TaskTimerModel::id(int id)
{
	mId = id;
}

void TaskTimerModel::taskId(int taskId)
{
	mTaskId = taskId;
}

void TaskTimerModel::starttime(qint64 start)
{
	mStarttime = start;
}

void TaskTimerModel::stoptime(qint64 stop)
{
	mStoptime = stop;
}

bool TaskTimerModel::start()
{
	qint64 timestamp = QDateTime::currentDateTime().toMSecsSinceEpoch();
	return TaskTimerRepository::start(mTaskId, timestamp);
}

bool TaskTimerModel::stop()
{
	qint64 timestamp = QDateTime::currentDateTime().toMSecsSinceEpoch();
	return TaskTimerRepository::stop(timestamp);
}


