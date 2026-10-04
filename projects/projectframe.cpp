#include "projectframe.h"
#include "projectmodel.h"
#include "../common/listdata.h"
#include "projectform.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QGroupBox>
#include <QMessageBox>

#include <QDebug>
#include <qnamespace.h>

ProjectFrame::ProjectFrame(QWidget* parent) : QFrame(parent)
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

	QGroupBox *groupBox = new QGroupBox(this);
	groupBox->setTitle("");
	
	mainLayout->addWidget(groupBox);
	
	QHBoxLayout *searchLayout = new QHBoxLayout(this);
	groupBox->setLayout(searchLayout);
	
	searchLineEdit = new QLineEdit(this);
	searchLineEdit->setPlaceholderText(tr("Search for projects"));
	searchLayout->addWidget(searchLineEdit);
	
	inactiveCheckBox = new QCheckBox(tr("Inactive"), this);
	searchLayout->addWidget(inactiveCheckBox);
	
	searchButton = new QPushButton(tr("Search"), this);
	connect(searchButton, &QPushButton::clicked, this, &ProjectFrame::handleSearchClicked);
	searchLayout->addWidget(searchButton);

	listWidget = new QListWidget(this);
	
	loadData();
		
	QHBoxLayout *controlLayout = new QHBoxLayout(this);

	QPushButton *viewButton = new QPushButton(tr("View"), this);
	connect(viewButton, &QPushButton::clicked, this, &ProjectFrame::handleViewClicked);
	controlLayout->addWidget(viewButton);
	
	QPushButton *addButton = new QPushButton(tr("New"), this);
	connect(addButton, &QPushButton::clicked, this, &ProjectFrame::handleAddClicked);
	controlLayout->addWidget(addButton);
	
	QPushButton *editButton = new QPushButton(tr("Edit"), this);
	connect(editButton, &QPushButton::clicked, this, &ProjectFrame::handleEditClicked);
	controlLayout->addWidget(editButton);
	
	QPushButton *deleteButton = new QPushButton(tr("Deactivate"), this);
	connect(deleteButton, &QPushButton::clicked, this, &ProjectFrame::handleDeleteClicked);
	controlLayout->addWidget(deleteButton);
	
	mainLayout->addWidget(listWidget);
	mainLayout->addLayout(controlLayout);
}	

ProjectFrame::~ProjectFrame()
{
}

void ProjectFrame::handleSearchClicked()
{
	QString searchFor = searchLineEdit->text().toLower();
	bool inactive = inactiveCheckBox->isChecked();
	
	loadData(searchFor, inactive);
}

void ProjectFrame::handleViewClicked()
{
	if (listWidget->currentItem() == nullptr) return;
	
	int id = listWidget->currentItem()->data(Qt::UserRole).toInt();
	
	ProjectForm *dialog = new ProjectForm(this, id, "view");
	dialog->exec();
}

void ProjectFrame::handleAddClicked()
{
	ProjectForm *dialog = new ProjectForm(this);
	dialog->exec();
	loadData();
}

void ProjectFrame::handleEditClicked()
{
	if (listWidget->currentItem() == nullptr) return;

	ProjectForm *dialog = new ProjectForm(this, listWidget->currentItem()->data(Qt::UserRole).toInt(), "Edit");
	dialog->exec();
	loadData();
}

void ProjectFrame::handleDeleteClicked()
{
	if (listWidget->currentItem() == nullptr) return;
	
	int id = listWidget->currentItem()->data(Qt::UserRole).toInt();
	ProjectModel model = ProjectModel::load(id);
	
	if (model.deactivate()) {
		QMessageBox::information(this, "Success", "Project deactivated");
		loadData();
	} else {
		QMessageBox::critical(this, "Error", "Project not deactivated");
	}
}

void ProjectFrame::loadData(QString searchFor, bool inactive)
{
	QList<ListData> projects = ProjectModel::list(searchFor, inactive);
	
	listWidget->clear();
	for (const ListData &project: projects) {
		QListWidgetItem *item = new QListWidgetItem(project.name, listWidget);
		item->setData(Qt::UserRole, project.id);
		listWidget->addItem(item);
	}
}
