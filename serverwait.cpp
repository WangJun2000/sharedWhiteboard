#include "serverwait.h"
#include "ui_serverwait.h"

ServerWait::ServerWait(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerWait)
{
    ui->setupUi(this);
    this->setWindowTitle("listening");
    //初始化

    //监听在某一个端口
    // if(!myTcpSocket->listen(QHostAddress::LocalHost,10085)){
        // qDebug()<<myTcpSocket->errorString();
        // close();
        // return;
    //     }
    //信号与槽
    //返回按钮
    connect(ui->backButton,&QPushButton::clicked,[=](){
       emit backSignal();
    });
}

ServerWait::~ServerWait()
{
    delete ui;
}
