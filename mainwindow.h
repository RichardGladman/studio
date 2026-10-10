#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
private:
	void createMenu();
	
private slots:
	void handleSettingsAction();
	void handleProjectsAction();
	void handleTasksAction();
	void handleAboutAction();
	void handleAboutQtAction();
	void handleProjectsTaskAction();
	void handleByStartDateAction();
	void handleStaffAction();
};
#endif // MAINWINDOW_H
