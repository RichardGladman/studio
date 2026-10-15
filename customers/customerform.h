/* =====================================
 *	customerform.h
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */

#pragma once

#include "qlineedit.h"
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>

class CustomerForm : public QDialog {
    Q_OBJECT

public:
    explicit CustomerForm(QWidget* parent = nullptr, int id = 0, QString mode = "edit");
    ~CustomerForm() = default;

private slots:
    void handleSaveButtonClicked();
    void handleCloseButtonClicked();

private:
    QString mDefaultName;
    QString mDefaultStreet;
    QString mDefaultArea;
    QString mDefaultTown;
    QString mDefaultCounty;
    QString mDefaultPostcode;
    QString mDefaultPhone;
    QString mDefaultEmail;

    int mId { };

    QLineEdit *nameLineEdit;
    QLineEdit *streetLineEdit;
    QLineEdit *areaLineEdit;
    QLineEdit *townLineEdit;
    QLineEdit *countyLineEdit;
    QLineEdit *postcodeLineEdit;
    QLineEdit *phoneLineEdit;
    QLineEdit *emailLineEdit;
    QPushButton *saveButton;

    void setupUI();
};
