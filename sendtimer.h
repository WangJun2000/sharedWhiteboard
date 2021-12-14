#ifndef SENDTIMER_H
#define SENDTIMER_H

#include <QObject>
#include <QTimer>
#include <QTcpSocket>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonDocument>
#include <QByteArray>
#include <QDataStream>
#include <QPoint>

class SendTimer : public QObject
{
    Q_OBJECT
public:
    explicit SendTimer(QObject *parent, QTcpSocket *myTcpSocket, quint16 interval);
    QJsonObject sendJsonObject;

    void sendMsg(QString msg);
    void sendLines(bool isNewLine,double x, double y);
    void sendLines(bool isEraser, bool isNewLine, double x, double y, int color, int size);
    void sendRects(bool isNewRect,double x, double y);
    void sendRects(bool isNewRect,double x, double y, int color, int size);
    void sendEllipse(bool isNewEllipse, double x,double y);
    void sendEllipse(bool isNewEllipse, double x,double y, int color, int size);
    void sendLine(bool isNewLine, double x,double y);
    void sendLine(bool isNewLine, double x,double y, int color, int size);
    void sendText(bool isNewText, double x, double y, QString text);
    void sendText(bool isNewText, double x, double y, QString text, int color, int size);
    void sendUndo();
    void sendMove(int type, double dx, double dy);
    void sendPic(QString pic);


signals:

private:
    QTimer *myTimer;
    QTcpSocket *myTcpSocket;
    quint16 interval;

private slots:
    void sendJson();
};

#endif // SENDTIMER_H
