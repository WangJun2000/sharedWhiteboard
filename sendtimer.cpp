#include "sendtimer.h"
#include <QDebug>

SendTimer::SendTimer(QObject *parent, QTcpSocket *_myTcpSocket, quint16 _interval) : QObject(parent)
{
    //初始化
    myTcpSocket = _myTcpSocket;
    myTimer = new QTimer(this);
    interval = _interval;
    //启动定时器
    myTimer->start(interval);
    connect(myTimer,&QTimer::timeout,this,&SendTimer::sendJson);
}

void SendTimer::sendJson(){
    //判断TCP连接状态
    if(myTcpSocket->state() == QAbstractSocket::ConnectedState){
        qDebug()<<"定时器tick";
        //判断json对象是否是空的
        if(!sendJsonObject.isEmpty()){


            //清空json
            sendJsonObject = QJsonObject();
        }
    }
    else{
        qDebug()<<"TCP未处在连接状态";
    }
}
