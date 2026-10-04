/* =====================================
 *	taskform.h
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */

#ifndef TASKFORM_H
#define TASKFORM_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>

class TaskForm : public QDialog {
    Q_OBJECT

public:
    explicit TaskForm(QWidget* parent = nullptr, int id = 0, QString mode = "edit", int projectId = 0, QString projectName = "");
    ~TaskForm() = default;

private slots:
    void handleSaveButtonClicked();
    void handleCloseButtonClicked();

private:
    QString mDefaultName;
    QString mDefaultDescription;

    int mId { };
	int mProjectId;
	QString mProjectName;

    QLineEdit* nameLineEdit;
    QTextEdit* descriptionTextEdit;
    QPushButton* saveButton;

    void setupUI();
};

#endif // ANIMALFORM_H
