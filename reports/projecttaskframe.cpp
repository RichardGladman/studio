/* =====================================
 *	projecttaskframe.cpp
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */

#include "projecttaskframe.h"
#include "../common/listdata.h"
#include "exporter.h"
#include "../projects/projectmodel.h"
#include "reportitem.h"
#include "../tasks/taskmodel.h"
#include "../tasktimer/tasktimermodel.h"

#include <QHBoxLayout>
#include <QListWidget>
#include <QVBoxLayout>
#include <QDebug>
#include <QDateTime>
#include <QFileDialog>
#include <QMessageBox>

ProjectTaskFrame::ProjectTaskFrame(QWidget *parent): QFrame(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
	
	QHBoxLayout *criteriaLayout = new QHBoxLayout(this);
	
	projectsCombo = new QComboBox(this);
	connect(projectsCombo, &QComboBox::currentIndexChanged, this, &ProjectTaskFrame::loadTasks);
	
	tasksCombo = new QComboBox(this);
	
	inactiveCheckbox = new QCheckBox("Inactive", this);
	connect(inactiveCheckbox, &QCheckBox::toggled, this, &ProjectTaskFrame::loadProjects);
	
	QPushButton *generateButton = new QPushButton("Generate", this);
	connect(generateButton, &QPushButton::clicked, this, &ProjectTaskFrame::generateReport);
	
	criteriaLayout->addWidget(projectsCombo);
	criteriaLayout->addWidget(tasksCombo);
	criteriaLayout->addWidget(inactiveCheckbox);
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
	
	loadProjects();
}

void ProjectTaskFrame::loadProjects()
{
	bool inactive = inactiveCheckbox->isChecked();
	QList<ListData> projects = ProjectModel::list("", inactive);

	projectsCombo->clear();
	tasksCombo->clear();
	projectsCombo->addItem("Select Project...");
	projectsCombo->addItem("All Projects");
	
	for (const ListData &project: projects) {
		projectsCombo->addItem(project.name, QVariant(project.id));
	}

}

void ProjectTaskFrame::loadTasks()
{
	tasksCombo->clear();
	if (projectsCombo->currentText() == "Select Project...") return;
	
	QList<int> projectIds;
	
	if (projectsCombo->currentText() == "All Projects") {
		for (int i = 0; i < projectsCombo->count(); ++i) {
			int data = projectsCombo->itemData(i, Qt::UserRole).toInt();
			if (data != 0) {
				projectIds.append(data);
			}
		}
	} else {
		projectIds.append(projectsCombo->currentData().toInt());
	}
	
	QList<ListData> tasks = TaskModel::list(projectIds);
	
	if (tasks.length() > 0) {
		tasksCombo->addItem("Select Task...");
		tasksCombo->addItem("All Tasks");
		
		for (const ListData &task: tasks) {
			tasksCombo->addItem(task.name, QVariant(task.id));
		}
	} else {
		tasksCombo->addItem("No tasks found");
	}
}

void ProjectTaskFrame::generateReport()
{
	listWidget->clear();
	if (tasksCombo->currentText() == "Select Task...") return;

	QList<int> taskIds;
	
	if (tasksCombo->currentText() == "All Tasks") {
		for (int i = 0; i < tasksCombo->count(); ++i) {
			int data = tasksCombo->itemData(i, Qt::UserRole).toInt();
			if (data != 0) {
				taskIds.append(data);
			}
		}
	} else {
		taskIds.append(tasksCombo->currentData().toInt());
	}

	timings = TaskTimerModel::list(taskIds);
	
	if (timings.length() > 0) {
		QString lastProject = "";
		QString lastTask = "";
		
		for (const ReportItem &timing: timings) {
			if (timing.project != lastProject) {
				listWidget->addItem(timing.project);
				lastProject = timing.project;
			}
			
			if (timing.task != lastTask) {
				listWidget->addItem("\t" + timing.task);
				lastTask = timing.task;
			}
			
			QString start = QDateTime::fromMSecsSinceEpoch(timing.startTime).toString("dd/MM/yyyy hh:mm");
			QString end = QDateTime::fromMSecsSinceEpoch(timing.endTime).toString("dd/MM/yyyy hh:mm");
			
			long long minutes = timing.elapsedTime / 1000 / 60;
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
		tasksCombo->addItem("No tasks found");
		exportButton->setDisabled(true);
		exportFormattedButton->setDisabled(true);
	}
}

void ProjectTaskFrame::runExport(bool formatted)
{
	QString filepath = QFileDialog::getSaveFileName(this, "Select File", "", "CSV Files (*.csv)");
	if (filepath.isEmpty()) return;
	
	Exporter exporter {filepath};
	
	if (formatted) {
		exporter.writeFormatted(timings);
	} else {
		exporter.write(timings);
	}
	
	QMessageBox::information(this, "Export Completed", "Exported to " + filepath);
}