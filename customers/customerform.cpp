/* =====================================
 *	CustomerForm.cpp
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */

#include "customerform.h"
#include "customermodel.h"

#include "../settings/settingsmodel.h"

#include <QHBoxLayout>
#include <QMessageBox>
#include <QVBoxLayout>
#include <qboxlayout.h>
#include <qlineedit.h>
#include <qpushbutton.h>

extern SettingsModel settings;

CustomerForm::CustomerForm(QWidget* parent, int id, QString mode)
    : QDialog(parent)
    , mDefaultName { "" }
{
    setupUI();

    if (id != 0) {
        CustomerModel model = CustomerModel::load(id);
        nameLineEdit->setText(model.name());
        chargedAtLineEdit->setText(QString::number(model.chargedAt()));
        mId = id;
        mDefaultName = model.name();
        mDefaultChargedAt = model.chargedAt();
    }

    if (mode == "view") {
        nameLineEdit->setReadOnly(true);
        chargedAtLineEdit->setReadOnly(true);
        saveButton->setVisible(false);
        saveButton->setEnabled(false);
    }
}

void CustomerForm::handleSaveButtonClicked()
{
    QString name = nameLineEdit->text();
    int chargedAt = chargedAtLineEdit->text().toInt();
    

    if (name.isEmpty()) {
        QMessageBox::critical(this, tr("Input Error"), tr("Name must not be empty"));
        return;
    }

    CustomerModel model { name, chargedAt, 1, mId };

    if (model.save()) {
        if (mId == 0) {
            nameLineEdit->clear();
            chargedAtLineEdit->clear();
        } else {
            QMessageBox::information(this, tr("Success"), name + tr(" saved"));
        }

        mDefaultName = model.name();
        mDefaultChargedAt = model.chargedAt();
 
    } else {
        QMessageBox::critical(this, tr("Error"), name + tr(" not saved"));
    }
}

void CustomerForm::handleCloseButtonClicked()
{
    if (settings.showWarnings() && (nameLineEdit->text() != mDefaultName|| chargedAtLineEdit->text().toInt() != mDefaultChargedAt)) {
        QMessageBox::StandardButton button = QMessageBox::warning(this, tr("Unsaved Changes"),
            tr("You have unsaved changes, if you continue they will be lost. Do you want to continue?"),
            QMessageBox::Yes | QMessageBox::No);

        if (button == QMessageBox::No) {
            return;
        }
    }
    reject();
}

void CustomerForm::setupUI()
{
    resize(450, 250);
    QVBoxLayout* mainLayout = new QVBoxLayout(this);

    nameLineEdit = new QLineEdit(this);
    nameLineEdit->setPlaceholderText(tr("Enter the staff member's name"));
    mainLayout->addWidget(nameLineEdit);

    chargedAtLineEdit = new QLineEdit(this);
    chargedAtLineEdit->setPlaceholderText(tr("Enter the hourly rate in pounds"));
    mainLayout->addWidget(chargedAtLineEdit);

    QHBoxLayout* buttonLayout = new QHBoxLayout(this);
    mainLayout->addLayout(buttonLayout);

    saveButton = new QPushButton(tr("Save"), this);
    connect(saveButton, &QPushButton::clicked, this, &CustomerForm::handleSaveButtonClicked);
    buttonLayout->addWidget(saveButton);

    QPushButton* closeButton = new QPushButton(tr("Close"), this);
    connect(closeButton, &QPushButton::clicked, this, &CustomerForm::handleCloseButtonClicked);
    buttonLayout->addWidget(closeButton);
}
