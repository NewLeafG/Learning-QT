#ifndef MSG_PROCESSER_H
#define MSG_PROCESSER_H

#include <QtCore>

typedef struct msgData
{
    int cmd;
    QByteArray data[];
};


class msg_processer
{
public:
    msg_processer();

    QByteArray pack_Get(); 
    QByteArray pack_Set(); 
    QByteArray pack_GetDevSnapshot(); 


};

#endif // MSG_PROCESSER_H
