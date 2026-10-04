/* =====================================
 *	taskframe.h
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */

#ifndef TASKFRAME_H
#define TASKFRAME_H


#include <QFrame>
#include <QLineEdit>
#include <QPushButton>
#include <QList>
#include <QListWidget>
#include <QComboBox>

class TaskFrame : public QFrame {
    Q_OBJECT

public:
    explicit TaskFrame(QWidget* parent = nullptr);
    ~TaskFrame();

private:
	QLineEdit *searchLineEdit;
	QComboBox *projectsCombobox;
	QPushButton *searchButton;
	QListWidget *listWidget;
	
	void handleSearchClicked();
	void handleViewClicked();
	void handleAddClicked();
	void handleEditClicked();
	void handleItemDoubleClicked();
	
	void loadData(QString searchFor = "");
	void loadProjectsData();
	void loadTasksForProject();
};


#endif
