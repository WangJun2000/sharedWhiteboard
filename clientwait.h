#ifndef CLIENTWAIT_H
#define CLIENTWAIT_H

#include <QWidget>
#include <QString>
#include "mytcpsocket.h"

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
    MyTcpSocket *myTcpSocket;
    QString serverIP;
    QString serverPort;
    void okButtonClicked();
};

#endif // CLIENTWAIT_H
