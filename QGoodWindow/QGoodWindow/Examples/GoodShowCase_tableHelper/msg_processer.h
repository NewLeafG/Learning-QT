#ifndef MSG_PROCESSER_H
#define MSG_PROCESSER_H

#include <QtCore>

using namespace std;


typedef struct
{
    int cmd;
    std::vector<uint8_t> data;
}msgData;


class msg_processer
{
public:
    msg_processer();

    QByteArray pack_Get(QByteArray attrid);
    QByteArray pack_Set(QByteArray value); //串口发送数据长度注意不要过长
    msgData msg_parser(QByteArray msg);

};

#endif // MSG_PROCESSER_H
