#include "mainwidget.h"
#include "mytcpsocket.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWidget *w= new MainWidget(0);
    w->show();
    return a.exec();
}
