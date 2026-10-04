/* =====================================
 *	bystartdateframe.h
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */

#ifndef BYSTARTDATEFRAME_H
#define BYSTARTDATEFRAME_H

#include "../reports/reportitem.h"

#include <QCheckBox>
#include <QDateEdit>
#include <QFrame>
#include <QPushButton>
#include <QListWidget>
#include <qdatetimeedit.h>

class ByStartDateFrame : public QFrame {
    Q_OBJECT

public:
    explicit ByStartDateFrame(QWidget *parent = nullptr);
    ~ByStartDateFrame() = default;

private:
	QDateEdit *fromDateEdit;
	QDateEdit *toDateEdit;
	QCheckBox *inactiveCheckbox;
	QListWidget *listWidget;
	QPushButton *exportButton;
	QPushButton *exportFormattedButton;
	
	QList<ReportItem> reportItems;
	
	void generateReport();
	void runExport(bool formatted);
};

#endif
