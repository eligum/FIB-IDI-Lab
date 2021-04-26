#pragma once

#include "ui_MyForm.h"

class MyForm : public QWidget
{
    Q_OBJECT

public:
    MyForm(QWidget* parent = nullptr);

private:
    Ui::MyForm ui;
};
