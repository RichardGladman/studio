/* =====================================
 *	teamform.cpp
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */

#include "teamform.h"
#include "qcombobox.h"
#include "teammodel.h"

#include "../common/listdata.h"
#include "../staff/staffmodel.h"
#include "../staff/staffrole.h"
#include "../settings/settingsmodel.h"

#include <QHBoxLayout>
#include <QMessageBox>
#include <QVBoxLayout>

#include <QDebug>
#include <QSqlQuery>

extern SettingsModel settings;

TeamForm::TeamForm(QWidget* parent, int projectId, int id, int staffId, QString mode)
    : QDialog(parent)
    , mDefaultStaff(0)
    , mDefaultRole(StaffRole::None)
{
    setupUI();

    mId = id;
    qDebug() << mId;
    mProjectId = projectId;
    mStaffId = staffId;

    if (mId != 0) {
        TeamModel model = TeamModel::load(mId);
        
        int index = staffIdComboBox->findData(model.staffId());
        staffIdComboBox->setCurrentIndex(index);

        index = roleComboBox->findData(static_cast<int>(model.role()));
        roleComboBox->setCurrentIndex(index);
        
        mDefaultStaff = model.staffId();
        mDefaultRole = model.role();
    }

    if (mode == "view") {
        staffIdComboBox->setEnabled(false);
        roleComboBox->setEnabled(false);
        saveButton->setVisible(false);
        saveButton->setEnabled(false);
    }
}

void TeamForm::handleSaveButtonClicked()
{
    int staffId = staffIdComboBox->currentData().toInt();
    StaffRole role = static_cast<StaffRole>(roleComboBox->currentData().toInt());

    qDebug() << QString::number(mProjectId) << " " << QString::number(staffId);

    TeamModel model { staffId, mProjectId, role, 1, mId };

    if (model.save()) {
        if (mProjectId == 0) {
            staffIdComboBox->setCurrentIndex(0);
            roleComboBox->setCurrentIndex(0);
        } else {
            QMessageBox::information(this, tr("Success"), tr("Team member saved"));
        }

        mDefaultStaff = staffId;
        mDefaultRole = role;

    } else {
        QMessageBox::critical(this, tr("Error"), tr("Team member not saved"));
    }
}

void TeamForm::handleCloseButtonClicked()
{
    int staffId = staffIdComboBox->currentData().toInt();
    int role = roleComboBox->currentData().toInt();

    if (settings.showWarnings() && (staffId != mDefaultStaff || role != static_cast<int>(mDefaultRole))) {
        QMessageBox::StandardButton button = QMessageBox::warning(this, tr("Unsaved Changes"),
            tr("You have unsaved changes, if you continue they will be lost. Do you want to continue?"),
            QMessageBox::Yes | QMessageBox::No);

        if (button == QMessageBox::No) {
            return;
        }
    }
    reject();
}

void TeamForm::setupUI()
{
    resize(450, 250);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    QList<ListData> staff = StaffModel::list("", false);

    staffIdComboBox = new QComboBox(this);

    for (ListData data: staff) {
        staffIdComboBox->addItem(data.name, data.id);
    }

    mainLayout->addWidget(staffIdComboBox);

    roleComboBox = new QComboBox(this);

    roleComboBox->addItem("None", static_cast<int>(StaffRole::None));
    roleComboBox->addItem("Admin", static_cast<int>(StaffRole::Admin));
    roleComboBox->addItem("Designer", static_cast<int>(StaffRole::Designer));
    roleComboBox->addItem("Developer", static_cast<int>(StaffRole::Developer));
    roleComboBox->addItem("Project Manager", static_cast<int>(StaffRole::ProjectManager));
    roleComboBox->addItem("Sales", static_cast<int>(StaffRole::Sales));
    roleComboBox->addItem("Support", static_cast<int>(StaffRole::Support));
    roleComboBox->addItem("Tester", static_cast<int>(StaffRole::Tester));

    mainLayout->addWidget(roleComboBox);

    QHBoxLayout* buttonLayout = new QHBoxLayout(this);
    mainLayout->addLayout(buttonLayout);

    saveButton = new QPushButton(tr("Save"), this);
    connect(saveButton, &QPushButton::clicked, this, &TeamForm::handleSaveButtonClicked);
    buttonLayout->addWidget(saveButton);

    QPushButton *closeButton = new QPushButton(tr("Close"), this);
    connect(closeButton, &QPushButton::clicked, this, &TeamForm::handleCloseButtonClicked);
    buttonLayout->addWidget(closeButton);
}
