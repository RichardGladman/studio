/* =====================================
 *	reportitem.h
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */

#ifndef REPORTS_REPORTITEM_H_
#define REPORTS_REPORTITEM_H_

#include <QString>

struct ReportItem
{
	QString project;
	QString task;
	long long startTime;
	long long endTime;
	long long elapsedTime;
};

#endif /* REPORTS_REPORTITEM_H_ */
