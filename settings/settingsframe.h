#ifndef SETTINGSFRAME_H
#define SETTINGSFRAME_H

#include <QFrame>
#include <QLineEdit>
#include <QCheckBox>

class SettingsFrame : public QFrame
{
    Q_OBJECT

public:
    explicit SettingsFrame(QWidget *parent = nullptr);
    ~SettingsFrame();

private:
	QLineEdit *directoryLineEdit;
	QCheckBox *warningsCheckbox;

    void directoryButtonClicked();
    void saveButtonClicked();
};

#endif // SETTINGSFRAME_H
