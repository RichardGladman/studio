/* =====================================
 *  userrepository.cpp
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */

#include "userrepository.h"
#include "usermodel.h"
#include <qsqlquery.h>

 UserModel UserRepository::login(QString email, QString password)
 {
    UserModel model {0, "", "", false, false};
    QSqlQuery query;

    query.prepare("SELECT id, name, email, active FROM staff WHERE email=? AND password=? AND active=1");
    query.addBindValue(email);
    query.addBindValue(password);

    if (query.exec() && query.next()) {
        model.id(query.value(0).toInt());
        model.name(query.value(1).toString());
        model.email(query.value(2).toString());
        model.active(query.value(3).toBool());
        model.loggedIn(true);
    }

    return model;
 }
