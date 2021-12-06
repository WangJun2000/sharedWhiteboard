#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include "serverwait.h"
#include "clientwait.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWidget; }
QT_END_NAMESPACE

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    MainWidget(QWidget *parent);
    ~MainWidget();

private slots:
    void serverButtonClicked();
    void clientButtonClicked();


private:
    Ui::MainWidget *ui;
    //点击server按钮打开的新窗口
    ServerWait *serverWaitWidget;
    //点击client打开的窗口
    ClientWait *clientWaitWidget;
};
#endif // MAINWIDGET_H
