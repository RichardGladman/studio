/* =====================================
 *	form.h
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */

#pragma once

#include "employeetype.hpp"
#include "qlineedit.h"
#include <QComboBox>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>

class StaffForm : public QDialog {
    Q_OBJECT

public:
    explicit StaffForm(QWidget* parent = nullptr, int id = 0, QString mode = "edit");
    ~StaffForm() = default;

private slots:
    void handleSaveButtonClicked();
    void handleCloseButtonClicked();

private:
    QString mDefaultName;
    EmployeeType mDefaultType;
    int mDefaultChargedAt;

    int mId { };

    QLineEdit *nameLineEdit;
    QComboBox *typeComboBox;
    QLineEdit *chargedAtLineEdit;
    QPushButton *saveButton;

    void setupUI();
};
