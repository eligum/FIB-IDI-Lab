#pragma once

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class MyForm; }
QT_END_NAMESPACE

class MyForm : public QWidget
{
    Q_OBJECT

public:
    MyForm(QWidget* parent = nullptr);
    ~MyForm();

private:
    Ui::MyForm* ui;
};
