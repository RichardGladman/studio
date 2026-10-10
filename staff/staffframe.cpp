/* =====================================
 *	frame.cpp
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */

#include "staffframe.h"
#include "staffform.h"
#include "staffmodel.h"
#include "../common/listdata.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QList>
#include <QSpacerItem>
#include <QMessageBox>

StaffFrame::StaffFrame(QWidget* parent) : QFrame(parent)
{
    setupUI();
    load();
}

StaffFrame::~StaffFrame()
{
}

void StaffFrame::setupUI()
{
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    //  Add the search bar
    QHBoxLayout *searchLayout = new QHBoxLayout(this);

    searchLineEdit = new QLineEdit(this);
    searchLineEdit->setPlaceholderText(tr("Search for staff"));
    searchLayout->addWidget(searchLineEdit);

    showDeletedCheckbox = new QCheckBox(tr("Deactivated"), this);
    searchLayout->addWidget(showDeletedCheckbox);

    QPushButton *searchButton = new QPushButton(tr("Search"), this);
    connect(searchButton, &QPushButton::clicked, this, &StaffFrame::load);
    searchLayout->addWidget(searchButton);

    mainLayout->addLayout(searchLayout);

    listWidget = new QListWidget(this);
	connect(listWidget, &QListWidget::itemClicked, this, &StaffFrame::handleItemClicked);
    mainLayout->addWidget(listWidget);
	
	// Button bar
	QHBoxLayout *buttonLayout = new QHBoxLayout(this);
	
	QPushButton *viewButton = new QPushButton(tr("View"), this);
	QPushButton *addButton = new QPushButton(tr("Add"), this);
	QPushButton *editButton = new QPushButton(tr("Edit"), this);
	deleteButton = new QPushButton(tr("Deactivate"), this);
	deleteButton->setEnabled(false);

    connect(viewButton, &QPushButton::clicked, this, &StaffFrame::showViewForm);
    connect(addButton, &QPushButton::clicked, this, &StaffFrame::showAddForm);
    connect(editButton, &QPushButton::clicked, this, &StaffFrame::showEditForm);
    connect(deleteButton, &QPushButton::clicked, this, &StaffFrame::deactivate);
	
	buttonLayout->addWidget(viewButton);
	buttonLayout->addWidget(addButton);
	buttonLayout->addWidget(editButton);
	buttonLayout->addWidget(deleteButton);

	mainLayout->addLayout(buttonLayout);
}

void StaffFrame::showViewForm()
{
   	if (listWidget->currentItem() == nullptr) return;
	
	int id = listWidget->currentItem()->data(Qt::UserRole).toInt();
	
	StaffForm *dialog = new StaffForm(this, id, "view");
	dialog->exec();
}

void StaffFrame::showAddForm()
{
    StaffForm *form = new StaffForm(this);
    form->exec();
    load();
}

void StaffFrame::showEditForm()
{
   	if (listWidget->currentItem() == nullptr) return;

	StaffForm *form = new StaffForm(this, listWidget->currentItem()->data(Qt::UserRole).toInt(), "Edit");
	form->exec();
	load();
}

void StaffFrame::deactivate()
{
 	if (listWidget->currentItem() == nullptr) return;
	
	int id = listWidget->currentItem()->data(Qt::UserRole).toInt();
	QString name = listWidget->currentItem()->text();
	StaffModel model = StaffModel::load(id);
	
	if (model.deactivate()) {
		QMessageBox::information(this, tr("Success"), name +  tr(" deactivated"));
		load();
	} else {
		QMessageBox::critical(this, tr("Error"), name + tr(" not deactivated"));
	}

	load();
}

void StaffFrame::activate()
{
 	if (listWidget->currentItem() == nullptr) return;
	
	int id = listWidget->currentItem()->data(Qt::UserRole).toInt();
	QString name = listWidget->currentItem()->text();
	StaffModel model = StaffModel::load(id);
	
	if (model.activate()) {
		QMessageBox::information(this, tr("Success"), name +  tr(" deactivated"));
		load();
	} else {
		QMessageBox::critical(this, tr("Error"), name + tr(" not deactivated"));
	}

	load();
}

void StaffFrame::handleItemClicked()
{
 	if (listWidget->currentItem() == nullptr) return;
	
	int id = listWidget->currentItem()->data(Qt::UserRole).toInt();
	QString name = listWidget->currentItem()->text();
	StaffModel model = StaffModel::load(id);
	
	deleteButton->setEnabled(true);
	
	if (model.active()) {
		deleteButton->setText("Deactivate");
		deleteButton->disconnect();
		connect(deleteButton, &QPushButton::clicked, this, &StaffFrame::deactivate);
	} else {
		deleteButton->setText("Activate");
		deleteButton->disconnect();
		connect(deleteButton, &QPushButton::clicked, this, &StaffFrame::activate);
	}
}

void StaffFrame::load()
{
    QString searchFor = searchLineEdit->text();
    bool showDeleted = showDeletedCheckbox->isChecked();

    QList<ListData> staff = StaffModel::list(searchFor, showDeleted);

	listWidget->clear();
	for (const ListData &employee: staff) {
		QListWidgetItem *item = new QListWidgetItem(employee.name, listWidget);
		item->setData(Qt::UserRole, employee.id);
		listWidget->addItem(item);
	}
}
