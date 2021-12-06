#ifndef CLIENTWAIT_H
#define CLIENTWAIT_H

#include <QWidget>
#include <QString>
#include <QTcpSocket>

#include "whiteboard.h"

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

private slots:
    void okButtonClicked();
    void displayError(QAbstractSocket::SocketError socketError);
};

#endif // CLIENTWAIT_H
