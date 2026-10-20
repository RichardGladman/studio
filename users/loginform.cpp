/* =====================================
 *  loginform.cpp
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */

#include "loginform.h"
#include "usermodel.h"

#include "qcryptographichash.h"
#include "qmessagebox.h"
#include "qpushbutton.h"
#include "../settings/settingsmodel.h"
#include <qboxlayout.h>
#include <qdialog.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qwidget.h>

extern SettingsModel settings;
extern UserModel user;

LoginForm::LoginForm(QWidget *parent) : QDialog(parent)
{
    setupUI();
}

void LoginForm::handleLoginButtonClicked()
{
    static int attempts = 0;

    QString username = usernameLineEdit->text();
    QString password = QCryptographicHash::hash(usernameLineEdit->text().toUtf8(), QCryptographicHash::Sha256);

    user.login(usernameLineEdit->text(), password);

    if (user.loggedIn()) {
        accept();
    } else {
        QMessageBox::information(this, tr("User Login"), tr("User name and password invalid or user is deactivated"));
        
        if (attempts == 3) {
                reject();
            }
        
            ++attempts;
        }
    }

void LoginForm::handleCloseButtonClicked()
{
    reject();
}

void LoginForm::setupUI()
{
    resize(450, 250);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    usernameLineEdit = new QLineEdit(this);
    usernameLineEdit->setPlaceholderText(tr("Enter your email address"));
    mainLayout->addWidget(usernameLineEdit);

    passwordLineEdit = new QLineEdit(this);
    passwordLineEdit->setPlaceholderText(tr("Enter new password"));
    passwordLineEdit->setEchoMode(QLineEdit::Password);
    mainLayout->addWidget(passwordLineEdit);

    mainLayout->addStretch(1);

    QHBoxLayout *buttonLayout = new QHBoxLayout(this);

    QPushButton *saveButton = new QPushButton(tr("Save"), this);
    connect(saveButton, &QPushButton::clicked, this, &LoginForm::handleLoginButtonClicked);
    buttonLayout->addWidget(saveButton);

    QPushButton *closeButton = new QPushButton(tr("Close"), this);
    connect(closeButton, &QPushButton::clicked, this, &LoginForm::handleCloseButtonClicked);
    buttonLayout->addWidget(closeButton);

    mainLayout->addLayout(buttonLayout);
}