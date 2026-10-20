/* =====================================
 *  userrepository.cpp
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */

#include "userrepository.h"
#include "usermodel.h"
#include <qsqlquery.h>

extern UserModel user;

 void UserRepository::login(QString email, QString password)
 {
    QSqlQuery query;

    query.prepare("SELECT id, name, email, active FROM staff WHERE email=? AND password=? AND active=1");
    query.addBindValue(email);
    query.addBindValue(password);

    if (query.exec() && query.next()) {
        user.id(query.value(0).toInt());
        user.name(query.value(1).toString());
        user.email(query.value(2).toString());
        user.active(query.value(3).toBool());
        user.loggedIn(true);
    }
 }
