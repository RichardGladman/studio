/* =====================================
 *	teamframe.cpp
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */

#include "qlistwidget.h"
#include "teamdata.h"
#include "teamframe.h"
#include "teamform.h"
#include "teammodel.h"

#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QListWidget>
#include <QListWidgetItem>
#include <QGroupBox>
#include <QMessageBox>
#include <QtCore/qnamespace.h>

TeamFrame::TeamFrame(QWidget* parent, int projectId): QDialog(parent), mProjectId(projectId) {
        QVBoxLayout* mainLayout = new QVBoxLayout(this);

	QGroupBox *groupBox = new QGroupBox(this);
	groupBox->setTitle("");
	
	mainLayout->addWidget(groupBox);
	
	QHBoxLayout *searchLayout = new QHBoxLayout(this);
	groupBox->setLayout(searchLayout);
	
	searchLineEdit = new QLineEdit(this);
	searchLineEdit->setPlaceholderText(tr("Search for team members"));
	searchLayout->addWidget(searchLineEdit);
	
	inactiveCheckBox = new QCheckBox(tr("Inactive"), this);
	searchLayout->addWidget(inactiveCheckBox);
	
	searchButton = new QPushButton(tr("Search"), this);
	connect(searchButton, &QPushButton::clicked, this, &TeamFrame::load);
	searchLayout->addWidget(searchButton);

	listWidget = new QListWidget(this);
	connect(listWidget, &QListWidget::itemClicked, this, &TeamFrame::handleItemClicked);
	
	load();
		
	QHBoxLayout *controlLayout = new QHBoxLayout(this);

	QPushButton *addButton = new QPushButton(tr("New"), this);
	connect(addButton, &QPushButton::clicked, this, &TeamFrame::showAddForm);
	controlLayout->addWidget(addButton);
	
	QPushButton *editButton = new QPushButton(tr("Edit"), this);
	connect(editButton, &QPushButton::clicked, this, &TeamFrame::showEditForm);
	controlLayout->addWidget(editButton);
	
	deleteButton = new QPushButton(tr("Deactivate"), this);
	connect(deleteButton, &QPushButton::clicked, this, &TeamFrame::deactivate);
	controlLayout->addWidget(deleteButton);
	
	mainLayout->addWidget(listWidget);
	mainLayout->addLayout(controlLayout);

}

TeamFrame::~TeamFrame() {}

void TeamFrame::handleCloseButtonClicked() {
    reject();
}

void TeamFrame::setupUI() {}

void TeamFrame::showAddForm() 
{
    TeamForm *form = new TeamForm(this, mProjectId, 0);
    form->exec();
    load();

}

void TeamFrame::showEditForm() 
{
   	if (listWidget->currentItem() == nullptr) return;

	TeamModel model = TeamModel::load(listWidget->currentItem()->data(Qt::UserRole).toInt());
	TeamForm *form = new TeamForm(this, model.projectId(), model.id(), model.staffId(), "Edit");
	form->exec();
	load();
}

void TeamFrame::deactivate() {
	if (listWidget->currentItem() == nullptr) return;

	TeamModel model = TeamModel::load(listWidget->currentItem()->data(Qt::UserRole).toInt());
	QString name = listWidget->currentItem()->text();
	qDebug() << QString::number(model.id()) << " " << QString::number(model.projectId()) << " " << QString::number(model.staffId());
	
	if (model.deactivate()) {
		QMessageBox::information(this, tr("Success"), name +  tr(" deactivated"));
		load();
	} else {
		QMessageBox::critical(this, tr("Error"), name + tr(" not deactivated"));
	}

	load();
}

void TeamFrame::activate() {
	if (listWidget->currentItem() == nullptr) return;

	TeamModel model = TeamModel::load(listWidget->currentItem()->data(Qt::UserRole).toInt());
	QString name = listWidget->currentItem()->text();
	qDebug() << QString::number(model.id()) << " " << QString::number(model.projectId()) << " " << QString::number(model.staffId());
	
	if (model.activate()) {
		QMessageBox::information(this, tr("Success"), name +  tr(" deactivated"));
		load();
	} else {
		QMessageBox::critical(this, tr("Error"), name + tr(" not deactivated"));
	}

	load();
}

void TeamFrame::handleItemClicked()
{
 	if (listWidget->currentItem() == nullptr) return;
	
	int id = listWidget->currentItem()->data(Qt::UserRole).toInt();
	QString name = listWidget->currentItem()->text();
	TeamModel model = TeamModel::load(id);
	
	deleteButton->setEnabled(true);
	
	if (model.active()) {
		deleteButton->setText("Deactivate");
		deleteButton->disconnect();
		connect(deleteButton, &QPushButton::clicked, this, &TeamFrame::deactivate);
	} else {
		deleteButton->setText("Activate");
		deleteButton->disconnect();
		connect(deleteButton, &QPushButton::clicked, this, &TeamFrame::activate);
	}
}

void TeamFrame::load() 
{
    QString searchFor = searchLineEdit->text().trimmed();
    bool showDeactivated = inactiveCheckBox->isChecked();

	QList<TeamData> team = TeamModel::list(mProjectId, showDeactivated);
	
	listWidget->clear();
	for (const TeamData &member: team) {
		QListWidgetItem *item = new QListWidgetItem(member.name, listWidget);
		item->setData(Qt::UserRole, member.id);
		listWidget->addItem(item);
	}
}
