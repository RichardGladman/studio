/* =====================================
 *  userrepository.h
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */

#pragma once

#include "usermodel.h"

#include <QString>

class UserRepository
{
    UserModel login(QString email, QString password);
};