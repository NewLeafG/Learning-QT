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

        connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(onOpenCFG()));
        connect(ui->actionSave,SIGNAL(triggered()),this,SLOT(onSaveCFG()));

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
    void serialSend(QByteArray data);

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

    void timeout1Hz();
    void onOpenCFG();
    void onSaveCFG();
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
