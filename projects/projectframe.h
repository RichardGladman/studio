#ifndef PROJECT_FRAME_H
#define PROJECT_FRAME_H

#include "qcombobox.h"
#include <QFrame>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QList>
#include <QListWidget>

class ProjectFrame : public QFrame {
    Q_OBJECT

public:
    explicit ProjectFrame(QWidget* parent = nullptr);
    ~ProjectFrame();

private:
	QComboBox *customersComboBox;
	QLineEdit *searchLineEdit;
	QCheckBox *inactiveCheckBox;
	QPushButton *searchButton;
	QListWidget *listWidget;
	
	void handleSearchClicked();
	void handleViewClicked();
	void handleAddClicked();
	void handleEditClicked();
	void handleDeleteClicked();
	void handleTeamClicked();
	
	void loadData(QString searchFor = "", bool inactive = false);
	void loadForCustomers();
	void loadCustomerData();
};

#endif
