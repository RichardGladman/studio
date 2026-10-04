#include "aboutdialog.h"

#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>
#include <qpushbutton.h>

AboutDialog::AboutDialog(QWidget *parent) : QDialog(parent) 
{
	setWindowTitle("About Studio");
	resize(400, 200);
	
	QHBoxLayout *mainLayout = new QHBoxLayout(this);
	
	QPixmap pixmap = QPixmap(":/assets/icon.png");
	QLabel *logo = new QLabel(this);
	logo->setPixmap(pixmap);
	
	mainLayout->addWidget(logo);
	
	QVBoxLayout *rightLayout = new QVBoxLayout(this);
	
	QLabel *titleLabel = new QLabel(tr("Studio"), this);
	rightLayout->addWidget(titleLabel);
	
	QLabel *copyrightLabel = new QLabel(this);
	copyrightLabel->setText("© 2026 Richard Muir-Gladman");
	rightLayout->addWidget(copyrightLabel);
	
	QLabel *licenceLabel = new QLabel(tr("Licensed under the GPLv3"), this);
	rightLayout->addWidget(licenceLabel);
	
	QLabel *descriptionLabel = new QLabel(this);
	descriptionLabel->setText(tr("Manage your projects and record your time spent on them."));
	rightLayout->addWidget(descriptionLabel);
	
	rightLayout->addStretch();
	
	QPushButton *button = new QPushButton("Close", this);
	connect(button, &QPushButton::clicked, this, &QDialog::reject);
	rightLayout->addWidget(button);
	
	mainLayout->addLayout(rightLayout);

}

AboutDialog::~AboutDialog() {}
