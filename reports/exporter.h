/* =====================================
 *	exporter.h
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */

#ifndef REPORTS_EXPORTER_H_
#define REPORTS_EXPORTER_H_

#include "reportitem.h"

#include <QString>
#include <QList>

class Exporter
{
public:
	Exporter(QString filepath);
	
	bool write(const QList<ReportItem> &items);
	bool writeFormatted(const QList<ReportItem> &items);

private:
	QString mFilepath;
};

#endif /* REPORTS_EXPORTER_H_ */
