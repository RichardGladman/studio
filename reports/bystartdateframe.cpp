/* =====================================
 *	frame.cpp
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */

#include "bystartdateframe.h"
#include "exporter.h"
#include "reportitem.h"
#include "../tasktimer/tasktimermodel.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <QDate>

ByStartDateFrame::ByStartDateFrame(QWidget* parent) : QFrame(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
	QHBoxLayout *criteriaLayout = new QHBoxLayout(this);

	QLabel *fromLabel = new QLabel("From", this);
	criteriaLayout->addWidget(fromLabel);

	fromDateEdit = new QDateEdit(this);
	fromDateEdit->setDate(QDate::currentDate());
	criteriaLayout->addWidget(fromDateEdit);

	QLabel *toLabel = new QLabel("To", this);
	criteriaLayout->addWidget(toLabel);

	toDateEdit = new QDateEdit(this);
	toDateEdit->setDate(QDate::currentDate());
	criteriaLayout->addWidget(toDateEdit);
	
	QPushButton *generateButton = new QPushButton("Generate", this);
	connect(generateButton, &QPushButton::clicked, this, &ByStartDateFrame::generateReport);
	criteriaLayout->addWidget(generateButton);

	mainLayout->addLayout(criteriaLayout);
	
	listWidget = new QListWidget(this);
	mainLayout->addWidget(listWidget);
	
	QHBoxLayout *exportLayout = new QHBoxLayout(this);
	
	exportButton = new QPushButton("Export", this);
	exportButton->setDisabled(true);
	connect(exportButton, &QPushButton::clicked, this, [&](){
		runExport(false);
	});
	
	exportFormattedButton = new QPushButton("Export Formatted", this);
	exportFormattedButton->setDisabled(true);
	connect(exportFormattedButton, &QPushButton::clicked, this, [&](){
		runExport(true);
	});

	exportLayout->addWidget(exportFormattedButton);
	exportLayout->addWidget(exportButton);
	
	mainLayout->addLayout(exportLayout);
}

void ByStartDateFrame::generateReport()
{
	listWidget->clear();

	QDate fromDate = fromDateEdit->date();
	QDate toDate = toDateEdit->date();

	qDebug() << fromDate;

	QList<ReportItem> reportItems = TaskTimerModel::list(fromDate, toDate);
	
	if (reportItems.length() > 0) {
		QString lastProject = "";
		QString lastTask = "";
		
		for (const ReportItem &reportItem: reportItems) {
			if (reportItem.project != lastProject) {
				listWidget->addItem(reportItem.project);
				lastProject = reportItem.project;
			}
			
			if (reportItem.task != lastTask) {
				listWidget->addItem("\t" + reportItem.task);
				lastTask = reportItem.task;
			}
			
			QString start = QDateTime::fromMSecsSinceEpoch(reportItem.startTime).toString("dd/MM/yyyy hh:mm");
			QString end = QDateTime::fromMSecsSinceEpoch(reportItem.endTime).toString("dd/MM/yyyy hh:mm");
			
			long long minutes = reportItem.elapsedTime / 1000 / 60;
			long long hours = minutes / 60;

			minutes %= 60;
			
			QString formattedMinutes;
			formattedMinutes = (minutes < 10) ? "0" + QString::number(minutes) : QString::number(minutes);
			
			QString formattedHours;
			formattedHours = (hours < 10) ? "0" + QString::number(hours) : QString::number(hours);

			listWidget->addItem("\t\t" + start + ", " + end + ", " + formattedHours + ":" + formattedMinutes);
			
			exportButton->setDisabled(false);
			exportFormattedButton->setDisabled(false);
		}
	} else {
		exportButton->setDisabled(true);
		exportFormattedButton->setDisabled(true);
	}
}

void ByStartDateFrame::runExport(bool formatted)
{
	QString filepath = QFileDialog::getSaveFileName(this, "Select File", "", "CSV Files (*.csv)");
	if (filepath.isEmpty()) return;
	
	Exporter exporter {filepath};
	
	if (formatted) {
		exporter.writeFormatted(reportItems);
	} else {
		exporter.write(reportItems);
	}
	
	QMessageBox::information(this, "Export Completed", "Exported to " + filepath);
}

