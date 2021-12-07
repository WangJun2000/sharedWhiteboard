#ifndef CLIENTWAIT_H
#define CLIENTWAIT_H

#include <QWidget>
#include <QString>
#include <QTcpSocket>

#include "whiteboard.h"
#include "receiveoption.h"

namespace Ui {
class ClientWait;
}

class ClientWait : public QWidget
{
    Q_OBJECT

public:
    explicit ClientWait(QWidget *parent);
    ~ClientWait();

signals:
    void backSignal();

private:
    Ui::ClientWait *ui;
    QTcpSocket *myTcpSocket;
    QString serverIP;
    int serverPort;
    WhiteBoard *myWhiteBoard;
    ReceiveOption *myReceiveOption;

private slots:
    void okButtonClicked();
    void displayError(QAbstractSocket::SocketError socketError);
};

#endif // CLIENTWAIT_H
