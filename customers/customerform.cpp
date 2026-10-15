/* =====================================
 *	CustomerForm.cpp
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */

#include "customerform.h"
#include "customermodel.h"

#include "../address/addressmodel.h"
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
    , mDefaultName("")
    , mDefaultStreet("")
    , mDefaultArea("")
    , mDefaultTown("")
    , mDefaultCounty("")
    , mDefaultPostcode("")
    , mDefaultPhone("")
    , mDefaultEmail("")
{
    setupUI();

    if (id != 0) {
        qCritical() << "HERE";
        CustomerModel model = CustomerModel::load(id);
        nameLineEdit->setText(model.name());
        streetLineEdit->setText(model.address().streetAddress());
        areaLineEdit->setText(model.address().area());
        townLineEdit->setText(model.address().town());
        countyLineEdit->setText(model.address().county());
        postcodeLineEdit->setText(model.address().postcode());
        phoneLineEdit->setText(model.phoneNumber());
        emailLineEdit->setText(model.email());
        mId = id;
        mDefaultName = model.name();
        mDefaultStreet = model.address().streetAddress();
        mDefaultArea = model.address().area();
        mDefaultTown = model.address().town();
        mDefaultCounty = model.address().county();
        mDefaultPostcode = model.address().postcode();
        mDefaultPhone = model.phoneNumber();
        mDefaultEmail = model.email();
    }

    if (mode == "view") {
        nameLineEdit->setReadOnly(true);
        streetLineEdit->setReadOnly(true);
        areaLineEdit->setReadOnly(true);
        townLineEdit->setReadOnly(true);
        countyLineEdit->setReadOnly(true);
        postcodeLineEdit->setReadOnly(true);
        phoneLineEdit->setReadOnly(true);
        emailLineEdit->setReadOnly(true);
        saveButton->setVisible(false);
        saveButton->setEnabled(false);
    }
}

void CustomerForm::handleSaveButtonClicked()
{
    QString name = nameLineEdit->text();
    QString street = streetLineEdit->text();
    QString area = areaLineEdit->text();
    QString town = townLineEdit->text();
    QString county = countyLineEdit->text();
    QString postcode = postcodeLineEdit->text();
    QString phone = phoneLineEdit->text();
    QString email = emailLineEdit->text();

    if (name.isEmpty() || street.isEmpty() || postcode.isEmpty()) {
        QMessageBox::critical(this, tr("Input Error"), tr("Name, street, and postcode must not be empty"));
        return;
    }

    if (phone.isEmpty() || email.isEmpty()) {
        QMessageBox::critical(this, tr("Input Error"), tr("Phone and email must not be empty"));
        return;
    }

    AddressModel address {street, area, town, county, postcode};
    CustomerModel model { name, address, phone, email, 1, mId };

    if (model.save()) {
        if (mId == 0) {
            nameLineEdit->clear();
            streetLineEdit->clear();
            areaLineEdit->clear();
            townLineEdit->clear();
            countyLineEdit->clear();
            postcodeLineEdit->clear();
            phoneLineEdit->clear();
            emailLineEdit->clear();
        } else {
            QMessageBox::information(this, tr("Success"), name + tr(" saved"));
        }

        mDefaultName = model.name();
        mDefaultStreet = model.address().streetAddress();
        mDefaultArea = model.address().area();
        mDefaultTown = model.address().town();
        mDefaultCounty = model.address().county();
        mDefaultPostcode = model.address().postcode();
        mDefaultPhone = model.phoneNumber();
        mDefaultEmail = model.email();
    } else {
        QMessageBox::critical(this, tr("Error"), name + tr(" not saved"));
    }
}

void CustomerForm::handleCloseButtonClicked()
{
    if (settings.showWarnings() && (nameLineEdit->text() != mDefaultName|| streetLineEdit->text() != mDefaultStreet ||
                                    areaLineEdit->text() != mDefaultArea || townLineEdit->text() != mDefaultTown ||
                                    countyLineEdit->text() != mDefaultCounty || postcodeLineEdit->text() != mDefaultPostcode ||
                                    phoneLineEdit->text() != mDefaultPhone || emailLineEdit->text() != mDefaultEmail)) {
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
    nameLineEdit->setPlaceholderText(tr("Enter the customer's name"));
    mainLayout->addWidget(nameLineEdit);

    streetLineEdit = new QLineEdit(this);
    streetLineEdit->setPlaceholderText(tr("Enter the street address"));
    mainLayout->addWidget(streetLineEdit);

    areaLineEdit = new QLineEdit(this);
    areaLineEdit->setPlaceholderText("Enter the area (Optional)");
    mainLayout->addWidget(areaLineEdit);

    townLineEdit= new QLineEdit(this);
    townLineEdit->setPlaceholderText("Enter the town (Optional)");
    mainLayout->addWidget(townLineEdit);

    countyLineEdit = new QLineEdit(this);
    countyLineEdit->setPlaceholderText("Enter the county (Optional)");
    mainLayout->addWidget(countyLineEdit);

    postcodeLineEdit = new QLineEdit(this);
    postcodeLineEdit->setPlaceholderText("Enter the post code");
    mainLayout->addWidget(postcodeLineEdit);

    phoneLineEdit = new QLineEdit(this);
    phoneLineEdit->setPlaceholderText("Enter the phone number");
    mainLayout->addWidget(phoneLineEdit);

    emailLineEdit = new QLineEdit(this);
    emailLineEdit->setPlaceholderText("Enter the email address");
    mainLayout->addWidget(emailLineEdit);

    QHBoxLayout* buttonLayout = new QHBoxLayout(this);
    mainLayout->addLayout(buttonLayout);

    saveButton = new QPushButton(tr("Save"), this);
    connect(saveButton, &QPushButton::clicked, this, &CustomerForm::handleSaveButtonClicked);
    buttonLayout->addWidget(saveButton);

    QPushButton* closeButton = new QPushButton(tr("Close"), this);
    connect(closeButton, &QPushButton::clicked, this, &CustomerForm::handleCloseButtonClicked);
    buttonLayout->addWidget(closeButton);
}
