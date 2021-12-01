#include "mainwidget.h"
#include "ui_mainwidget.h"

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MainWidget)
{
    ui->setupUi(this);
    this->setWindowTitle("model selection");
    this->setAttribute(Qt::WA_DeleteOnClose,false);

    //初始化

    //信号与槽的连接
    connect(ui->serverButton,&QPushButton::clicked,this,&MainWidget::serverButtonClicked);
    connect(ui->clientButton,&QPushButton::clicked,this,&MainWidget::clientButtonClicked);

    //

}

void MainWidget::serverButtonClicked(){
    this->hide();

    if (serverWaitWidget != NULL)
        delete serverWaitWidget;

    serverWaitWidget = new ServerWait(0);

    //返回到主窗口
    connect(serverWaitWidget,&ServerWait::backSignal,[=](){
       serverWaitWidget->close();
       this->show();
    });

    serverWaitWidget->show();
}

void MainWidget::clientButtonClicked(){
    this->hide();

    if (clientWaitWidget != NULL)
        delete clientWaitWidget;
    clientWaitWidget = new ClientWait(0);

     //返回到主窗口
    connect(clientWaitWidget,&ClientWait::backSignal,[=](){
       clientWaitWidget->close();
       this->show();
    });


    clientWaitWidget->show();
}

MainWidget::~MainWidget()
{
    delete ui;
}

