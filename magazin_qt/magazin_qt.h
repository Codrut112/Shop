#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_magazin_qt.h"

class magazin_qt : public QMainWindow
{
    Q_OBJECT

public:
    magazin_qt(QWidget *parent = nullptr);
    ~magazin_qt();

private:
    Ui::magazin_qtClass ui;
};
