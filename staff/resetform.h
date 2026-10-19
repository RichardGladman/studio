/* =====================================
 *	resetform.h
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */

#pragma once

#include <QWidget>
#include <QDialog>
#include <QLineEdit>

class ResetForm : public QDialog
{
    Q_OBJECT

public:
    explicit ResetForm(int id, QWidget *parent = nullptr);
    ~ResetForm() = default;

private slots:
    void handleSaveButtonClicked();
    void handleCloseButtonClicked();

private:
    int mId;

    QLineEdit *passwordLineEdit;
    QLineEdit *confirmLineEdit;

    void setupUI();
};