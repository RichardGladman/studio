/* =====================================
 *	exporter.cpp
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */

#include "exporter.h"

#include <QDataStream>
#include <QDateTime>
#include <QFile>
#include <QIODevice>
#include <qfiledevice.h>
#include <qobject.h>

Exporter::Exporter(QString filepath) : mFilepath {filepath} {}

bool Exporter::write(const QList<ReportItem> &items)
{
	QFile file(mFilepath);
	if (!file.open(QIODevice::WriteOnly)) {
		return false;
	}
	
	QTextStream out(&file);
	out.setEncoding(QStringConverter::Utf8);
	
	out << "Project,Task,Start Time,End Time,Elapsed\n";
	
	for (const ReportItem &item: items) {
		QString start = QDateTime::fromMSecsSinceEpoch(item.startTime).toString("dd/MM/yyyy hh:mm");
		QString end = QDateTime::fromMSecsSinceEpoch(item.endTime).toString("dd/MM/yyyy hh:mm");
		
		long long minutes = item.elapsedTime / 1000 / 60;
		long long hours = minutes / 60;

		minutes %= 60;

		QString formattedMinutes;
		formattedMinutes = (minutes < 10) ? "0" + QString::number(minutes) : QString::number(minutes);

		QString formattedHours;
		formattedHours = (hours < 10) ? "0" + QString::number(hours) : QString::number(hours);
		
		out << item.project.toUtf8() << "," << item.task.toUtf8() << "," << start.toUtf8() 
			<< "," << end.toUtf8() << "," << formattedHours.toUtf8() << ":" << formattedMinutes.toUtf8() << "\n";
	}
	
	file.close();
	
	return true;
}

bool Exporter::writeFormatted(const QList<ReportItem> &items)
{
	QFile file(mFilepath);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		return false;
	}

	QTextStream out(&file);
	out.setEncoding(QStringConverter::Utf8);

	out << "Project,Task,Start Time,End Time,Duration\n";
	
	QString lastProject = "";
	QString lastTask = "";

	for (const ReportItem &item: items) {
		QString start = QDateTime::fromMSecsSinceEpoch(item.startTime).toString("dd/MM/yyyy hh:mm");
		QString end = QDateTime::fromMSecsSinceEpoch(item.endTime).toString("dd/MM/yyyy hh:mm");

		long long minutes = item.elapsedTime / 1000 / 60;
		long long hours = minutes / 60;

		minutes %= 60;

		QString formattedMinutes;
		formattedMinutes = (minutes < 10) ? "0" + QString::number(minutes) : QString::number(minutes);

		QString formattedHours;
		formattedHours = (hours < 10) ? "0" + QString::number(hours) : QString::number(hours);
		
		if (item.project != lastProject) {
			out << item.project.toUtf8() << "\n";
			lastProject = item.project;
		}
		
		if (item.task != lastTask) {
			out << "," << item.task.toUtf8() << "\n";
			lastTask = item.task;
		}
		
		out << ",," << start.toUtf8() << "," << end.toUtf8() << "," << formattedHours.toUtf8() 
			<< ":" << formattedMinutes.toUtf8() << "\n";
	}

	file.close();

	return true;
}