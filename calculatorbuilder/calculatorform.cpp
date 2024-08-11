// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

//! [0]
#include <QtUiTools>
//! [0]
#include <QSpinBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QFile>

#include "calculatorform.h"
#include <QtCore/qmath.h>

#define NTC_B 4200
#define NTC_R25 281300

//! [1]
CalculatorForm::CalculatorForm(QWidget *parent)
    : QWidget(parent)
{
    QUiLoader loader;

    QFile file(":/forms/calculatorform.ui");
    file.open(QFile::ReadOnly);
    QWidget *formWidget = loader.load(&file, this);
    file.close();
//! [1]

//! [2]
    ui_inputSpinBox1 = findChild<QSpinBox*>("inputSpinBox1");
    ui_inputSpinBox2 = findChild<QSpinBox*>("inputSpinBox2");
    ui_outputWidget = findChild<QLabel*>("outputWidget");
    ui_inputResistor = findChild<QLineEdit*>("inputResistor");
    ui_btnEnter = findChild<QPushButton*>("btn_enter");
//! [2]

//! [3]
    QMetaObject::connectSlotsByName(this);
//! [3]

//! [4]
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(formWidget);
    setLayout(layout);

    setWindowTitle(tr("Calculator Builder"));
}
//! [4]

//! [5]
void CalculatorForm::on_inputSpinBox1_valueChanged(int value)
{
//    ui_outputWidget->setText(QString::number(value + ui_inputSpinBox2->value()));
}
//! [5] //! [6]

//! [6] //! [7]
void CalculatorForm::on_inputSpinBox2_valueChanged(int value)
{
//    ui_outputWidget->setText(QString::number(value + ui_inputSpinBox1->value()));
}
//! [7]

/*************************************************
[函数名称]fGet_NTC_Temp
[函数功能]计算ntc温度
[参    数]Rntc 当前的NTC电阻值
[全局变量]
[返 回 值]当前的温度值
[备    注]
*************************************************/
void CalculatorForm::on_btn_enter_clicked()
{
//    double b=qExp(1);
//    b=1;

    double temp;
    temp=qLn(1829/NTC_R25);
    temp=1/(1/298.15+(1/NTC_B)*temp);
    temp-=273.15;
}
