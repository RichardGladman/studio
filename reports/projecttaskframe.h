/* =====================================
 *	projecttaskframe.h
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */

#ifndef PEOJECTTASKFRAME_H
#define PEOJECTTASKFRAME_H

#include "../reports/reportitem.h"

#include <QCheckBox>
#include <QComboBox>
#include <QFrame>
#include <QPushButton>
#include <QListWidget>

class ProjectTaskFrame : public QFrame {
    Q_OBJECT

public:
    explicit ProjectTaskFrame(QWidget *parent = nullptr);
    ~ProjectTaskFrame() = default;

private:
	QComboBox *projectsCombo;
	QComboBox *tasksCombo;
	QCheckBox *inactiveCheckbox;
	QListWidget *listWidget;
	QPushButton *exportButton;
	QPushButton *exportFormattedButton;
	
	QList<ReportItem> timings;
	
	void loadProjects();
	void loadTasks();
	void generateReport();
	void runExport(bool formatted);
};

#endif
