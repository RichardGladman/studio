/* =====================================
 *	tasktimerrepository.h
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */

#ifndef TASKTIMER_TASKTIMERREPOSITORY_H_
#define TASKTIMER_TASKTIMERREPOSITORY_H_

#include "../tasktimer/tasktimermodel.h"
#include "../reports/reportitem.h"

#include <QList>
#include <QDateTime>

class TaskTimerRepository
{
public:
	static void createStore();
	static TaskTimerModel getRunningTask();
	static bool start(int taskId, qint64 starttime);
	static bool stop(qint64 stoptime);
	
	static QList<ReportItem> list(QList<int> &taskIds);
	static QList<ReportItem> list(QDateTime from, QDateTime to);
};

#endif /* TASKTIMER_TASKTIMERREPOSITORY_H_ */
