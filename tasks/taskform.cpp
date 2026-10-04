/* =====================================
 *	taskform.cpp
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */

#include "taskform.h"

#include "../settings/settingsmodel.h"
#include "taskmodel.h"

#include <QHBoxLayout>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QLabel>

extern SettingsModel settings;

TaskForm::TaskForm(QWidget* parent, int id, QString mode, int projectId, QString projectName)
    : QDialog(parent)
    , mDefaultName { "" }
    , mDefaultDescription { "" }
	, mProjectId {projectId}
	, mProjectName {projectName}
{
    setupUI();

    if (id != 0) {
        TaskModel model = TaskModel::load(id);
        nameLineEdit->setText(model.name());
        descriptionTextEdit->setPlainText(model.description());
        mId = id;
        mDefaultName = model.name();
        mDefaultDescription = model.description();
    }

    if (mode == "view") {
        nameLineEdit->setEnabled(false);
        descriptionTextEdit->setEnabled(false);
        saveButton->setVisible(false);
        saveButton->setEnabled(false);
    }
}

void TaskForm::handleSaveButtonClicked()
{
    QString name = nameLineEdit->text();
    QString description = descriptionTextEdit->toPlainText();

    if (name.isEmpty()) {
        QMessageBox::critical(this, tr("Input Error"), tr("Name must not be empty"));
        return;
    }

    TaskModel model { mId, name, description, mProjectId };

    if (model.save()) {
        if (mId == 0) {
            nameLineEdit->clear();
            descriptionTextEdit->clear();
        } else {
            QMessageBox::information(this, tr("Success"), tr("Task saved"));
        }
    } else {
        QMessageBox::critical(this, tr("Error"), tr("Task not saved"));
    }
}

void TaskForm::handleCloseButtonClicked()
{
    if (settings.showWarnings() && (nameLineEdit->text() != mDefaultName || descriptionTextEdit->toPlainText() != mDefaultDescription)) {
        QMessageBox::StandardButton button = QMessageBox::warning(this, tr("Unsaved Changes"),
            tr("You have unsaved changes, if you continue they will be lost. Do you want to continue?"),
            QMessageBox::Yes | QMessageBox::No);

        if (button == QMessageBox::No) {
            return;
        }
    }
    reject();
}

void TaskForm::setupUI()
{
    resize(450, 250);
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
	
	QLabel *projectName = new QLabel(mProjectName);
	mainLayout->addWidget(projectName);

    nameLineEdit = new QLineEdit(this);
    nameLineEdit->setPlaceholderText(tr("Enter the task name"));
    mainLayout->addWidget(nameLineEdit);

    descriptionTextEdit = new QTextEdit(this);
    descriptionTextEdit->setPlaceholderText(tr("Enter the task description"));
    mainLayout->addWidget(descriptionTextEdit);

    QHBoxLayout* buttonLayout = new QHBoxLayout(this);
    mainLayout->addLayout(buttonLayout);

    saveButton = new QPushButton("Save", this);
    connect(saveButton, &QPushButton::clicked, this, &TaskForm::handleSaveButtonClicked);
    buttonLayout->addWidget(saveButton);

    QPushButton* closeButton = new QPushButton("Close", this);
    connect(closeButton, &QPushButton::clicked, this, &TaskForm::handleCloseButtonClicked);
    buttonLayout->addWidget(closeButton);
}
