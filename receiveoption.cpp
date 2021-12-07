#include "receiveoption.h"

ReceiveOption::ReceiveOption(QObject *parent, QTcpSocket *_myTcpSocket, WhiteBoard *_myWhiteBoard) : QObject(parent)
{

    //初始化
    myTcpSocket = _myTcpSocket;
    myWhiteBoard = _myWhiteBoard;
    bytesReceived = 0;
    totalBytes = 0;

    connect(myTcpSocket,&QTcpSocket::readyRead,this,&ReceiveOption::readJson);

}

void ReceiveOption::readJson()
{
    QDataStream in(myTcpSocket);
    in.setVersion(QDataStream::Qt_5_15);

    //如果接收到的数据小于8个字节,保留到来的json大小
    if (bytesReceived == 0){
        if(myTcpSocket->bytesAvailable() >= sizeof (qint64)){
            in>>totalBytes;
            qDebug()<<"接收json长度"<<totalBytes;
            bytesReceived += sizeof(qint64);
        }
        else
            return;
    }

    if (bytesReceived < totalBytes){
        bytesReceived += myTcpSocket->bytesAvailable();
        receiveJsonByteArray += myTcpSocket->readAll();
    }

    //接收数据完成时
    if ((bytesReceived == totalBytes) && (bytesReceived != 0)){
        bytesReceived = 0;
        totalBytes = 0;

        QJsonParseError jsonError;
        myJsonDoc = QJsonDocument::fromJson(receiveJsonByteArray,&jsonError);
        if (myJsonDoc.isObject() && jsonError.error == QJsonParseError::NoError){
            myJsonObject = myJsonDoc.object();
            //test
            // QStringList keys = myJsonObject.keys();
            // for(int i=0; i<keys.size(); ++i)
            // {
                // QString key = keys.at(i);
                // QJsonValue value = myJsonObject.value(key);
                // if(value.isBool())
                // {
                // qDebug() << key << ":" << value.toBool();
                // }
                // if(value.isString())
                // {
                // qDebug() << key << ":" << value.toString();
                // }
                // if(value.isDouble())
                // {
                // qDebug() << key << ":" << value.toInt();
                // }
            //             }
            handleJson(myJsonObject);
            //清空缓存
            myJsonObject = QJsonObject();
            receiveJsonByteArray.clear();
        }
        else{
            qDebug()<<"接收到错误类型数据";
            qDebug()<<jsonError.errorString();
            qDebug()<<receiveJsonByteArray;
        }
    }
}

void ReceiveOption::handleJson(QJsonObject comeJson){
    if (comeJson.contains("msg")){
        QJsonArray msgArray = comeJson.value("msg").toArray();

        for (int i=0; i<msgArray.size(); i++){
            myWhiteBoard->msgBrowserAppend(false,msgArray[i].toString());
        }
    }
}
