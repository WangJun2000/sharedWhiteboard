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

void SendTimer::sendMsg(QString msg){
    if (sendJsonObject.contains("msg")){
        sendJsonObject.value("msg").toArray().append(msg);
    }
    else{
        QJsonArray msgArray;
        msgArray.append(msg);
        sendJsonObject.insert("msg",msgArray);
    }

}

void SendTimer::sendJson(){
    //判断TCP连接状态
    if(myTcpSocket->state() == QAbstractSocket::ConnectedState){
        // qDebug()<<"定时器tick";
        //判断json对象是否是空的
        if(!sendJsonObject.isEmpty()){
            //打印一下
            qDebug()<<sendJsonObject;

            QJsonDocument doc(sendJsonObject);
            QByteArray json = doc.toJson();
            qint64 jsonLength = json.length() + sizeof(qint64);

            //datastream发送的载体
            QByteArray outBlock;
            QDataStream sendout(&outBlock,QIODevice::WriteOnly);
            sendout.setVersion(QDataStream::Qt_5_15);
            sendout<<jsonLength;
            qDebug()<<"发送数据长度"<<jsonLength;
            //长度
            myTcpSocket->write(outBlock);

            //本体
            myTcpSocket->write(json);


            //清空json
            sendJsonObject = QJsonObject();
        }
    }
    else{
        qDebug()<<"TCP未处在连接状态";
    }
}
