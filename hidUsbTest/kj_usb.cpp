#include "kj_usb.h"
#include <QTimer>
#include <QDateTime>

KjUsb::KjUsb(QObject *parent)
    : QObject{parent}
{
    USBHID_Rev_Enable = false;

    QTimer *timer1 = new QTimer(this);
    connect(timer1, &QTimer::timeout, this, &KjUsb::Receive_USBHID_message);
    timer1->start(10);

}

QString KjUsb::on_pushButton_detectusb_clicked()
{
    hid_init();
    struct hid_device_info * P_device;

    P_device = hid_enumerate(0, 0);

    //清空usbhid设备框
    // ui->comboBox_usbhid->clear();

    // if(P_device != NULL)
    //     statusBar()->showMessage("检测到USBHID设备",3000);

    QString devicesName;
    while(P_device != NULL)
    {
        devicesName.append(QString::fromWCharArray(P_device->product_string));
        devicesName.append(',');
        P_device = P_device->next;
    }

    hid_free_enumeration(P_device);
    hid_exit();
    return devicesName;
}

bool KjUsb::on_pushButton_usblock_clicked(QString dev,bool cmd)
{
    char s[100];
    bool rst=false;

    if(cmd)//打开
    {
        hid_init();
        struct hid_device_info * P_device;

        P_device = hid_enumerate(0, 0);
        while(P_device != NULL)
        {
            if(dev == (QString::fromWCharArray(P_device->product_string)))
            {
                this->vendor_id = P_device->vendor_id;
                this->product_id = P_device->product_id;
                break;
            }
            P_device = P_device->next;
        }

        //已经获得选中项的vid&pid，释放设备链表
        hid_free_enumeration(P_device);

        this->handle = hid_open(this->vendor_id , this->product_id, NULL);

        if(NULL != this->handle)
        {
            USBHID_Rev_Enable = true;
            qDebug("成功打开vid=0x%04x,pid=0x%04x 的usbhid设备！", this->vendor_id, this->product_id);
            sprintf(s,"成功打开vid=0x%04x,pid=0x%04x 的usbhid设备！", this->vendor_id, this->product_id);

            //在界面显示vid和pid
//            char s[40];
//            sprintf(s,"VID:0x%04X", this->vendor_id);
//            QString vid_str = s;
//            ui->label_vid->setText(vid_str);
//            sprintf(s,"PID:0x%04X", this->product_id);
//            QString pid_str = s;
//            ui->label_pid->setText(pid_str);

//            //以下控件失效
//            ui->pushButton_detectusb->setEnabled(false);
//            ui->comboBox_usbhid->setEnabled(false);
//            //以下控件使能
//            ui->pushButton_HIDSend->setEnabled(true);
        }else
        {
            qDebug("打开vid=0x%04x,pid=0x%04x 的usbhid设备失败！", this->vendor_id, this->product_id);
//            sprintf(s,"打开vid=0x%04x,pid=0x%04x 的usbhid设备失败！", this->vendor_id, this->product_id);
//            statusBar()->showMessage(QString(s),3000);
            return rst;
        }
    }
    else
    {
        hid_close(this->handle);
        USBHID_Rev_Enable = false;
        qDebug("成功关闭vid=0x%04x,pid=0x%04x 的usbhid设备！", this->vendor_id, this->product_id);
//        sprintf(s,"成功关闭vid=0x%04x,pid=0x%04x 的usbhid设备！", this->vendor_id, this->product_id);
//        statusBar()->showMessage(QString(s),3000);

        hid_exit();
//        ui->pushButton_usblock->setText(QString("打开"));      //usb进入关闭状态

        QString vid_str = "VID:";
        QString pid_str = "PID:";
//        ui->label_vid->setText(vid_str);
//        ui->label_pid->setText(pid_str);

//        //以下控件使能
//        ui->pushButton_detectusb->setEnabled(true);
//        ui->comboBox_usbhid->setEnabled(true);
//        //以下控件失效
//        ui->pushButton_HIDSend->setEnabled(false);
    }
    return rst;
}

void KjUsb::on_comboBox_usbhid_currentTextChanged()
{
//    hid_init();
//    struct hid_device_info * P_device;

//    P_device = hid_enumerate(0, 0);
//    while(P_device != NULL)
//    {
//        if((ui->comboBox_usbhid->currentText()) == (QString::fromWCharArray(P_device->product_string)))
//        {
//            this->vendor_id = P_device->vendor_id;
//            this->product_id = P_device->product_id;
//            break;
//        }
//        P_device = P_device->next;
//    }

//    //已经获得选中项的vid&pid，释放设备链表
//    hid_free_enumeration(P_device);

//    char s[100];
//    sprintf(s,"VID:0x%04X", this->vendor_id);
//    QString vid_str = s;
//    ui->label_vid->setText(vid_str);
//    sprintf(s,"PID:0x%04X", this->product_id);
//    QString pid_str = s;
//    ui->label_pid->setText(pid_str);

//    sprintf(s,"设备属性:vid=0x%04x,pid=0x%04x", this->vendor_id, this->product_id);
//    statusBar()->showMessage(QString(s),3000);
}


void KjUsb::on_checkBox_HexReceive_clicked()
{

}

void KjUsb::on_checkBox_HexSend_clicked()
{
}

/*
 * @breif 将16进制字符串转换为对应的字节序列
 */
QByteArray KjUsb::HexStringToByteArray(QString HexString)
{
    bool ok;
    QByteArray ret;
    HexString = HexString.trimmed();
    HexString = HexString.simplified();
    QStringList sl = HexString.split(" ");

    foreach (QString s, sl) {
        if(!s.isEmpty())
        {
            char c = s.toInt(&ok,16)&0xFF;
            if(ok){
                ret.append(c);
            }else{
                qDebug("非法的16进制字符：");
            }
        }
    }
    //qDebug()<<ret;
    return ret;
}

/*
 * @breif 将字节序列转换为对应的16进制字符串
 */
QString KjUsb::ByteArrayToHexString(QByteArray data){
    QString ret(data.toHex().toUpper());
    int len = ret.length()/2;
    for(int i=1;i<len;i++)
    {
        //qDebug()<<i;
        ret.insert(2*i+i-1," ");
    }

    return ret;
}

void KjUsb::Receive_USBHID_message()
{

    if(USBHID_Rev_Enable)
    {
        int res = hid_read_timeout(this->handle, usb_data, 64, 1);

        if(res>0)
        {
            QDateTime time = QDateTime::currentDateTime();
            QString time_qstr = time.toString("yyyy-MM-dd hh:mm:ss");

            QString qstr = "接收时间:"+time_qstr+"\r\n----------------------\r\n";


            for(int i=0; i<64; i++)
            {
                qstr += QString(QByteArray((char *)&usb_data[i],1).toHex()).toUpper();
                qstr += " ";
            }

            emit msgReceived(qstr);
        }
    }
}

void KjUsb::on_pushButton_HIDSend_clicked(bool hex,QString sendMsg)
{
    unsigned char usb_data[65];
    char s[100];

    //获取界面上的数据并转换成utf8格式的字节流
//    QString sendMsg = ui->textEdit_send->toPlainText();
    QByteArray data = sendMsg.toLatin1();

    //如果以16进制发送
    if(hex)
    {
        data = HexStringToByteArray(sendMsg);
    }

    for(int i=1; i<65; i++)
    {
        if(i<data.length()+1)
            usb_data[i]=data.data()[i-1];
        else
            usb_data[i]=0xff;
    }

    int res = hid_write(this->handle, usb_data, 65);    //至少写入64字节，协议64字节，第一个字节作废

    qDebug("写入结果res = %d", res);
    if(-1 == res)
    {
        qDebug("USBHID写入字节错误！");
//        statusBar()->showMessage("USBHID写入字节错误！",3000);
        return;
    }
    else
    {
        qDebug("USBHID写入成功，实际写入了 %d 个字节！", res-1);
        sprintf(s,"USBHID写入成功，实际写入了 %d 个字节！", res-1);
//        statusBar()->showMessage(QString(s),3000);
    }
}
// ————————————————
// 版权声明：本文为CSDN博主「超级大洋葱806」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
// 原文链接：https://blog.csdn.net/u014779536/article/details/104534462/
