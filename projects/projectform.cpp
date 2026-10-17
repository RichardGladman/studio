#include "projectform.h"

#include "../settings/settingsmodel.h"
#include "projectmodel.h"
#include "qcombobox.h"
#include "qlogging.h"
#include "qmessagebox.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <qboxlayout.h>
#include <qlineedit.h>
#include <qpushbutton.h>

extern SettingsModel settings;

ProjectForm::ProjectForm(QWidget* parent, int id, QString mode)
    : QDialog(parent), mDefaultName { "" }, mDefaultDescription { "" }, mDefaultCustomerId(0)
{
	setupUI();
	
    if (mode != "add" && id != 0) {
        ProjectModel model = ProjectModel::load(id);
        int index = customersComboBox->findData(QVariant(model.customerId()));
        if (index != -1) {
            customersComboBox->setCurrentIndex(index);
        }

        nameLineEdit->setText(model.name());
        descriptionTextEdit->setPlainText(model.description());

        mId = id;
        mDefaultCustomerId = model.customerId();
        mDefaultName = model.name();
        mDefaultDescription = model.description();
    } else if (mode == "add" and id != -1) {
        int index = customersComboBox->findData(QVariant(id));
        if (index != -1) {
            customersComboBox->setCurrentIndex(index);
        }
    }

    if (mode == "view") {
        nameLineEdit->setEnabled(false);
        descriptionTextEdit->setEnabled(false);
        saveButton->setVisible(false);
        saveButton->setEnabled(false);
    }
}

void ProjectForm::handleSaveButtonClicked()
{
    int customerId = customersComboBox->currentData().toInt();
    qWarning() << customerId;
    QString name = nameLineEdit->text();
    QString description =descriptionTextEdit->toPlainText();

    if (customerId == -1) {
        QMessageBox::critical(this, tr("Input Error"), tr("You must select a customer"));
        return;
    }

    if (name.isEmpty()) {
        QMessageBox::critical(this, tr("Input Error"), tr("Name must not be empty"));
        return;
    }

    ProjectModel model { mId, customerId, name, description };

    if (model.save()) {
        if (mId == 0) {
            nameLineEdit->clear();
            descriptionTextEdit->clear();
        } else {
            QMessageBox::information(this, tr("Success"), tr("Project saved"));
            mDefaultCustomerId = customerId;
			mDefaultName = model.name();
			mDefaultDescription = model.description();
        }
    } else {
        QMessageBox::critical(this, tr("Error"), tr("Project not saved"));
    }
}

void ProjectForm::handleCloseButtonClicked()
{
    int customerId = customersComboBox->currentData().toInt();
    if (settings.showWarnings() && (nameLineEdit->text() != mDefaultName || descriptionTextEdit->toPlainText() != mDefaultDescription ||
                                    customerId != mDefaultCustomerId)) {
        QMessageBox::StandardButton button = QMessageBox::warning(this, tr("Unsaved Changes"),
            tr("You have unsaved changes, if you continue they will be lost. Do you want to continue?"),
            QMessageBox::Yes | QMessageBox::No);

        if (button == QMessageBox::No) {
            return;
        }
    }
    reject();
}

void ProjectForm::setupUI()
{
	resize(450, 250);
	QVBoxLayout *mainLayout = new QVBoxLayout(this);

    customersComboBox = new QComboBox(this);
    mainLayout->addWidget(customersComboBox);

    loadCustomerData();
	
	nameLineEdit = new QLineEdit(this);
	nameLineEdit->setPlaceholderText(tr("Enter the project name"));
	mainLayout->addWidget(nameLineEdit);
	
	descriptionTextEdit = new QTextEdit(this);
	descriptionTextEdit->setPlaceholderText(tr("Enter the project description"));
	mainLayout->addWidget(descriptionTextEdit);
	
	QHBoxLayout *buttonLayout = new QHBoxLayout(this);
	mainLayout->addLayout(buttonLayout);
	
	saveButton = new QPushButton("Save", this);
	connect(saveButton, &QPushButton::clicked, this, &ProjectForm::handleSaveButtonClicked);
	buttonLayout->addWidget(saveButton);
	
	QPushButton *closeButton = new QPushButton("Close", this);
	connect(closeButton, &QPushButton::clicked, this, &ProjectForm::handleCloseButtonClicked);
	buttonLayout->addWidget(closeButton);
}


void ProjectForm::loadCustomerData()
{
	QList<ListData> customers = CustomerModel::list("", false);

	customersComboBox->clear();
	customersComboBox->addItem("Select Customer...", QVariant(-1));
	for (const ListData &customer: customers) {
		customersComboBox->addItem(customer.name, QVariant(customer.id));
	}
}
