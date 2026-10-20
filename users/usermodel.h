/* =====================================
 *	usermodel.h
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */
#pragma once

#include <QString>

class UserModel
{
public:
    UserModel(int id, QString name, QString email, bool active);

    int id();
    QString name();
    QString email();
    bool active();

    UserModel login(QString email, QString password);
    void logout();

private:
    int mId;
    QString mName;
    QString mEmail;
    bool mActive;
};