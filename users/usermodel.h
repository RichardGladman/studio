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
    UserModel(int id, QString name, QString email, bool active, bool loggedIn);

    int id();
    QString name();
    QString email();
    bool active();
    bool loggedIn();

    void id(int id);
    void name(QString name);
    void email(QString email);
    void active(bool active);
    void loggedIn(bool loggedIn);

    UserModel login(QString email, QString password);
    void logout();

private:
    int mId;
    QString mName;
    QString mEmail;
    bool mActive;
    bool mLoggedIn;
};