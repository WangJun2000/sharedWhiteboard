#include "serverwait.h"
#include "ui_serverwait.h"
#include <QMessageBox>
#include <QNetworkInterface>

ServerWait::ServerWait(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerWait)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowTitle("listening");
    //初始化
    myTcpServer = new QTcpServer(0);
    myTcpServerConnection = nullptr;
    myWhiteBoard = nullptr;
    myReceiveOption = nullptr;
    //监听在某一个端口
    if(!myTcpServer->listen(QHostAddress::AnyIPv4)){
        qDebug()<<myTcpServer->errorString();
        QMessageBox::information(this,"listen wrong!",myTcpServer->errorString());
    }
    else{
        qDebug()<<"start listening!";
        qDebug()<<"IP:"<<myTcpServer->serverAddress()<<"Port:"<<myTcpServer->serverPort();
        qDebug()<<"IP"<<getHostIpAddress();
        ui->ipLabel->setText(ui->ipLabel->text()+getHostIpAddress());
        ui->portLabel->setText(ui->portLabel->text()+QString::number(myTcpServer->serverPort()));
    }
    //信号与槽
    //返回按钮
    connect(ui->backButton,&QPushButton::clicked,[=](){
       emit backSignal();
    });
    //有建立连接的请求到来
    connect(myTcpServer,&QTcpServer::newConnection,this,&ServerWait::handleNewConnection);
}

QString ServerWait::getHostIpAddress()
{
    QString strIpAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // 获取第一个本主机的IPv4地址
    int nListSize = ipAddressesList.size();
    for (int i = 0; i < nListSize; ++i)
    {
           if (ipAddressesList.at(i).toIPv4Address()) {
               strIpAddress += ipAddressesList.at(i).toString();
               strIpAddress += " ";
           }
     }
     // 如果没有找到，则以本地IP地址为IP
     if (strIpAddress.isEmpty())
        strIpAddress = QHostAddress(QHostAddress::LocalHost).toString();
     return strIpAddress;
}


void ServerWait::handleNewConnection()
{
    myTcpServerConnection =myTcpServer->nextPendingConnection();
    myWhiteBoard = new WhiteBoard(0,myTcpServerConnection);
    myReceiveOption = new ReceiveOption(0,myTcpServerConnection,myWhiteBoard);
    myWhiteBoard->setWindowIcon(QIcon(":/png/images/1.png"));
    this->hide();
    //如果发生错误,就打印出来
    connect(myTcpServerConnection,SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(displayError(QAbstractSocket::SocketError)));
    myWhiteBoard->show();
    myTcpServer->close();
    qDebug()<<"tcpServer close";
}

void ServerWait::displayError(QAbstractSocket::SocketError socketError)
{
    Q_UNUSED(socketError)
    qDebug()<<myTcpServerConnection->errorString();
    myTcpServerConnection->close();
    myWhiteBoard->close();
    this->close();
}

ServerWait::~ServerWait()
{
    if(myTcpServer->isListening())
    {
        myTcpServer->close();
        qDebug()<<"tcpServer close";
    }
        delete ui;
}
