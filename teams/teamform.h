/* =====================================
 *	teamform.h
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */

#pragma once

#include "../staff/staffrole.h"

#include <QComboBox>
#include <QDialog>
#include <QPushButton>

class TeamForm : public QDialog {
    Q_OBJECT

public:
    explicit TeamForm(QWidget* parent = nullptr, int projectId = 0, int id = 0, int staffId = 0, QString mode = "edit");
    ~TeamForm() = default;

private slots:
    void handleSaveButtonClicked();
    void handleCloseButtonClicked();

private:
    StaffRole mDefaultRole;
    int mDefaultStaff;

    int mId;
    int mProjectId;
    int mStaffId;

    QComboBox *staffIdComboBox;
    QComboBox *roleComboBox;
    QPushButton *saveButton;

    void setupUI();
};
