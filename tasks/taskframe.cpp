/* =====================================
 *	taskframe.cpp
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */

#include "taskframe.h"
#include "taskmodel.h"
#include "../projects/projectmodel.h"
#include "../common/listdata.h"
#include "../tasktimer/tasktimermodel.h"
#include "taskform.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QGroupBox>
#include <QMessageBox>

#include <QDebug>
#include <qnamespace.h>

TaskFrame::TaskFrame(QWidget* parent) : QFrame(parent)
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

	QGroupBox *groupBox = new QGroupBox(this);
	groupBox->setTitle("");
	
	mainLayout->addWidget(groupBox);
	
	QHBoxLayout *searchLayout = new QHBoxLayout(this);
	groupBox->setLayout(searchLayout);
	
	projectsCombobox = new QComboBox(this);
	loadProjectsData();
	connect(projectsCombobox, &QComboBox::currentIndexChanged, this, &TaskFrame::loadTasksForProject);
	searchLayout->addWidget(projectsCombobox);
	
	searchLineEdit = new QLineEdit(this);
	searchLineEdit->setPlaceholderText(tr("Search for tasks"));
	searchLayout->addWidget(searchLineEdit);
	
	searchButton = new QPushButton(tr("Search"), this);
	connect(searchButton, &QPushButton::clicked, this, [&](){
		loadData(searchLineEdit->text());
	});
	searchLayout->addWidget(searchButton);

	listWidget = new QListWidget(this);
	connect(listWidget, &QListWidget::itemDoubleClicked, this, &TaskFrame::handleItemDoubleClicked);
	listWidget->clear();
	
	loadData();
		
	QHBoxLayout *controlLayout = new QHBoxLayout(this);

	QPushButton *viewButton = new QPushButton(tr("View"), this);
	connect(viewButton, &QPushButton::clicked, this, &TaskFrame::handleViewClicked);
	controlLayout->addWidget(viewButton);
	
	QPushButton *addButton = new QPushButton(tr("New"), this);
	connect(addButton, &QPushButton::clicked, this, &TaskFrame::handleAddClicked);
	controlLayout->addWidget(addButton);
	
	QPushButton *editButton = new QPushButton(tr("Edit"), this);
	connect(editButton, &QPushButton::clicked, this, &TaskFrame::handleEditClicked);
	controlLayout->addWidget(editButton);
	
	mainLayout->addWidget(listWidget);
	mainLayout->addLayout(controlLayout);
}	

TaskFrame::~TaskFrame()
{
}

void TaskFrame::handleSearchClicked()
{
	QString searchFor = searchLineEdit->text().toLower();
	loadData(searchFor);
}

void TaskFrame::handleViewClicked()
{
	if (listWidget->currentItem() == nullptr) return;
	
	int id = listWidget->currentItem()->data(Qt::UserRole).toInt();
	
	TaskForm *dialog = new TaskForm(this, id, "view");
	dialog->exec();
}

void TaskFrame::handleAddClicked()
{
	if (projectsCombobox->currentText() == "Select Project...") return;
	
	QString projectName = projectsCombobox->currentText();
	int projectId = projectsCombobox->currentData().toInt();
	
	TaskForm *dialog = new TaskForm(this, 0, "edit", projectId, projectName);
	dialog->exec();
	loadTasksForProject();
}

void TaskFrame::handleEditClicked()
{
	if (projectsCombobox->currentText() == "Select Project...") return;
	if (listWidget->currentItem() == nullptr) return;

	QString projectName = projectsCombobox->currentText();
	int projectId = projectsCombobox->currentData().toInt();
	
	int id = listWidget->currentItem()->data(Qt::UserRole).toInt();

	TaskForm *dialog = new TaskForm(this, id, "Edit",	projectId, projectName);
	dialog->exec();
	loadTasksForProject();
}

void TaskFrame::handleItemDoubleClicked()
{
	if (projectsCombobox->currentText() == "Select Project...") return;
	if (listWidget->currentItem() == nullptr) return;
	
	int taskId = listWidget->currentItem()->data(Qt::UserRole).toInt();
	TaskTimerModel taskTimerModel = TaskTimerModel::getRunning();
	
	if (taskTimerModel.id() == -1) {
		taskTimerModel = TaskTimerModel {0, taskId, -1, -1};
		taskTimerModel.start();
	} else {
		taskTimerModel.stop();
		
		if (taskId != taskTimerModel.taskId()) {
			taskTimerModel = TaskTimerModel {0, taskId, -1 , -1};
			taskTimerModel.start();
		}
	}
	
	loadTasksForProject();
	
}

void TaskFrame::loadData(QString searchFor)
{
	listWidget->clear();

	if (projectsCombobox->currentText() == "Select Project...") return;
	
	QList<ListData> tasks = TaskModel::list(searchFor);
	TaskTimerModel taskTimerModel = TaskTimerModel::getRunning();

	for (const ListData &task: tasks) {
		QString itemText = task.name;
		if (taskTimerModel.taskId() == task.id) {
			itemText += " (Running)";
		}
		
		QListWidgetItem *item = new QListWidgetItem(itemText, listWidget);
		item->setData(Qt::UserRole, task.id);
		listWidget->addItem(item);
	}
}


void TaskFrame::loadProjectsData()
{
	QList<ListData> projects = ProjectModel::list("", false);
	
	projectsCombobox->clear();
	projectsCombobox->addItem("Select Project...");
	for (const ListData &project: projects) {
		projectsCombobox->addItem(project.name, QVariant(project.id));
	}
}

void TaskFrame::loadTasksForProject()
{
	listWidget->clear();

	if (projectsCombobox->currentText() == "Select Project...") return;
	
	QList<ListData> tasks = TaskModel::list(projectsCombobox->currentData().toInt());
	TaskTimerModel taskTimerModel = TaskTimerModel::getRunning();
	
	for (const ListData &task: tasks) {
		QString itemText = task.name;
		
		if (taskTimerModel.taskId() == task.id && taskTimerModel.stoptime() == -1) {
			itemText += " (Running)";
		}
		
		QListWidgetItem *item = new QListWidgetItem(itemText, listWidget);
		item->setData(Qt::UserRole, task.id);
		listWidget->addItem(item);
	}
}

