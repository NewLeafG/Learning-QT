#include "msg_processer.h"

msg_processer::msg_processer()
{

}

QByteArray msg_processer::pack_Get(QByteArray attrid)
{
    vector<uint8_t> ret;
    ret.push_back(0xa5);
    ret.push_back(0xa5);
    ret.push_back(0x03);
    ret.push_back(0x03);//GET
    ret.push_back(0x00);//LEN_H
    ret.push_back(attrid.size());//LEN_L
    ret.push_back(0x00);//msg_id
    for (int i = 0; i < attrid.size(); i++) {
        ret.push_back(attrid[i]);
    }
    uint8_t sum=0xa5;
    for (unsigned long long i = 0; i < ret.size(); ++i) {
        sum+=ret[i];
    }
    ret.push_back(sum);


    return *(new QByteArray(reinterpret_cast<const char*>(ret.data()),ret.size()));
}

QByteArray msg_processer::pack_Set(QByteArray value) //串口发送数据长度注意不要过长
{
    vector<uint8_t> ret;
    ret.push_back(0xa5);
    ret.push_back(0xa5);
    ret.push_back(0x03);
    ret.push_back(0x01);//SET
    ret.push_back(0x00);//LEN_H
    ret.push_back(value.size()+1);//LEN_L
    ret.push_back(0x00);//msg_id
    for (int i = 0; i < value.size(); i++) {
        ret.push_back(value[i]);
    }
    uint8_t sum=0x00;
    for (unsigned long long i = 0; i < ret.size(); ++i) {
        sum+=ret[i];
    }
    ret.push_back(sum);


    return *(new QByteArray(reinterpret_cast<const char*>(ret.data()),ret.size()));
}

msgData msg_processer::msg_parser(QByteArray msg)
{
    msgData ret;
    ret.cmd=-1;

    uint8_t sum=0x00;
    for (int i = 0; i < msg.size(); i++) {
        sum+=msg[i];
    }
    if(sum==msg[msg.size()-1])
    {
        ret.cmd=msg[3];

    }

    return ret;
}







