/*
The MIT License (MIT)

Copyright © 2022 Antonio Dias

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore>
#include <QtGui>
#include <QtWidgets>
#include <QGoodWindow>
#include <QGoodCentralWidget>

#include "ui_centralwidget.h"
#include <QSerialPort>
#include "msg_processer.h"
#include <QTimer>

class CentralWidget : public QMainWindow
{
    Q_OBJECT
public:
    explicit CentralWidget(QWidget *parent = nullptr) : QMainWindow(parent), ui(new Ui::CentralWidget)
    {
        ui->setupUi(this);
        connect(ui->chk_data1,SIGNAL(clicked()),this,SLOT(on_chk_data_clicked()));
        connect(ui->chk_data2,SIGNAL(clicked()),this,SLOT(on_chk_data_clicked()));
        connect(ui->chk_data3,SIGNAL(clicked()),this,SLOT(on_chk_data_clicked()));
        connect(ui->chk_data4,SIGNAL(clicked()),this,SLOT(on_chk_data_clicked()));
        connect(ui->chk_data5,SIGNAL(clicked()),this,SLOT(on_chk_data_clicked()));
        connect(ui->chk_data6,SIGNAL(clicked()),this,SLOT(on_chk_data_clicked()));
        connect(ui->chk_data7,SIGNAL(clicked()),this,SLOT(on_chk_data_clicked()));
        connect(ui->chk_data8,SIGNAL(clicked()),this,SLOT(on_chk_data_clicked()));
        connect(ui->chk_data9,SIGNAL(clicked()),this,SLOT(on_chk_data_clicked()));
        connect(ui->chk_data10,SIGNAL(clicked()),this,SLOT(on_chk_data_clicked()));
        connect(ui->chk_data11,SIGNAL(clicked()),this,SLOT(on_chk_data_clicked()));
        connect(ui->chk_data12,SIGNAL(clicked()),this,SLOT(on_chk_data_clicked()));
        connect(ui->chk_data13,SIGNAL(clicked()),this,SLOT(on_chk_data_clicked()));
        connect(ui->chk_data14,SIGNAL(clicked()),this,SLOT(on_chk_data_clicked()));
        connect(ui->chk_data15,SIGNAL(clicked()),this,SLOT(on_chk_data_clicked()));

//        connect(ui->sb_data1,&QSpinBox::valueChanged,this,&CentralWidget::on_sb_data_valueChanged);//QT5不支持这个connect重载函数
//        connect(ui->sb_data2,&QSpinBox::valueChanged,this,&CentralWidget::on_sb_data_valueChanged);
//        connect(ui->sb_data3,&QSpinBox::valueChanged,this,&CentralWidget::on_sb_data_valueChanged);
//        connect(ui->sb_data4,&QSpinBox::valueChanged,this,&CentralWidget::on_sb_data_valueChanged);
//        connect(ui->sb_data5,&QSpinBox::valueChanged,this,&CentralWidget::on_sb_data_valueChanged);
//        connect(ui->sb_data6,&QSpinBox::valueChanged,this,&CentralWidget::on_sb_data_valueChanged);
//        connect(ui->sb_data7,&QSpinBox::valueChanged,this,&CentralWidget::on_sb_data_valueChanged);
//        connect(ui->sb_data8,&QSpinBox::valueChanged,this,&CentralWidget::on_sb_data_valueChanged);
//        connect(ui->sb_data9,&QSpinBox::valueChanged,this,&CentralWidget::on_sb_data_valueChanged);
//        connect(ui->sb_data10,&QSpinBox::valueChanged,this,&CentralWidget::on_sb_data_valueChanged);
//        connect(ui->sb_data11,&QSpinBox::valueChanged,this,&CentralWidget::on_sb_data_valueChanged);
//        connect(ui->sb_data12,&QSpinBox::valueChanged,this,&CentralWidget::on_sb_data_valueChanged);
//        connect(ui->sb_data13,&QSpinBox::valueChanged,this,&CentralWidget::on_sb_data_valueChanged);
//        connect(ui->sb_data14,&QSpinBox::valueChanged,this,&CentralWidget::on_sb_data_valueChanged);
//        connect(ui->sb_data15,&QSpinBox::valueChanged,this,&CentralWidget::on_sb_data_valueChanged);

        connect(ui->sb_data1,SIGNAL(valueChanged(int)),this,SLOT(on_sb_data_valueChanged(int)));
        connect(ui->sb_data2,SIGNAL(valueChanged(int)),this,SLOT(on_sb_data_valueChanged(int)));
        connect(ui->sb_data3,SIGNAL(valueChanged(int)),this,SLOT(on_sb_data_valueChanged(int)));
        connect(ui->sb_data4,SIGNAL(valueChanged(int)),this,SLOT(on_sb_data_valueChanged(int)));
        connect(ui->sb_data5,SIGNAL(valueChanged(int)),this,SLOT(on_sb_data_valueChanged(int)));
        connect(ui->sb_data6,SIGNAL(valueChanged(int)),this,SLOT(on_sb_data_valueChanged(int)));
        connect(ui->sb_data7,SIGNAL(valueChanged(int)),this,SLOT(on_sb_data_valueChanged(int)));
        connect(ui->sb_data8,SIGNAL(valueChanged(int)),this,SLOT(on_sb_data_valueChanged(int)));
        connect(ui->sb_data9,SIGNAL(valueChanged(int)),this,SLOT(on_sb_data_valueChanged(int)));
        connect(ui->sb_data10,SIGNAL(valueChanged(int)),this,SLOT(on_sb_data_valueChanged(int)));
        connect(ui->sb_data11,SIGNAL(valueChanged(int)),this,SLOT(on_sb_data_valueChanged(int)));
        connect(ui->sb_data12,SIGNAL(valueChanged(int)),this,SLOT(on_sb_data_valueChanged(int)));
        connect(ui->sb_data13,SIGNAL(valueChanged(int)),this,SLOT(on_sb_data_valueChanged(int)));
        connect(ui->sb_data14,SIGNAL(valueChanged(int)),this,SLOT(on_sb_data_valueChanged(int)));
        connect(ui->sb_data15,SIGNAL(valueChanged(int)),this,SLOT(on_sb_data_valueChanged(int)));

        connect(timer_1000ms, &QTimer::timeout, this, &CentralWidget::timeout1Hz);
        timer_1000ms->start(1000);

//        int width_parent = ui->verticalLayout_left->parentWidget()->width();
//        int height_parent = ui->verticalLayout_left->parentWidget()->height();

//        ui->verticalLayout_left->setGeometry(0,0,width_parent/3,height_parent);
    }

    ~CentralWidget()
    {
        delete ui;
    }

    void fillPortsInfo();
    void fillPortsParameters();

    QSerialPort *m_serial = nullptr;
    msg_processer msg_handler;
    bool b_send_clicked=0;
    Ui::CentralWidget *ui;
    QObject* m_cmd_sender;
    QTimer *timer_1000ms = new QTimer(this);
    bool m_b_connected=0;

private slots:
    void on_cb_serialPorts_activated(int index);


    void on_btn_connect_clicked();
    void on_btn_send_clicked();
    void on_btn_clrReceive_clicked();
    void on_btn_writeAll_clicked();
    void on_btn_readAll_clicked();

    void on_chk_data_clicked();
    void on_sb_data_valueChanged(int arg1);
    void on_btn_clrAll_clicked();
    void timeout1Hz();
};

class MainWindow : public QGoodWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void themeChange();
    void readData();

private:
    //Functions
#ifdef QT_VERSION_QT5
    bool nativeEvent(const QByteArray &eventType, void *message, long *result);
#endif
#ifdef QT_VERSION_QT6
    bool nativeEvent(const QByteArray &eventType, void *message, qintptr *result);
#endif
    void closeEvent(QCloseEvent *event);

    //Variables
    QGoodCentralWidget *m_good_central_widget;
    CentralWidget *m_central_widget;
};

#endif // MAINWINDOW_H
