/* =====================================
 *	customerframe.cpp
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */

#include "customerframe.h"
#include "customerform.h"
#include "customermodel.h"
#include "../common/listdata.h"

#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QList>
#include <QSpacerItem>
#include <QMessageBox>

CustomerFrame::CustomerFrame(QWidget* parent) : QFrame(parent)
{
    setupUI();
    load();
}

CustomerFrame::~CustomerFrame()
{
}

void CustomerFrame::setupUI()
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
    connect(searchButton, &QPushButton::clicked, this, &CustomerFrame::load);
    searchLayout->addWidget(searchButton);

    mainLayout->addLayout(searchLayout);

    listWidget = new QListWidget(this);
	connect(listWidget, &QListWidget::itemClicked, this, &CustomerFrame::handleItemClicked);
    mainLayout->addWidget(listWidget);
	
	// Button bar
	QHBoxLayout *buttonLayout = new QHBoxLayout(this);
	
	QPushButton *viewButton = new QPushButton(tr("View"), this);
	QPushButton *addButton = new QPushButton(tr("Add"), this);
	QPushButton *editButton = new QPushButton(tr("Edit"), this);
	deleteButton = new QPushButton(tr("Deactivate"), this);
	deleteButton->setEnabled(false);

    connect(viewButton, &QPushButton::clicked, this, &CustomerFrame::showViewForm);
    connect(addButton, &QPushButton::clicked, this, &CustomerFrame::showAddForm);
    connect(editButton, &QPushButton::clicked, this, &CustomerFrame::showEditForm);
    connect(deleteButton, &QPushButton::clicked, this, &CustomerFrame::deactivate);
	
	buttonLayout->addWidget(viewButton);
	buttonLayout->addWidget(addButton);
	buttonLayout->addWidget(editButton);
	buttonLayout->addWidget(deleteButton);

	mainLayout->addLayout(buttonLayout);
}

void CustomerFrame::showViewForm()
{
   	if (listWidget->currentItem() == nullptr) return;
	
	int id = listWidget->currentItem()->data(Qt::UserRole).toInt();
	
	CustomerForm *dialog = new CustomerForm(this, id, "view");
	dialog->exec();
}

void CustomerFrame::showAddForm()
{
    CustomerForm *form = new CustomerForm(this);
    form->exec();
    load();
}

void CustomerFrame::showEditForm()
{
   	if (listWidget->currentItem() == nullptr) return;

	CustomerForm *form = new CustomerForm(this, listWidget->currentItem()->data(Qt::UserRole).toInt(), "Edit");
	form->exec();
	load();
}

void CustomerFrame::deactivate()
{
 	if (listWidget->currentItem() == nullptr) return;
	
	int id = listWidget->currentItem()->data(Qt::UserRole).toInt();
	QString name = listWidget->currentItem()->text();
	CustomerModel model = CustomerModel::load(id);
	
	if (model.deactivate()) {
		QMessageBox::information(this, tr("Success"), name +  tr(" deactivated"));
		load();
	} else {
		QMessageBox::critical(this, tr("Error"), name + tr(" not deactivated"));
	}

	load();
}

void CustomerFrame::activate()
{
 	if (listWidget->currentItem() == nullptr) return;
	
	int id = listWidget->currentItem()->data(Qt::UserRole).toInt();
	QString name = listWidget->currentItem()->text();
	CustomerModel model = CustomerModel::load(id);
	
	if (model.activate()) {
		QMessageBox::information(this, tr("Success"), name +  tr(" deactivated"));
		load();
	} else {
		QMessageBox::critical(this, tr("Error"), name + tr(" not deactivated"));
	}

	load();
}

void CustomerFrame::handleItemClicked()
{
 	if (listWidget->currentItem() == nullptr) return;
	
	int id = listWidget->currentItem()->data(Qt::UserRole).toInt();
	CustomerModel model = CustomerModel::load(id);
	
	deleteButton->setEnabled(true);

	if (model.active()) {
		deleteButton->setText("Deactivate");
		deleteButton->disconnect();
		connect(deleteButton, &QPushButton::clicked, this, &CustomerFrame::deactivate);
	} else {
		deleteButton->setText("Activate");
		deleteButton->disconnect();
		connect(deleteButton, &QPushButton::clicked, this, &CustomerFrame::activate);
	}
}

void CustomerFrame::load()
{
    QString searchFor = searchLineEdit->text();
    bool showDeleted = showDeletedCheckbox->isChecked();

    QList<ListData> staff = CustomerModel::list(searchFor, showDeleted);

	listWidget->clear();
	for (const ListData &employee: staff) {
		QListWidgetItem *item = new QListWidgetItem(employee.name, listWidget);
		item->setData(Qt::UserRole, employee.id);
		listWidget->addItem(item);
	}
}
