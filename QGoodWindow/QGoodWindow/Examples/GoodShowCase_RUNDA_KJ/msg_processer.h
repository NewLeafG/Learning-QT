#ifndef MSG_PROCESSER_H
#define MSG_PROCESSER_H

#include <QtCore>

using namespace std;


typedef struct
{
    int cmd;
    QString ver;
    std::vector<uint8_t> data;
}msgData;


class msg_processer
{
public:
    msg_processer();

    QByteArray pack_Get(QByteArray attrid);
    QByteArray pack_Set(QByteArray value); //串口发送数据长度注意不要过长
    QByteArray pack_Heartbeat(void);
    msgData msg_parser(QByteArray msg);

private:
    vector<uint8_t> m_readBuffer;
    uchar rx_num=0;
    uchar rx_f=0;
};

#endif // MSG_PROCESSER_H
