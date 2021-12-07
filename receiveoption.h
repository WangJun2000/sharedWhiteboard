#ifndef RECEIVEOPTION_H
#define RECEIVEOPTION_H

#include <QObject>
#include <QTcpSocket>
#include <QByteArray>
#include <QDataStream>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonDocument>
#include <QDebug>
#include "whiteboard.h"

class ReceiveOption : public QObject
{
    Q_OBJECT
public:
    explicit ReceiveOption(QObject *parent, QTcpSocket *myTcpSocket, WhiteBoard *myWhiteBoard);

signals:

private:
    QTcpSocket *myTcpSocket;
    WhiteBoard *myWhiteBoard;
    qint64 totalBytes;
    qint64 bytesReceived;

    //json对象
    QJsonDocument myJsonDoc;
    QJsonObject myJsonObject;
    QByteArray receiveJsonByteArray;

private slots:
    void readJson();
    void handleJson(QJsonObject comeJson);
};

#endif // RECEIVEOPTION_H
