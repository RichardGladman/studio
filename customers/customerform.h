/* =====================================
 *	customerform.h
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */

#pragma once

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
    int mDefaultChargedAt;

    int mId { };

    QLineEdit *nameLineEdit;
    QLineEdit *chargedAtLineEdit;
    QPushButton *saveButton;

    void setupUI();
};
