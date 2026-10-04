#include "settingsframe.h"
#include "settingsmodel.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QPushButton>
#include <qcheckbox.h>
#include <qpushbutton.h>

extern SettingsModel settings;

SettingsFrame::SettingsFrame(QWidget *parent) : QFrame(parent)
{
	QVBoxLayout *mainLayout = new QVBoxLayout(this);

	serverLineEdit = new QLineEdit(this);
    serverLineEdit->setText(settings.server());
    mainLayout->addWidget(serverLineEdit);

	databaseLineEdit = new QLineEdit(this);
    databaseLineEdit->setText(settings.database());
    mainLayout->addWidget(databaseLineEdit);

	userLineEdit = new QLineEdit(this);
    userLineEdit->setText(settings.user());
    mainLayout->addWidget(userLineEdit);

	passwordLineEdit = new QLineEdit(this);
    passwordLineEdit->setText(settings.password());
    mainLayout->addWidget(passwordLineEdit);
	
	warningsCheckbox = new QCheckBox(this);
	warningsCheckbox->setText("Show Warnings");
	
	mainLayout->addWidget(warningsCheckbox);
	mainLayout->addStretch();
	
	QPushButton *saveButton = new QPushButton("Save", this);
	connect(saveButton, &QPushButton::clicked, this, &SettingsFrame::saveButtonClicked);
	
	mainLayout->addWidget(saveButton);
}

SettingsFrame::~SettingsFrame()
{
}

void SettingsFrame::saveButtonClicked()
{
    settings.server(serverLineEdit->text());
    settings.database(databaseLineEdit->text());
    settings.user(userLineEdit->text());
    settings.password(passwordLineEdit->text());
    settings.showWarnings(warningsCheckbox->isChecked());

    settings.save();
}
