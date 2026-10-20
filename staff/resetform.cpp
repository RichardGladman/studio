/* =====================================
 *	resetform.cpp
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */

#include "resetform.h"

#include <QCryptographicHash>
#include "qcryptographichash.h"
#include "qmessagebox.h"
#include "qpushbutton.h"
#include "../settings/settingsmodel.h"
#include "staffmodel.h"
#include <qboxlayout.h>
#include <qdialog.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qwidget.h>


extern SettingsModel settings;

ResetForm::ResetForm(int id, QWidget *parent): QDialog(parent)
{
    setupUI();
    mId = id;
}

void ResetForm::handleSaveButtonClicked()
{
    QString password = passwordLineEdit->text();
    QString confirm = confirmLineEdit->text();

    if (password.isEmpty() || password != confirm) {
        QMessageBox::critical(this, tr("Input Error"), tr("Password must not be empty and must match the confirm"));
        return;
    }

    password = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256).toBase64();

    StaffModel staff = StaffModel::load(mId);
    staff.password(password);

    if (staff.reset()) {
        QMessageBox::information(this, tr("Success"), tr("Password reset"));
        accept();
    } else {
        QMessageBox::critical(this, tr("Error"), tr("Password not reset"));
    }
}

void ResetForm::handleCloseButtonClicked()
{
    reject();
}

void ResetForm::setupUI()
{
    resize(450, 250);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    passwordLineEdit = new QLineEdit(this);
    passwordLineEdit->setPlaceholderText(tr("Enter new password"));
    passwordLineEdit->setEchoMode(QLineEdit::Password);
    mainLayout->addWidget(passwordLineEdit);

    confirmLineEdit = new QLineEdit(this);
    confirmLineEdit->setPlaceholderText(tr("Confirm new password"));
    confirmLineEdit->setEchoMode(QLineEdit::Password);
    mainLayout->addWidget(confirmLineEdit);

    mainLayout->addStretch(1);

    QHBoxLayout *buttonLayout = new QHBoxLayout(this);

    QPushButton *saveButton = new QPushButton(tr("Save"), this);
    connect(saveButton, &QPushButton::clicked, this, &ResetForm::handleSaveButtonClicked);
    buttonLayout->addWidget(saveButton);

    QPushButton *closeButton = new QPushButton(tr("Close"), this);
    connect(closeButton, &QPushButton::clicked, this, &ResetForm::handleCloseButtonClicked);
    buttonLayout->addWidget(closeButton);

    mainLayout->addLayout(buttonLayout);
    
}