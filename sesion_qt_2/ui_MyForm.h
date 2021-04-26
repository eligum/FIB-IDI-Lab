/********************************************************************************
** Form generated from reading UI file 'MyForm.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYFORM_H
#define UI_MYFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "MyLineEdit.h"

QT_BEGIN_NAMESPACE

class Ui_MyForm
{
public:
    QPushButton *pushButton;
    MyLineEdit *lineEdit;
    QLabel *label;
    QLabel *label_2;

    void setupUi(QWidget *MyForm)
    {
        if (MyForm->objectName().isEmpty())
            MyForm->setObjectName(QString::fromUtf8("MyForm"));
        MyForm->resize(545, 360);
        pushButton = new QPushButton(MyForm);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(230, 250, 89, 25));
        lineEdit = new MyLineEdit(MyForm);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(220, 150, 113, 25));
        label = new QLabel(MyForm);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(240, 110, 67, 17));
        label_2 = new QLabel(MyForm);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(130, 150, 67, 17));

        retranslateUi(MyForm);
        QObject::connect(lineEdit, SIGNAL(returnPressed(QString)), label, SLOT(setText(QString)));

        QMetaObject::connectSlotsByName(MyForm);
    } // setupUi

    void retranslateUi(QWidget *MyForm)
    {
        MyForm->setWindowTitle(QApplication::translate("MyForm", "Form", nullptr));
        pushButton->setText(QApplication::translate("MyForm", "PushButton", nullptr));
        label->setText(QApplication::translate("MyForm", "TextLabel", nullptr));
        label_2->setText(QApplication::translate("MyForm", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyForm: public Ui_MyForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYFORM_H
