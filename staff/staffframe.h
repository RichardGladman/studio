/* =====================================
 *	staffframe.h
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

class StaffFrame : public QFrame {
    Q_OBJECT

public:
    explicit StaffFrame(QWidget* parent = nullptr);
    ~StaffFrame();

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
