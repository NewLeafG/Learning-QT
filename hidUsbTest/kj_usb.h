#ifndef KJ_USB_H
#define KJ_USB_H

#include <QObject>
#include "hidapi-win/include/hidapi.h"

class KjUsb : public QObject
{
    Q_OBJECT
public:
    explicit KjUsb(QObject *parent = nullptr);

    QByteArray HexStringToByteArray(QString HexString);
    QString ByteArrayToHexString(QByteArray data);
    void Receive_USBHID_message();

    Q_INVOKABLE QString on_pushButton_detectusb_clicked();

    bool on_pushButton_usblock_clicked(QString dev,bool cmd);

    void on_comboBox_usbhid_currentTextChanged();



    void on_checkBox_HexReceive_clicked();

    void on_checkBox_HexSend_clicked();

    void on_pushButton_HIDSend_clicked(bool hex,QString sendMsg);

signals:
     void msgReceived(QString msg);

private slots:

private:
    /*usbhid*/
    hid_device *handle;
    unsigned short vendor_id;
    unsigned short product_id;
    bool USBHID_Rev_Enable;
    unsigned char usb_data[65];

};

#endif // KJ_USB_H
