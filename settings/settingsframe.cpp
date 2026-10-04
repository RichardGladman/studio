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
	QHBoxLayout *fileLayout = new QHBoxLayout(this);	
	
	directoryLineEdit = new QLineEdit(this);
	QPushButton *directoryButton = new QPushButton("...", this);
	connect(directoryButton, &QPushButton::clicked, this, &SettingsFrame::directoryButtonClicked);
	
	fileLayout->addWidget(directoryLineEdit);
	fileLayout->addWidget(directoryButton);
	
	mainLayout->addLayout(fileLayout);
	
	warningsCheckbox = new QCheckBox(this);
	warningsCheckbox->setText("Show Warnings");
	
	mainLayout->addWidget(warningsCheckbox);
	mainLayout->addStretch();
	
	QPushButton *saveButton = new QPushButton("Save", this);
	connect(saveButton, &QPushButton::clicked, this, &SettingsFrame::saveButtonClicked);
	
	mainLayout->addWidget(saveButton);
	
    directoryLineEdit->setText(settings.dataDirectory());
    warningsCheckbox->setChecked(settings.showWarnings());
}

SettingsFrame::~SettingsFrame()
{
}

void SettingsFrame::directoryButtonClicked()
{
    QString dirName = QFileDialog::getExistingDirectory(this, tr("Choose data directory"), QString(), QFileDialog::ShowDirsOnly);
    if (!dirName.isEmpty()) {
        directoryLineEdit->setText(dirName);
    }
}


void SettingsFrame::saveButtonClicked()
{
    settings.dataDirectory(directoryLineEdit->text());
    settings.showWarnings(warningsCheckbox->isChecked());

    if (settings.dataDirectory().isEmpty()) {
        QMessageBox::warning(this, tr("Validation Error"), tr("You must choose a directory"));
        return;
    }

    settings.save();
}
