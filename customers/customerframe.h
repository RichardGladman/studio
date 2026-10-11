/* =====================================
 *	customerframe.h
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */

#pragma once

#include <QFrame>
#include <QCheckBox>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>

class CustomerFrame : public QFrame {
    Q_OBJECT

public:
    explicit CustomerFrame(QWidget* parent = nullptr);
    ~CustomerFrame();

private:
    QLineEdit *searchLineEdit;
    QCheckBox *showDeletedCheckbox;
    QListWidget *listWidget;

    QPushButton *deleteButton;

    void setupUI();
    void showAddForm();
    void showEditForm();
    void showViewForm();
    void deactivate();
    void activate();
    void handleItemClicked();
	void load();

};
