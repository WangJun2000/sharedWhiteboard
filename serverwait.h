#ifndef SERVERWAIT_H
#define SERVERWAIT_H

#include <QWidget>
#include <QTcpServer>
#include <QHostAddress>
#include <QString>

#include "whiteboard.h"
#include "receiveoption.h"

namespace Ui {
class ServerWait;
}

class ServerWait : public QWidget
{
    Q_OBJECT

public:
    explicit ServerWait(QWidget *parent);
    ~ServerWait();

signals:
    /**
     * 信号必须要signals关键字来声明
     * 信号没有返回值, 但可以有参数
     * 信号就是函数的声明, 无需定义
     * 使用: emit mySignal();
     * 信号可以被重载
     * 注释打全一点
     */
    void backSignal();

private:
    Ui::ServerWait *ui;
    QTcpServer *myTcpServer;
    QTcpSocket *myTcpServerConnection;
    //白板对象
    WhiteBoard *myWhiteBoard;
    ReceiveOption *myReceiveOption;

    QString getHostIpAddress();

private slots:
    void handleNewConnection();
    void displayError(QAbstractSocket::SocketError socketError);
};

#endif // SERVERWAIT_H
