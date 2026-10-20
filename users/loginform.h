/* =====================================
 *  loginform.h
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */

#pragma once

#include <QWidget>
#include <QDialog>
#include <QLineEdit>
#include <qlineedit.h>
#include <qtmetamacros.h>

class LoginForm : public QDialog
{
    Q_OBJECT

public:
    explicit LoginForm(QWidget *parent = nullptr);

private slots:
    void handleLoginButtonClicked();
    void handleCloseButtonClicked();

private:
    QLineEdit *emailLineEdit;
    QLineEdit *passwordLineEdit;

    void setupUI();
};