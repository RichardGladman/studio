/* =====================================
 *	customerrepository.h
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */

#pragma once

#include <QStringList>

#include "customermodel.h"
#include "../common/listdata.h"

class CustomerRepository
{
public:
    static void createStore();

    static QList<ListData> list(QString searchFor, bool inactive = false);
    static CustomerModel load(int id);

    static bool insert(CustomerModel *model);
    static bool update(CustomerModel *model);
    static bool activate(int id);
    static bool deactivate(int id);
};