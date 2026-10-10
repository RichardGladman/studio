/* =====================================
 *	teamrepository.h
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */

#pragma once

#include "teammodel.h"

class TeamRepository
{
public:
    static void createStore();

    static TeamModel load(int id);

    static bool insert(TeamModel *model);
    static bool update(TeamModel *model);
    static bool activate(int id);
    static bool deactivate(int id);
};