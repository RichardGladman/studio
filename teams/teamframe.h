/* =====================================
 *	teamform.cpp
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */

#pragma once

#include <QDialog>
#include <QCheckBox>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>


class TeamFrame : public QDialog {
    Q_OBJECT

public:
    explicit TeamFrame(QWidget* parent = nullptr, int projectId = 0);
    virtual ~TeamFrame();
    void handleCloseButtonClicked();

private:
    QLineEdit *searchLineEdit;
    QCheckBox *inactiveCheckBox;
    QListWidget *listWidget;

    QPushButton *searchButton;
    QPushButton *deleteButton;

    int mId;
    int mProjectId;

    void setupUI();
    void showAddForm();
    void showEditForm();
    void deactivate();
    void activate();
    void handleItemClicked();
	void load();
};