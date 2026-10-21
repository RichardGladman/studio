#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qwidget.h"
#include <QMainWindow>
#include <qaction.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private:
	QString loggedInAs;
	QAction *loginAction;

	void createMenu();
	void setMenuState(bool enabled);
	
private slots:
	void handleSettingsAction();
	void handleProjectsAction();
	void handleTasksAction();
	void handleAboutAction();
	void handleAboutQtAction();
	void handleProjectsTaskAction();
	void handleByStartDateAction();
	void handleCustomerAction();
	void handleStaffAction();
	void handleLoginClicked();
};
#endif // MAINWINDOW_H
