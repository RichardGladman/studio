#ifndef PROJECT_FORM_H
#define PROJECT_FORM_H

#include <QDialog>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>

class ProjectForm : public QDialog {
    Q_OBJECT

public:
    explicit ProjectForm(QWidget* parent = nullptr, int id = 0, QString mode = "edit");
    ~ProjectForm() = default;

private slots:
    void handleSaveButtonClicked();
    void handleCloseButtonClicked();

private:
    QString mDefaultName;
    QString mDefaultDescription;

    int mId { };
	
	QLineEdit *nameLineEdit;
	QTextEdit *descriptionTextEdit;
	QPushButton *saveButton;
	
	void setupUI();
};

#endif // ANIMALFORM_H
