#ifndef SENDTIMER_H
#define SENDTIMER_H

#include <QObject>
#include <QTimer>
#include <QTcpSocket>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonDocument>

class SendTimer : public QObject
{
    Q_OBJECT
public:
    explicit SendTimer(QObject *parent, QTcpSocket *myTcpSocket, quint16 interval);
    QJsonObject sendJsonObject;

signals:

private:
    QTimer *myTimer;
    QTcpSocket *myTcpSocket;
    quint16 interval;

private slots:
    void sendJson();
};

#endif // SENDTIMER_H
