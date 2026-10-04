/* =====================================
 *	tasktimermodel.h
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */

#ifndef TASKTIMER_TASKTIMERMODEL_H_
#define TASKTIMER_TASKTIMERMODEL_H_

#include "../reports/reportitem.h"

#include <qtypes.h>
#include <QList>
#include <QDate>

class TaskTimerModel
{
public:
	static TaskTimerModel getRunning();
	static QList<ReportItem> list(QList<int> projectIds);
	static QList<ReportItem> list(QDate from, QDate to);
	
	TaskTimerModel(int id, int task_id, qint64 start, qint64 stop);
	
	int id() const;
	int taskId() const;
	qint64 starttime() const;
	qint64 stoptime() const;
	
	void id(int id);
	void taskId(int taskId);
	void starttime(qint64 start);
	void stoptime(qint64 stop);
	
	bool start();
	bool stop();
	
private:
	int mId;
	int mTaskId;
	qint64 mStarttime;
	qint64 mStoptime;
};

#endif /* TASKTIMER_TASKTIMERMODEL_H_ */
