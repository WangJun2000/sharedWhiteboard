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
    //短消息
    if (comeJson.contains("msg")){
        QJsonValue msg = comeJson.value("msg");
        if (msg.isArray()){
            QJsonArray msgArray = comeJson.value("msg").toArray();

            for (int i=0; i<msgArray.size(); i++){
                myWhiteBoard->msgBrowserAppend(false,msgArray[i].toString());
            }
        }
        else{
            qDebug()<<"msg不是一个QJsonArray";
        }
    }
    //绘画操作
    if (comeJson.contains("draw")){
        QJsonValue draw = comeJson.value("draw");
        if(draw.isObject()){
            QJsonObject drawObject = draw.toObject();

            //lines
            if(drawObject.contains("lines")){
                QJsonValue line = drawObject.value("lines");
                if (line.isArray()){
                    QJsonArray lineArray = line.toArray();
                    for (int i=0; i<lineArray.size(); i++){
                        QJsonObject point = lineArray[i].toObject();
                        //qDebug()<<point;
                        myWhiteBoard->remoteLinesAppend(point.value("isNewLine").toBool(),point.value("x").toDouble(),point.value("y").toDouble());

                    }
                }
                else{
                    qDebug()<<"line不是一个QJsonArray";
                }
            }
            //rects
            if(drawObject.contains("rects")){
                QJsonValue rect = drawObject.value("rects");
                if (rect.isArray()){
                    QJsonArray rectArray = rect.toArray();
                    for (int i=0; i<rectArray.size(); i++){
                        QJsonObject point = rectArray[i].toObject();
                        //qDebug()<<point;
                        myWhiteBoard->remoteRectsAppend(point.value("isNewRect").toBool(),point.value("x").toDouble(),point.value("y").toDouble());

                    }
                }
                else{
                    qDebug()<<"rect不是一个QJsonArray";
                }
            }

            //ellipse
            if(drawObject.contains("ellipse")){
                QJsonValue ellipse = drawObject.value("ellipse");
                if (ellipse.isArray()){
                    QJsonArray ellipseArray = ellipse.toArray();
                    for (int i=0; i<ellipseArray.size(); i++){
                        QJsonObject point = ellipseArray[i].toObject();
                        //qDebug()<<point;
                        myWhiteBoard->remoteEllipseAppend(point.value("isNewEllipse").toBool(),point.value("x").toDouble(),point.value("y").toDouble());

                    }
                }
                else{
                    qDebug()<<"ellipse不是一个QJsonArray";
                }
            }

            //line
            if(drawObject.contains("line")){
                QJsonValue line = drawObject.value("line");
                if (line.isArray()){
                    QJsonArray lineArray = line.toArray();
                    for (int i=0; i<lineArray.size(); i++){
                        QJsonObject point = lineArray[i].toObject();
                        //qDebug()<<point;
                        myWhiteBoard->remoteLineAppend(point.value("isNewLine").toBool(),point.value("x").toDouble(),point.value("y").toDouble());

                    }
                }
                else{
                    qDebug()<<"line不是一个QJsonArray";
                }
            }

            //text
            if(drawObject.contains("text")){
                QJsonValue text = drawObject.value("text");
                if (text.isArray()){
                    QJsonArray lineArray = text.toArray();
                    for (int i=0; i<lineArray.size(); i++){
                        QJsonObject point = lineArray[i].toObject();
                        //qDebug()<<point;
                        myWhiteBoard->remoteTextAppend(point.value("isNewText").toBool(),point.value("x").toDouble(),point.value("y").toDouble(),point.value("text").toString());

                    }
                }
                else{
                    qDebug()<<"text不是一个QJsonArray";
                }
            }
            myWhiteBoard->update();
        }
        else{
            qDebug()<<"draw不是一个QJsonObject";
        }

    }

    //撤销
    if (comeJson.contains("undo")){
        QJsonValue undoValue = comeJson.value("undo");
        int undo = undoValue.toInt();
        for(int i=0; i < undo; i++){
            myWhiteBoard->remoteUndo();
        }
    }

    //移动图形
    if (comeJson.contains("move")){
        QJsonValue move = comeJson.value("move");
        if( move.isArray()){
            QJsonArray moveArray = move.toArray();
            for (int i=0; i<moveArray.size(); i++){
                QJsonObject moveOption = moveArray[i].toObject();
                myWhiteBoard->remoteMove(moveOption.value("type").toInt(),moveOption.value("dx").toDouble(),moveOption.value("dy").toDouble());
            }
        }
        else{
            qDebug()<<"move不是一个JsonArray";
        }
    }

    //打开图片
    if (comeJson.contains("pic")){
        QJsonValue pic = comeJson.value("pic");
        if( pic.isArray()){
            QJsonArray picArray = pic.toArray();
            for (int i=0; i<picArray.size(); i++){
                QString picture = picArray[i].toString();
                myWhiteBoard->remoteOpenpic(picture);

            }
        }
        else{
            qDebug()<<"pic不是一个JsonArray";
        }
    }


}
