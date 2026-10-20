//
// Created by richard on 20.10.2026 
//
#include "userutils.h"
#include "loginform.h"
#include <qdialog.h>

void UserUtils::renderLoginForm(QWidget *parent)
{
    LoginForm *form = new LoginForm(parent);
    form->exec();
}