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

void StoreInitialiser::createDataTables()
{
	ProjectRepository::createStore();
	TaskRepository::createStore();
	TaskTimerRepository::createStore();
}