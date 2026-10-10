/* =====================================
 *	mainwindow.cpp
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */
#include "mainwindow.h"
#include "about/aboutdialog.h"
#include "dbinitialiser.h"
#include "qaction.h"
#include "reports/bystartdateframe.h"
#include "settings/settingsmodel.h"
#include "settings/settingsframe.h"
#include "projects/projectframe.h"
#include "tasks/taskframe.h"
#include "reports/projecttaskframe.h"
#include "staff/staffframe.h"

#include <QApplication>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QDialog>
#include <QSqlDatabase>

SettingsModel settings;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
	setWindowTitle("Studio");
	resize(600, 800);
	
	settings.load();
	if (settings.server().isEmpty()) {
		handleSettingsAction();
		QMessageBox::information(this, tr("Action Required"), tr("Please enter server details"));
		return;
	}
	
	StoreInitialiser *init = new StoreInitialiser();
	
	QSqlDatabase dbConnection = QSqlDatabase::addDatabase("QMYSQL");
	dbConnection.setHostName(settings.server());
	dbConnection.setPort(3306);
	dbConnection.setDatabaseName(settings.database());
	dbConnection.setUserName(settings.user());
	dbConnection.setPassword(settings.password());

	if (!dbConnection.open()) {
	    qDebug() << "Database connection error";
	}
	
	init->createDataTables();
	
	delete init;

	QPixmap pixmap = QPixmap(":/assets/icon.png");
	QIcon icon = QIcon(pixmap);

	setWindowIcon(icon);
	
	QWidget *centralWidget = new QWidget(this);
	setCentralWidget(centralWidget);
	
	createMenu();
	
	QVBoxLayout *mainLayout = new QVBoxLayout(this);
}

MainWindow::~MainWindow() = default;

void MainWindow::createMenu()
{
	QMenuBar *menuBar = this->menuBar();
	QMenu *fileMenu = menuBar->addMenu(tr("&File"));
	
	QAction *settingsAction = new QAction(tr("&Settings"), this);
	QAction *exitAction = new QAction(tr("E&xit"), this);
	
	connect(settingsAction, &QAction::triggered, this, &MainWindow::handleSettingsAction);
	connect(exitAction, &QAction::triggered, this, &QApplication::quit);
	
	fileMenu->addAction(settingsAction);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAction);

	QMenu *staffMenu = menuBar->addMenu(tr("&Stakeholders"));

	QAction *staffAction = new QAction(tr("Staff"), this);

	connect(staffAction, &QAction::triggered, this, &MainWindow::handleStaffAction);

	staffMenu->addAction(staffAction);
	
	QMenu *projectsMenu = menuBar->addMenu(tr("&Projects"));
	
	QAction *projectsAction = new QAction(tr("P&rojects"), this);
	QAction *tasksAction = new QAction(tr("&Tasks"), this);
	
	connect(projectsAction, &QAction::triggered, this, &MainWindow::handleProjectsAction);
	connect(tasksAction, &QAction::triggered, this, &MainWindow::handleTasksAction);
	
	projectsMenu->addAction(projectsAction);
	projectsMenu->addAction(tasksAction);
	
	QMenu *reportsMenu = menuBar->addMenu(tr("&Reports"));
	
	QAction *projectTasksAction = new QAction("By Project and Task", this);
	connect(projectTasksAction, &QAction::triggered, this, &MainWindow::handleProjectsTaskAction);
	reportsMenu->addAction(projectTasksAction);
	
	QAction *byStartDateAction = new QAction("By Start Date", this);
	connect(byStartDateAction, &QAction::triggered, this, &MainWindow::handleByStartDateAction);
	reportsMenu->addAction(byStartDateAction);
	
	QMenu *helpMenu = menuBar->addMenu(tr("&Help"));
	
	QAction *aboutAction = new QAction(tr("&About"), this);
	QAction *aboutQtAction = new QAction(tr("About &Qt"), this);
	
	connect(aboutAction, &QAction::triggered, this, &MainWindow::handleAboutAction);
	connect(aboutQtAction, &QAction::triggered, this, &MainWindow::handleAboutQtAction);
	
	helpMenu->addAction(aboutAction);
	helpMenu->addAction(aboutQtAction);
}

void ::MainWindow::handleSettingsAction()
{
	SettingsFrame *frame = new SettingsFrame(this);
	setWindowTitle(tr("Studio:- Settings"));
	setCentralWidget(frame);
}

void MainWindow::handleProjectsAction()
{
	ProjectFrame *frame = new ProjectFrame(this);
	setWindowTitle(tr("Studio:- Projects"));
	setCentralWidget(frame);
}

void MainWindow::handleTasksAction()
{
	TaskFrame *frame = new TaskFrame(this);
	setWindowTitle("Studio:- Tasks");
	setCentralWidget(frame);
}

void MainWindow::handleProjectsTaskAction()
{
	ProjectTaskFrame *frame = new ProjectTaskFrame(this);
	setWindowTitle("Studio:- By Project and Tasks");
	setCentralWidget(frame);
}

void MainWindow::handleByStartDateAction()
{
	ByStartDateFrame *frame = new ByStartDateFrame(this);
	setWindowTitle("Studio:- By Start Date");
	setCentralWidget(frame);
}

void MainWindow::handleAboutAction()
{
	AboutDialog *dialog = new AboutDialog();
	dialog->exec();
	delete dialog;
}

void MainWindow::handleAboutQtAction()
{
	QMessageBox::aboutQt(this, "About Qt");
}

void MainWindow::handleStaffAction()
{
	StaffFrame *frame = new StaffFrame(this);
	setWindowTitle("Studio:- Staff");
	setCentralWidget(frame);
}