/* =====================================
 *  usermodel.cpp
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */
#include "usermodel.h"
#include "userrepository.h"

UserModel::UserModel(int id, QString name, QString email, bool active, bool loggedIn) :
                        mId(id), mName(name), mEmail(email), mActive(active), mLoggedIn(loggedIn) {}

int UserModel::id() 
{
    return mId;
}

QString UserModel::name()
{
    return mName;
}

QString UserModel::email()
{
    return mEmail;
}

bool UserModel::active()
{
    return mActive;
}

bool UserModel::loggedIn()
{
    return mLoggedIn;
}

void UserModel::id(int id)
{
    mId = id;
}

void UserModel::name(QString name)
{
    mName = name;
}

void UserModel::email(QString email)
{
    mEmail = email;
}

void UserModel::active(bool active)
{
    mActive = active;
}

void UserModel::loggedIn(bool loggedIn)
{
    mLoggedIn = loggedIn;
}

void UserModel::login(QString email, QString password)
{
    UserRepository::login(email, password);
}

void UserModel::logout() {}
