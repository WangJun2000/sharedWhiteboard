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
        QJsonValueRef msgArrayRef = sendJsonObject.find("msg").value();
        QJsonArray msgArray = msgArrayRef.toArray();
        msgArray.append(msg);
        msgArrayRef = msgArray;

    }
    else{
        QJsonArray msgArray;
        msgArray.append(msg);
        sendJsonObject.insert("msg",msgArray);
    }

}

void SendTimer::sendLines(bool isNewLine,double x, double y){
    if (sendJsonObject.contains("draw")){
        //使用引用,才能呢个修改本来的值
        QJsonValueRef drawRef = sendJsonObject.find("draw").value();
        QJsonObject draw = drawRef.toObject();
        if(draw.contains("lines")){
            QJsonValueRef linesRef = draw.find("lines").value();
            QJsonArray lines = linesRef.toArray();
            QJsonObject point;
            point.insert("isNewLine",isNewLine);
            point.insert("x",x);
            point.insert("y",y);
            lines.append(point);
            linesRef = lines;
        }
        else{
            QJsonArray lines;
            QJsonObject point;
            point.insert("isNewLine",isNewLine);
            point.insert("x",x);
            point.insert("y",y);
            lines.append(point);
            draw.insert("lines",lines);
        }
        drawRef = draw;
    }
    else{
        QJsonObject draw;
        QJsonArray lines;
        QJsonObject point;
        point.insert("isNewLine",isNewLine);
        point.insert("x",x);
        point.insert("y",y);
        lines.append(point);
        draw.insert("lines",lines);
        sendJsonObject.insert("draw",draw);
    }
}

void SendTimer::sendLines(bool isEraser, bool isNewLine,double x, double y,int color,int size){
    if (sendJsonObject.contains("draw")){
        //使用引用,才能呢个修改本来的值
        QJsonValueRef drawRef = sendJsonObject.find("draw").value();
        QJsonObject draw = drawRef.toObject();
        if(draw.contains("lines")){
            QJsonValueRef linesRef = draw.find("lines").value();
            QJsonArray lines = linesRef.toArray();
            QJsonObject point;
            point.insert("isNewLine",isNewLine);
            point.insert("x",x);
            point.insert("y",y);
            point.insert("isEraser",isEraser);
            point.insert("color",color);
            point.insert("size",size);
            lines.append(point);
            linesRef = lines;
        }
        else{
            QJsonArray lines;
            QJsonObject point;
            point.insert("isNewLine",isNewLine);
            point.insert("x",x);
            point.insert("y",y);
            point.insert("isEraser",isEraser);
            point.insert("color",color);
            point.insert("size",size);
            lines.append(point);
            draw.insert("lines",lines);
        }
        drawRef = draw;
    }
    else{
        QJsonObject draw;
        QJsonArray lines;
        QJsonObject point;
        point.insert("isNewLine",isNewLine);
        point.insert("x",x);
        point.insert("y",y);
        point.insert("isEraser",isEraser);
        point.insert("color",color);
        point.insert("size",size);
        lines.append(point);
        draw.insert("lines",lines);
        sendJsonObject.insert("draw",draw);
    }
}

void SendTimer::sendRects(bool isNewRect,double x, double y){
    if (sendJsonObject.contains("draw")){
        //使用引用,才能呢个修改本来的值
        QJsonValueRef drawRef = sendJsonObject.find("draw").value();
        QJsonObject draw = drawRef.toObject();
        if(draw.contains("rects")){
            QJsonValueRef rectsRef = draw.find("rects").value();
            QJsonArray rects = rectsRef.toArray();
            QJsonObject point;
            point.insert("isNewRect",isNewRect);
            point.insert("x",x);
            point.insert("y",y);
            rects.append(point);
            rectsRef = rects;
        }
        else{
            QJsonArray rects;
            QJsonObject point;
            point.insert("isNewRect",isNewRect);
            point.insert("x",x);
            point.insert("y",y);
            rects.append(point);
            draw.insert("rects",rects);
        }
        drawRef = draw;
    }
    else{
        QJsonObject draw;
        QJsonArray rects;
        QJsonObject point;
        point.insert("isNewRect",isNewRect);
        point.insert("x",x);
        point.insert("y",y);
        rects.append(point);
        draw.insert("rects",rects);
        sendJsonObject.insert("draw",draw);
    }
}

void SendTimer::sendRects(bool isNewRect,double x, double y, int color, int size){
    if (sendJsonObject.contains("draw")){
        //使用引用,才能呢个修改本来的值
        QJsonValueRef drawRef = sendJsonObject.find("draw").value();
        QJsonObject draw = drawRef.toObject();
        if(draw.contains("rects")){
            QJsonValueRef rectsRef = draw.find("rects").value();
            QJsonArray rects = rectsRef.toArray();
            QJsonObject point;
            point.insert("isNewRect",isNewRect);
            point.insert("x",x);
            point.insert("y",y);
            point.insert("color",color);
            point.insert("size",size);
            rects.append(point);
            rectsRef = rects;
        }
        else{
            QJsonArray rects;
            QJsonObject point;
            point.insert("isNewRect",isNewRect);
            point.insert("x",x);
            point.insert("y",y);
            point.insert("color",color);
            point.insert("size",size);
            rects.append(point);
            draw.insert("rects",rects);
        }
        drawRef = draw;
    }
    else{
        QJsonObject draw;
        QJsonArray rects;
        QJsonObject point;
        point.insert("isNewRect",isNewRect);
        point.insert("x",x);
        point.insert("y",y);
        point.insert("color",color);
        point.insert("size",size);
        rects.append(point);
        draw.insert("rects",rects);
        sendJsonObject.insert("draw",draw);
    }
}

void SendTimer::sendEllipse(bool isNewEllipse,double x, double y){
    if (sendJsonObject.contains("draw")){
        //使用引用,才能呢个修改本来的值
        QJsonValueRef drawRef = sendJsonObject.find("draw").value();
        QJsonObject draw = drawRef.toObject();
        if(draw.contains("ellipse")){
            QJsonValueRef ellipseRef = draw.find("ellipse").value();
            QJsonArray ellipse = ellipseRef.toArray();
            QJsonObject point;
            point.insert("isNewEllipse",isNewEllipse);
            point.insert("x",x);
            point.insert("y",y);
            ellipse.append(point);
            ellipseRef = ellipse;
        }
        else{
            QJsonArray ellipse;
            QJsonObject point;
            point.insert("isNewEllipse",isNewEllipse);
            point.insert("x",x);
            point.insert("y",y);
            ellipse.append(point);
            draw.insert("ellipse",ellipse);
        }
        drawRef = draw;
    }
    else{
        QJsonObject draw;
        QJsonArray ellipse;
        QJsonObject point;
        point.insert("isNewEllipse",isNewEllipse);
        point.insert("x",x);
        point.insert("y",y);
        ellipse.append(point);
        draw.insert("ellipse",ellipse);
        sendJsonObject.insert("draw",draw);
    }
}

void SendTimer::sendEllipse(bool isNewEllipse,double x, double y,int color, int size){
    if (sendJsonObject.contains("draw")){
        //使用引用,才能呢个修改本来的值
        QJsonValueRef drawRef = sendJsonObject.find("draw").value();
        QJsonObject draw = drawRef.toObject();
        if(draw.contains("ellipse")){
            QJsonValueRef ellipseRef = draw.find("ellipse").value();
            QJsonArray ellipse = ellipseRef.toArray();
            QJsonObject point;
            point.insert("isNewEllipse",isNewEllipse);
            point.insert("x",x);
            point.insert("y",y);
            point.insert("color",color);
            point.insert("size",size);
            ellipse.append(point);
            ellipseRef = ellipse;
        }
        else{
            QJsonArray ellipse;
            QJsonObject point;
            point.insert("isNewEllipse",isNewEllipse);
            point.insert("x",x);
            point.insert("y",y);
            point.insert("color",color);
            point.insert("size",size);
            ellipse.append(point);
            draw.insert("ellipse",ellipse);
        }
        drawRef = draw;
    }
    else{
        QJsonObject draw;
        QJsonArray ellipse;
        QJsonObject point;
        point.insert("isNewEllipse",isNewEllipse);
        point.insert("x",x);
        point.insert("y",y);
        point.insert("color",color);
        point.insert("size",size);
        ellipse.append(point);
        draw.insert("ellipse",ellipse);
        sendJsonObject.insert("draw",draw);
    }
}

void SendTimer::sendLine(bool isNewLine, double x, double y){
    if (sendJsonObject.contains("draw")){
        //使用引用,才能呢个修改本来的值
        QJsonValueRef drawRef = sendJsonObject.find("draw").value();
        QJsonObject draw = drawRef.toObject();
        if(draw.contains("line")){
            QJsonValueRef lineRef = draw.find("line").value();
            QJsonArray line = lineRef.toArray();
            QJsonObject point;
            point.insert("isNewLine",isNewLine);
            point.insert("x",x);
            point.insert("y",y);
            line.append(point);
            lineRef = line;
        }
        else{
            QJsonArray line;
            QJsonObject point;
            point.insert("isNewLine",isNewLine);
            point.insert("x",x);
            point.insert("y",y);
            line.append(point);
            draw.insert("line",line);
        }
        drawRef = draw;
    }
    else{
        QJsonObject draw;
        QJsonArray line;
        QJsonObject point;
        point.insert("isNewLine",isNewLine);
        point.insert("x",x);
        point.insert("y",y);
        line.append(point);
        draw.insert("line",line);
        sendJsonObject.insert("draw",draw);
    }
}

void SendTimer::sendLine(bool isNewLine, double x, double y, int color, int size){
    if (sendJsonObject.contains("draw")){
        //使用引用,才能呢个修改本来的值
        QJsonValueRef drawRef = sendJsonObject.find("draw").value();
        QJsonObject draw = drawRef.toObject();
        if(draw.contains("line")){
            QJsonValueRef lineRef = draw.find("line").value();
            QJsonArray line = lineRef.toArray();
            QJsonObject point;
            point.insert("isNewLine",isNewLine);
            point.insert("x",x);
            point.insert("y",y);
            point.insert("color",color);
            point.insert("size",size);
            line.append(point);
            lineRef = line;
        }
        else{
            QJsonArray line;
            QJsonObject point;
            point.insert("isNewLine",isNewLine);
            point.insert("x",x);
            point.insert("y",y);
            point.insert("color",color);
            point.insert("size",size);
            line.append(point);
            draw.insert("line",line);
        }
        drawRef = draw;
    }
    else{
        QJsonObject draw;
        QJsonArray line;
        QJsonObject point;
        point.insert("isNewLine",isNewLine);
        point.insert("x",x);
        point.insert("y",y);
        point.insert("color",color);
        point.insert("size",size);
        line.append(point);
        draw.insert("line",line);
        sendJsonObject.insert("draw",draw);
    }
}

void SendTimer::sendText(bool isNewText, double x, double y, QString text){
    if (sendJsonObject.contains("draw")){
        //使用引用,才能呢个修改本来的值
        QJsonValueRef drawRef = sendJsonObject.find("draw").value();
        QJsonObject draw = drawRef.toObject();
        if(draw.contains("text")){
            QJsonValueRef textRef = draw.find("text").value();
            QJsonArray textArray = textRef.toArray();
            QJsonObject point;
            point.insert("isNewText",isNewText);
            point.insert("x",x);
            point.insert("y",y);
            point.insert("text",text);
            textArray.append(point);
            textRef = textArray;
        }
        else{
            QJsonArray textArray;
            QJsonObject point;
            point.insert("isNewText",isNewText);
            point.insert("x",x);
            point.insert("y",y);
            point.insert("text",text);
            textArray.append(point);
            draw.insert("text",textArray);
        }
        drawRef = draw;
    }
    else{
        QJsonObject draw;
        QJsonArray textArray;
        QJsonObject point;
        point.insert("isNewText",isNewText);
        point.insert("x",x);
        point.insert("y",y);
        point.insert("text",text);
        textArray.append(point);
        draw.insert("text",textArray);
        sendJsonObject.insert("draw",draw);
    }
}

void SendTimer::sendText(bool isNewText, double x, double y, QString text, int color, int size){
    if (sendJsonObject.contains("draw")){
        //使用引用,才能呢个修改本来的值
        QJsonValueRef drawRef = sendJsonObject.find("draw").value();
        QJsonObject draw = drawRef.toObject();
        if(draw.contains("text")){
            QJsonValueRef textRef = draw.find("text").value();
            QJsonArray textArray = textRef.toArray();
            QJsonObject point;
            point.insert("isNewText",isNewText);
            point.insert("x",x);
            point.insert("y",y);
            point.insert("color",color);
            point.insert("size",size);
            point.insert("text",text);
            textArray.append(point);
            textRef = textArray;
        }
        else{
            QJsonArray textArray;
            QJsonObject point;
            point.insert("isNewText",isNewText);
            point.insert("x",x);
            point.insert("y",y);
            point.insert("color",color);
            point.insert("size",size);
            point.insert("text",text);
            textArray.append(point);
            draw.insert("text",textArray);
        }
        drawRef = draw;
    }
    else{
        QJsonObject draw;
        QJsonArray textArray;
        QJsonObject point;
        point.insert("isNewText",isNewText);
        point.insert("x",x);
        point.insert("y",y);
        point.insert("color",color);
        point.insert("size",size);
        point.insert("text",text);
        textArray.append(point);
        draw.insert("text",textArray);
        sendJsonObject.insert("draw",draw);
    }
}

void SendTimer::sendUndo(){
    if(sendJsonObject.contains("undo")){
        QJsonValueRef undoRef = sendJsonObject.find("undo").value();
        int undo = undoRef.toInt();
        undo++;
        undoRef = undo;
    }
    else{
        sendJsonObject.insert("undo",(int)1);
    }
}

void SendTimer::sendMove(int type, double dx, double dy){
    if(sendJsonObject.contains("move")){
        QJsonValueRef moveRef = sendJsonObject.find("move").value();
        QJsonArray moveArray = moveRef.toArray();
        QJsonObject moveOption;
        moveOption.insert("type",type);
        moveOption.insert("dx",dx);
        moveOption.insert("dy",dy);
        moveArray.append(moveOption);
        moveRef = moveArray;
    }
    else{
        QJsonArray moveArray;
        QJsonObject moveOption;
        moveOption.insert("type",type);
        moveOption.insert("dx",dx);
        moveOption.insert("dy",dy);
        moveArray.append(moveOption);
        sendJsonObject.insert("move",moveArray);
    }
}

void SendTimer::sendPic(QString pic){
    if(sendJsonObject.contains("pic")){
        QJsonValueRef picRef = sendJsonObject.find("pic").value();
        QJsonArray picArray = picRef.toArray();
        picArray.append(pic);
        picRef = picArray;
    }
    else{
        QJsonArray picArray;
        picArray.append(pic);
        sendJsonObject.insert("pic",picArray);
    }
}

void SendTimer::sendJson(){
    //判断TCP连接状态
    if(myTcpSocket->state() == QAbstractSocket::ConnectedState){
        // qDebug()<<"定时器tick";
        //判断json对象是否是空的
        if(!sendJsonObject.isEmpty()){
            //打印一下
            // qDebug()<<sendJsonObject;

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
