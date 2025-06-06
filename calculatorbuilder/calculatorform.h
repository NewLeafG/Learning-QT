// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef CALCULATORFORM_H
#define CALCULATORFORM_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QLabel;
class QSpinBox;
class QLineEdit;
class QPushButton;
QT_END_NAMESPACE

//! [0]
class CalculatorForm : public QWidget
{
    Q_OBJECT

public:
    explicit CalculatorForm(QWidget *parent = nullptr);

private slots:
    void on_inputSpinBox1_valueChanged(int value);
    void on_inputSpinBox2_valueChanged(int value);
    void on_btn_enter_clicked();

private:
    QSpinBox *ui_inputSpinBox1;
    QSpinBox *ui_inputSpinBox2;
    QLabel *ui_outputWidget;
    QLineEdit *ui_inputResistor;
    QPushButton *ui_btnEnter;

};
//! [0]

#endif
