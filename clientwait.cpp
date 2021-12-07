#include "clientwait.h"
#include "ui_clientwait.h"
#include <QHostAddress>
#include <QDebug>

ClientWait::ClientWait(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientWait)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowTitle("waiting for input!");

    //初始化
    myTcpSocket = new QTcpSocket(0);
    myWhiteBoard = nullptr;
    myReceiveOption = nullptr;

    //绑定TCP地址与端口,QTcpSocket不支持bind,不知道为什么
    // if(myTcpSocket->bind(QHostAddress::LocalHost))
    // {
        // qDebug()<<"绑定成功";
        // qDebug()<<"IP:"<<myTcpSocket->localAddress().toString();
        // qDebug()<<"Port:"<<myTcpSocket->localPort();
    // }
    // else{
        // qDebug()<<"绑定失败";
        // qDebug()<<myTcpSocket->errorString();
        // }

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
    serverPort = ui->portInput->text().toInt();
    qDebug()<<"ok is clicked";
    qDebug()<<"serverIP:"<<serverIP<<"serverPort:"<<serverPort;
    myTcpSocket->connectToHost(serverIP,serverPort);
    //等待10s,直到建立连接
    if(myTcpSocket->waitForConnected(10000)){
        qDebug()<<"connect successful!";
        qDebug()<<"my port:"<<myTcpSocket->localPort();
        connect(myTcpSocket,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(displayError(QAbstractSocket::SocketError)));
        myWhiteBoard = new WhiteBoard(0,myTcpSocket);
        myReceiveOption = new ReceiveOption(0,myTcpSocket,myWhiteBoard);
        myWhiteBoard->setWindowIcon(QIcon(":/png/images/1.png"));
        myWhiteBoard->show();
        this->hide();
    }
    else{
        qDebug()<<"connect wrong:"<<myTcpSocket->errorString();
    }
}

void ClientWait::displayError(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError)
    qDebug()<<myTcpSocket->errorString();
    myTcpSocket->close();
    myWhiteBoard->close();
    this->close();
}
ClientWait::~ClientWait()
{
    delete ui;
}
