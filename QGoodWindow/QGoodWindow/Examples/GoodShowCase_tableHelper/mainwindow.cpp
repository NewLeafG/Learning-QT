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

#ifdef _WIN32

#ifdef _WIN32_WINNT
#undef _WIN32_WINNT
#endif

#define _WIN32_WINNT _WIN32_WINNT_VISTA

#include <windows.h>
#include <dwmapi.h>

#endif

#include "mainwindow.h"
#include <QSerialPortInfo>
#include<string>

static const char blankString[] = QT_TRANSLATE_NOOP("SettingsDialog", "N/A");

#ifdef QGOODWINDOW
inline qreal pixelRatio()
{
    QScreen *screen = QApplication::primaryScreen();

#ifdef Q_OS_MAC
    qreal pixel_ratio = screen->devicePixelRatio();
#else
    qreal pixel_ratio = screen->logicalDotsPerInch() / qreal(96);
#endif

    return pixel_ratio;
}
#endif

MainWindow::MainWindow(QWidget *parent) : QGoodWindow(parent)
{
    m_central_widget = new CentralWidget(this);
    m_central_widget->setWindowFlags(Qt::Widget);

    m_good_central_widget = new QGoodCentralWidget(this);

#ifdef QGOODWINDOW
#ifndef Q_OS_MAC
    QMenuBar *menu_bar = m_central_widget->menuBar();

    //Set font of menu bar
    QFont font = menu_bar->font();
    font.setPixelSize(qRound(12 * pixelRatio()));
#ifdef Q_OS_WIN
    font.setFamily("Segoe UI");
#else
    font.setFamily(qApp->font().family());
#endif
    menu_bar->setFont(font);

    QTimer::singleShot(0, this, [=]{
        menu_bar->setFixedWidth(menu_bar->sizeHint().width());
        const int title_bar_height = m_good_central_widget->titleBarHeight();
        menu_bar->setStyleSheet(QString("QMenuBar {height: %0px;}").arg(title_bar_height));
    });

    m_good_central_widget->setLeftTitleBarWidget(menu_bar);
#endif

    QWidget *widget = new QWidget();

    QHBoxLayout *layout = new QHBoxLayout(widget);
    layout->setContentsMargins(0, 0, 0, 0);

    // QPushButton *button = new QPushButton("Toggle All!", widget);

    // connect(button, &QPushButton::clicked, this, [=]{
    //     m_good_central_widget->setTitleVisible(!m_good_central_widget->isTitleVisible());
    //     m_good_central_widget->setIconVisible(!m_good_central_widget->isIconVisible());
    //     m_good_central_widget->setTitleBarColor(!m_good_central_widget->isTitleVisible() ? Qt::red : QColor());
    //     m_good_central_widget->setActiveBorderColor(!m_good_central_widget->isTitleVisible() ? Qt::red : QColor());
    // });

    QLabel *label = new QLabel("升降桌助手", widget);
    label->setAttribute(Qt::WA_TransparentForMouseEvents);

//    layout->addWidget(button);
    layout->addWidget(label);

    m_good_central_widget->setRightTitleBarWidget(widget, true);
#endif

    connect(qGoodStateHolder, &QGoodStateHolder::currentThemeChanged, this, &MainWindow::themeChange);

    connect(this, &QGoodWindow::systemThemeChanged, this, [=]{
        qGoodStateHolder->setCurrentThemeDark(QGoodWindow::isSystemThemeDark());
    });

    QShortcut *shortcut1 = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_S), this);

    connect(shortcut1, &QShortcut::activated, this, [=]{
        qGoodStateHolder->setCurrentThemeDark(!qGoodStateHolder->isCurrentThemeDark());
    });

    QShortcut *shortcut2 = new QShortcut(QKeySequence(Qt::CTRL | Qt::Key_T), this);

    connect(shortcut2, &QShortcut::activated, this, [=]{
        m_good_central_widget->setTitleBarVisible(!m_good_central_widget->isTitleBarVisible());
    });

//    qGoodStateHolder->setCurrentThemeDark(QGoodWindow::isSystemThemeDark());
    qGoodStateHolder->setCurrentThemeDark(true);

    m_good_central_widget->setCentralWidget(m_central_widget);
    setCentralWidget(m_good_central_widget);

    setWindowIcon(qApp->style()->standardIcon(QStyle::SP_DesktopIcon));
    // setWindowTitle("Good Window - CTRL+S toggle theme - CTRL+T toggle title bar!");
    setWindowTitle("TableHelper");

    resize(m_central_widget->size());
    move(QGuiApplication::primaryScreen()->availableGeometry().center() - rect().center());

    m_central_widget->fillPortsInfo();
    m_central_widget->fillPortsParameters();
    m_central_widget->m_serial=new QSerialPort(this);
    connect(m_central_widget->m_serial, &QSerialPort::readyRead, this, &MainWindow::readData);
    this->setWindowIcon(QIcon(":/img/kj_logo.png"));

}

MainWindow::~MainWindow()
{

}

void MainWindow::themeChange()
{
    if (qGoodStateHolder->isCurrentThemeDark())
        setAppDarkTheme();
    else
        setAppLightTheme();
}

#ifdef QT_VERSION_QT5
bool MainWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
#endif
#ifdef QT_VERSION_QT6
bool MainWindow::nativeEvent(const QByteArray &eventType, void *message, qintptr *result)
#endif
{
#ifdef QGOODWINDOW
#ifdef Q_OS_WIN
#ifdef QT_VERSION_QT5
    MSG *msg = static_cast<MSG*>(message);

    switch (msg->message)
    {
    case WM_THEMECHANGED:
    case WM_DWMCOMPOSITIONCHANGED:
    {
        //Keep window theme on Windows theme change events.
        QTimer::singleShot(100, this, [=]{
            if (qGoodStateHolder->isCurrentThemeDark())
                setAppDarkTheme();
            else
                setAppLightTheme();
        });

        break;
    }
    default:
        break;
    }
#endif
#endif
#endif
    return QGoodWindow::nativeEvent(eventType, message, result);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMessageBox msgbox(this);
    msgbox.setIcon(QMessageBox::Question);
    msgbox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgbox.setDefaultButton(QMessageBox::No);
    msgbox.setText("Are you sure to close?");
    msgbox.setWindowTitle("kjdq");

    int result = QGoodCentralWidget::execDialogWithWindow(&msgbox, this, m_good_central_widget);

    if (result != QMessageBox::Yes)
    {
        event->ignore();
        return;
    }
}

void CentralWidget::fillPortsInfo()
{
    const auto infos = QSerialPortInfo::availablePorts();
    if(infos.count()==ui->cb_serialPorts->count())
        return;

    ui->cb_serialPorts->clear();
    const QString blankString = tr(::blankString);

    for (const QSerialPortInfo &info : infos) {
        QStringList list;
        const QString description = info.description();
        const QString manufacturer = info.manufacturer();
        const QString serialNumber = info.serialNumber();
        const auto vendorId = info.vendorIdentifier();
        const auto productId = info.productIdentifier();
        list << info.portName()
             << (!description.isEmpty() ? description : blankString)
             << (!manufacturer.isEmpty() ? manufacturer : blankString)
             << (!serialNumber.isEmpty() ? serialNumber : blankString)
             << info.systemLocation()
             << (vendorId ? QString::number(vendorId, 16) : blankString)
             << (productId ? QString::number(productId, 16) : blankString);

        ui->cb_serialPorts->addItem(list.constFirst()+"("+list[1]+")", list);
    }

//    ui->cb_serialPorts->addItem(tr("Custom"));
}

void CentralWidget::fillPortsParameters()
{
    ui->cb_baudrate->addItem(QStringLiteral("19200"), QSerialPort::Baud19200);
    ui->cb_baudrate->addItem(QStringLiteral("9600"), QSerialPort::Baud9600);
    ui->cb_baudrate->addItem(QStringLiteral("38400"), QSerialPort::Baud38400);
    ui->cb_baudrate->addItem(QStringLiteral("115200"), QSerialPort::Baud115200);
    ui->cb_baudrate->addItem(tr("Custom"));

    ui->cb_databits->addItem(QStringLiteral("5"), QSerialPort::Data5);
    ui->cb_databits->addItem(QStringLiteral("6"), QSerialPort::Data6);
    ui->cb_databits->addItem(QStringLiteral("7"), QSerialPort::Data7);
    ui->cb_databits->addItem(QStringLiteral("8"), QSerialPort::Data8);
    ui->cb_databits->setCurrentIndex(3);

    ui->cb_parity->addItem(tr("None"), QSerialPort::NoParity);
    ui->cb_parity->addItem(tr("Even"), QSerialPort::EvenParity);
    ui->cb_parity->addItem(tr("Odd"), QSerialPort::OddParity);
    ui->cb_parity->addItem(tr("Mark"), QSerialPort::MarkParity);
    ui->cb_parity->addItem(tr("Space"), QSerialPort::SpaceParity);

    ui->cb_stopBits->addItem(QStringLiteral("1"), QSerialPort::OneStop);
#ifdef Q_OS_WIN
    ui->cb_stopBits->addItem(tr("1.5"), QSerialPort::OneAndHalfStop);
#endif
    ui->cb_stopBits->addItem(QStringLiteral("2"), QSerialPort::TwoStop);

    ui->cb_flowControl->addItem(tr("None"), QSerialPort::NoFlowControl);
    ui->cb_flowControl->addItem(tr("RTS/CTS"), QSerialPort::HardwareControl);
    ui->cb_flowControl->addItem(tr("XON/XOFF"), QSerialPort::SoftwareControl);
}

void CentralWidget::on_cb_serialPorts_activated(int index)
{
    QList<QSerialPortInfo> ports = QSerialPortInfo::availablePorts();
    if(ports.size()!=ui->cb_serialPorts->count())
    {
        fillPortsInfo();
    }

}


void CentralWidget::on_btn_connect_clicked()
{
    int idx=ui->cb_serialPorts->currentIndex();
    if(idx<0)
    {
        QMessageBox::critical(this, "无可用设备！", m_serial->errorString());
        return;
    }

    if (m_serial->isOpen())
    {
        m_serial->close();
        ui->btn_connect->setText("连接");
        m_b_connected=0;
    }
else{
    const QStringList list = ui->cb_serialPorts->itemData(idx).toStringList();

    m_serial->setPortName(list[0]);
    const auto baudRateData = ui->cb_baudrate->currentData();
    m_serial->setBaudRate(baudRateData.value<QSerialPort::BaudRate>());
    const auto dataBitsData = ui->cb_databits->currentData();
    m_serial->setDataBits(dataBitsData.value<QSerialPort::DataBits>());
    const auto parityData = ui->cb_parity->currentData();
    m_serial->setParity(parityData.value<QSerialPort::Parity>());
    const auto stopBitsData = ui->cb_stopBits->currentData();
    m_serial->setStopBits(stopBitsData.value<QSerialPort::StopBits>());
    const auto flowControlData = ui->cb_flowControl->currentData();
    m_serial->setFlowControl(flowControlData.value<QSerialPort::FlowControl>());
    if (m_serial->open(QIODevice::ReadWrite)) {
        ui->btn_connect->setText("断开连接");
        m_b_connected=true;
    } else {
        QMessageBox::critical(this, tr("Error"), m_serial->errorString());

    }
    }
}


void CentralWidget::on_btn_send_clicked()
{
//    m_serial->write(ui->lineEdit_send->text().toUtf8());
    QByteArray qbyte;
    QString hex=(ui->lineEdit_send->text()).trimmed();

        QStringList sl=hex.split(" ");
        foreach(QString s,sl)
        {
            if(!s.isEmpty())
                qbyte.append((char)s.toInt(0,16)&0xFF);
        }
    m_serial->write(qbyte);
    b_send_clicked=1;

}

void MainWindow::readData()
{
    const QByteArray dataBA = m_central_widget->m_serial->readAll();
//    QString data(dataBA);

//    m_central_widget->ui->textBrowser_receive->append(data);
//    m_central_widget->ui->textBrowser_receive->append(dataBA.toHex(' ').toUpper());//append接口会自动换行
    m_central_widget->ui->textBrowser_receive->insertPlainText(dataBA.toHex(' ').toUpper());
    msgData ret = m_central_widget->msg_handler.msg_parser(dataBA);
    if(ret.cmd>0)
    {
        m_central_widget->ui->textBrowser_receive->append(QTime::currentTime().toString("hh:mm:ss")+": 成功发送指令："+QString::number(ret.cmd)+"\r\n");
        m_central_widget->ui->lineEdit_version->setText(ret.ver);
        m_central_widget->ui->cb_version->setChecked(true);
        QList<QCheckBox*> cbList = this->findChildren<QCheckBox*>();
        switch (ret.cmd)
        {
        case 0x01://SET
            if("btn_writeAll"==m_central_widget->m_cmd_sender->objectName())
            {
                for(int i=0;i<cbList.count();i++)
                {
                    cbList[i]->setChecked(true);
                }
            }
            else
            {
                QCheckBox* cb = qobject_cast<QCheckBox*>(m_central_widget->m_cmd_sender);//获取发射信号的对象
                cb->setChecked(true);
            }
            break;

        case 0x03://GET
            for(uint i=0;i<ret.data.size();)
            {
                if(2==ret.data[i])
                {
                    QList<QSpinBox *> sb = this->findChildren<QSpinBox *> ("sb_data"+QString::number(ret.data[i+1]));
                    if(sb.count()>0)
                    {
                        sb[0]->setValue(ret.data[i+2]);
                    }
                    QList<QCheckBox *> cb = this->findChildren<QCheckBox *> ("chk_data"+QString::number(ret.data[i+1]));
                    if(cb.count()>0)
                    {
                        cb[0]->setChecked(true);
                    }
                    i+=3;
                }
                else
                {
                    i=255;
                }
            }
            break;

        default:
            break;
        }
    }
    else if(m_central_widget->b_send_clicked)
    {
        m_central_widget->b_send_clicked=0;
        m_central_widget->ui->textBrowser_receive->append("\r\n");//换行
    }
    m_central_widget->ui->textBrowser_receive->moveCursor(QTextCursor::End);
}

void CentralWidget::on_btn_clrReceive_clicked()
{
    ui->textBrowser_receive->clear();
}

void CentralWidget::on_btn_writeAll_clicked()
{
    m_cmd_sender = sender();//获取发射信号的对象

    QByteArray data_raw,data_send;
    data_raw.resize(39);
    data_raw[0]=2;//typeid
    data_raw[1]=1;//attrid
    data_raw[2]=ui->sb_data1->value();//value
    data_raw[3]=2;//typeid
    data_raw[4]=2;//attrid
    data_raw[5]=ui->sb_data2->value();//value
    data_raw[6]=2;//typeid
    data_raw[7]=3;//attrid
    data_raw[8]=ui->sb_data3->value();//value
    data_raw[9]=2;//typeid
    data_raw[10]=4;//attrid
    data_raw[11]=ui->sb_data4->value();//value
    data_raw[12]=2;//typeid
    data_raw[13]=5;//attrid
    data_raw[14]=ui->sb_data5->value();//value
    data_raw[15]=2;//typeid
    data_raw[16]=6;//attrid
    data_raw[17]=ui->sb_data6->value();//value
    data_raw[18]=2;//typeid
    data_raw[19]=7;//attrid
    data_raw[20]=ui->sb_data7->value();//value
    data_raw[21]=2;//typeid
    data_raw[22]=8;//attrid
    data_raw[23]=ui->sb_data8->value();//value
    data_raw[24]=2;//typeid
    data_raw[25]=9;//attrid
    data_raw[26]=ui->sb_data9->value();//value
    data_raw[27]=2;//typeid
    data_raw[28]=10;//attrid
    data_raw[29]=ui->sb_data10->value();//value
    data_raw[30]=2;//typeid
    data_raw[31]=11;//attrid
    data_raw[32]=ui->sb_data11->value();//value
    data_raw[33]=2;//typeid
    data_raw[34]=12;//attrid
    data_raw[35]=ui->sb_data12->value();//value
    data_raw[36]=2;//typeid
    data_raw[37]=13;//attrid
    data_raw[38]=ui->sb_data13->value();//value
    data_raw[36]=2;//typeid
    data_raw[37]=14;//attrid
    data_raw[38]=ui->sb_data14->value();//value14
    data_raw[36]=2;//typeid
    data_raw[37]=15;//attrid
    data_raw[38]=ui->sb_data15->value();//value15
    data_send=msg_handler.pack_Set(data_raw);
    m_serial->write(data_send);
    ui->lineEdit_send->clear();
    ui->lineEdit_send->setText(data_send.toHex(' ').toUpper());

}

void CentralWidget::on_btn_readAll_clicked()
{
    QByteArray data_raw,data_send;
    data_raw.resize(15);//attrId
    data_raw[0]=1;
    data_raw[1]=2;
    data_raw[2]=3;
    data_raw[3]=4;
    data_raw[4]=5;
    data_raw[5]=6;
    data_raw[6]=7;
    data_raw[7]=8;
    data_raw[8]=9;
    data_raw[9]=10;
    data_raw[10]=11;
    data_raw[11]=12;
    data_raw[12]=13;
    data_raw[13]=14;
    data_raw[14]=15;
    data_send=msg_handler.pack_Get(data_raw);
    m_serial->write(data_send);
    ui->lineEdit_send->clear();
    ui->lineEdit_send->setText(data_send.toHex(' ').toUpper());

}


void CentralWidget::on_chk_data_clicked()
{
    QCheckBox* cb = qobject_cast<QCheckBox*>(sender());//获取发射信号的对象
    cb->setChecked(false);
    m_cmd_sender = sender();//获取发射信号的对象
    QString name=m_cmd_sender->objectName();
    name.remove(0,8);
    bool ok = false;
    uchar id=name.toUInt(&ok);
    QList<QSpinBox *> widgets = this->findChildren<QSpinBox *> ("sb_data"+name);

    if(ok&&(widgets.count()>0))
    {
        QByteArray data_raw,data_send;
        data_raw.resize(3);
        data_raw[0]=2;//uint8
        data_raw[1]=id;//attrid
        data_raw[2]=widgets[0]->value();//value
        data_send=msg_handler.pack_Set(data_raw);
        m_serial->write(data_send);
        ui->lineEdit_send->clear();
        ui->lineEdit_send->setText(data_send.toHex(' ').toUpper());
    }

}


void CentralWidget::on_sb_data_valueChanged(int arg1)
{
    QString name=sender()->objectName();
    name.remove(0,7);
    QList<QCheckBox *> widgets = this->findChildren<QCheckBox *> ("chk_data"+name);
    if(widgets.count()>0)
    {
        widgets[0]->setChecked(false);
    }
}


void CentralWidget::on_btn_clrAll_clicked()
{
    QList<QCheckBox*> cbList = this->findChildren<QCheckBox*>();
    for(int i=0;i<cbList.count();i++)
    {
        cbList[i]->setChecked(false);
    }

    QList<QSpinBox*> sbList = this->findChildren<QSpinBox*>();
    for(int i=0;i<sbList.count();i++)
    {
        sbList[i]->setValue(0);
    }

}

void CentralWidget::timeout1Hz()
{
    if(!m_b_connected)
    {
        fillPortsInfo();
    }
    else
    {
        const auto infos = QSerialPortInfo::availablePorts();


        const QString blankString = tr(::blankString);

        bool dev_exist=0;
        for (const QSerialPortInfo &info : infos) {
            if(info.portName()==m_serial->portName())
            {
                dev_exist=1;
            }
        }

        if(!dev_exist)
        {
            m_serial->close();
            ui->btn_connect->setText("连接");
            m_b_connected=0;
            QMessageBox::critical(this, "设备已被移除！", m_serial->errorString());
        }
    }
}
