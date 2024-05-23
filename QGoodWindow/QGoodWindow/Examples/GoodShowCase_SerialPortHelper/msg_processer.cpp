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
    ret.push_back(attrid.size()+1);//LEN_L
    ret.push_back(0x00);//msg_id
    for (int i = 0; i < attrid.size(); i++) {
        ret.push_back(attrid[i]);
    }
    uint8_t sum=0;
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

    for(int i=0;i<msg.size();i++)
    {
        m_readBuffer.push_back(msg[i]);
        if (0xa5 == m_readBuffer[0])
        {
            if ((rx_num >= (m_readBuffer[1]-1)) && (rx_num > 2)) //
            {
                rx_f |= 1;
            }
            else
                rx_num++;

            if (m_readBuffer[1] > 200)
            {
                rx_num = 0; // rec err
                m_readBuffer[0] = 0;
                m_readBuffer[1] = 0;
                m_readBuffer[7] = 0;
            }
        }
        else
        {
            rx_num = 0;
            m_readBuffer.clear();
        }
    }

    if (rx_f & 1)
    {
        rx_f=0;
        uint8_t sum = 0x00;
        for (int i = 0; i < rx_num; i++)
        {
            sum += m_readBuffer[i];
        }
        if (sum == m_readBuffer[rx_num])
        {
            ret.cmd = m_readBuffer[3];
            if((0x04==ret.cmd)&&(0x00!= m_readBuffer[5])&&(m_readBuffer[5]<16))
            {
                for(int i=0;i<m_readBuffer[1];i++)
                {
                    ret.data.push_back(m_readBuffer[i]);
                }
            }
            else
            {
                ret.cmd = 0;
            }
        }
        rx_num = 0;
        m_readBuffer.clear();
    }

    return ret;
}







