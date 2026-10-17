/* =====================================
 *	resetform.h
 *  Richard Muir-Gladman (c) 2026
 *
 *	Licence GPLv3
 * ===================================== */

#pragma once

#include "qtmetamacros.h"
#include "qwidget.h"
#include <QDialog>

class ResetForm : public QDialog
{
    Q_OBJECT

public:
    explicit ResetForm(int id, QWidget *parent = nullptr);
    ~ResetForm() = default;
};