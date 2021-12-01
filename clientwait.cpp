#include "clientwait.h"
#include "ui_clientwait.h"
#include <QHostAddress>
#include <QDebug>

ClientWait::ClientWait(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientWait)
{
    ui->setupUi(this);
    this->setWindowTitle("waiting for input!");

    //初始化

    //绑定TCP地址与端口
    // if(myTcpSocket->bind(QHostAddress::AnyIPv4))
    // {
        // qDebug()<<"绑定成功";
        // qDebug()<<"IP:"<<myTcpSocket->localAddress().toString();
        // qDebug()<<"Port:"<<myTcpSocket->localPort();
    // }
    // else{
        // qDebug()<<"绑定失败";
        // qDebug()<<myTcpSocket->errorString();
    //     }

    //信号与槽
    //返回按钮
    connect(ui->backButton,&QPushButton::clicked,[=](){
       emit backSignal();
    });
    //确认按钮
    connect(ui->okButton,&QPushButton::clicked,this,&ClientWait::okButtonClicked);

}

void ClientWait::okButtonClicked(){
    serverIP = ui->ipInput->text();
    serverPort = ui->portInput->text();
    qDebug()<<"ok is clicked";
    qDebug()<<"serverIP:"+serverIP<<"serverPort:"+serverPort;
}

ClientWait::~ClientWait()
{
    delete ui;
}
