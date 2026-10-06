/* =====================================
 *	staffrepository.h
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */

#pragma once

#include <QStringList>

#include "staffmodel.h"
#include "../common/listdata.h"

class StaffRepository
{
public:
    static void createStore();

    static QList<ListData> list(QString searchFor, bool inactive = false);
    static StaffModel load(int id);

    static bool insert(StaffModel *model);
    static bool update(StaffModel *model);
    static bool activate(int id);
    static bool deactivate(int id);
};