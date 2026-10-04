/* ===================================== 
 *	dbinitialiser.cpp
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */

#include "dbinitialiser.h"
#include "projects/projectrepository.h"
#include "tasks/taskrepository.h"
#include "tasktimer/tasktimerrepository.h"

#include <QDir>
#include <QDebug>

void StoreInitialiser::createStore(const QString &base) 
{
	QDir dir(base + "/data");
	if (!dir.exists()) {
	    if (!dir.mkpath(".")) {
	        qDebug() << "Failed to create data directory";
	        return;
	    }
	}

	QFile file(base + "/data/projects.dat");
	if (!file.exists()) {
	    if (file.open(QIODevice::WriteOnly)) {
	        file.close();
		}
	}
}

void StoreInitialiser::createDataTables()
{
	ProjectRepository::createStore();
	TaskRepository::createStore();
	TaskTimerRepository::createStore();
}