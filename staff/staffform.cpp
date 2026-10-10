/* =====================================
 *	StaffForm.cpp
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */

#include "staffform.h"

#include "../settings/settingsmodel.h"
#include "employeetype.hpp"
#include "qcombobox.h"
#include "staffmodel.h"

#include <QHBoxLayout>
#include <QMessageBox>
#include <QVBoxLayout>
#include <qboxlayout.h>
#include <qlineedit.h>
#include <qpushbutton.h>

extern SettingsModel settings;

StaffForm::StaffForm(QWidget* parent, int id, QString mode)
    : QDialog(parent)
    , mDefaultName { "" }
    , mDefaultType { 0 }
    , mDefaultChargedAt {0}
{
    setupUI();

    if (id != 0) {
        StaffModel model = StaffModel::load(id);
        nameLineEdit->setText(model.name());
        int index = typeComboBox->findData(static_cast<int>(model.type()));
        typeComboBox->setCurrentIndex(index);
        chargedAtLineEdit->setText(QString::number(model.chargedAt()));
        mId = id;
        mDefaultName = model.name();
        mDefaultType = model.type();
        mDefaultChargedAt = model.chargedAt();
    }

    if (mode == "view") {
        nameLineEdit->setReadOnly(true);
        typeComboBox->setEnabled(false);
        chargedAtLineEdit->setReadOnly(true);
        saveButton->setVisible(false);
        saveButton->setEnabled(false);
    }
}

void StaffForm::handleSaveButtonClicked()
{
    QString name = nameLineEdit->text();
    int staffType = typeComboBox->currentData().toInt();
    int chargedAt = chargedAtLineEdit->text().toInt();
    

    if (name.isEmpty()) {
        QMessageBox::critical(this, tr("Input Error"), tr("Name must not be empty"));
        return;
    }

    StaffModel model { name, static_cast<EmployeeType>(staffType), chargedAt, 1, mId };

    if (model.save()) {
        if (mId == 0) {
            nameLineEdit->clear();
            typeComboBox->setCurrentIndex(0);
            chargedAtLineEdit->clear();
        } else {
            QMessageBox::information(this, tr("Success"), name + tr(" saved"));
        }

        mDefaultName = model.name();
        mDefaultType = model.type();
        mDefaultChargedAt = model.chargedAt();
 
    } else {
        QMessageBox::critical(this, tr("Error"), name + tr(" not saved"));
    }
}

void StaffForm::handleCloseButtonClicked()
{
    int staffType = typeComboBox->currentData().toInt();
    if (settings.showWarnings() && (nameLineEdit->text() != mDefaultName || staffType != static_cast<int>(mDefaultType) ||
            chargedAtLineEdit->text().toInt() != mDefaultChargedAt)) {
        QMessageBox::StandardButton button = QMessageBox::warning(this, tr("Unsaved Changes"),
            tr("You have unsaved changes, if you continue they will be lost. Do you want to continue?"),
            QMessageBox::Yes | QMessageBox::No);

        if (button == QMessageBox::No) {
            return;
        }
    }
    reject();
}

void StaffForm::setupUI()
{
    resize(450, 250);
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    nameLineEdit = new QLineEdit(this);
    nameLineEdit->setPlaceholderText(tr("Enter the staff member's name"));
    mainLayout->addWidget(nameLineEdit);

    typeComboBox = new QComboBox(this);

    typeComboBox->addItem("Employee", static_cast<int>(EmployeeType::Employee));
    typeComboBox->addItem("Contractor", static_cast<int>(EmployeeType::Contractor));

    mainLayout->addWidget(typeComboBox);

    chargedAtLineEdit = new QLineEdit(this);
    chargedAtLineEdit->setPlaceholderText(tr("Enter the hourly rate in pounds"));
    mainLayout->addWidget(chargedAtLineEdit);

    QHBoxLayout* buttonLayout = new QHBoxLayout(this);
    mainLayout->addLayout(buttonLayout);

    saveButton = new QPushButton(tr("Save"), this);
    connect(saveButton, &QPushButton::clicked, this, &StaffForm::handleSaveButtonClicked);
    buttonLayout->addWidget(saveButton);

    QPushButton* closeButton = new QPushButton(tr("Close"), this);
    connect(closeButton, &QPushButton::clicked, this, &StaffForm::handleCloseButtonClicked);
    buttonLayout->addWidget(closeButton);
}
