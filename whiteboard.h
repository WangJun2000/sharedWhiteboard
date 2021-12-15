#ifndef WHITEBOARD_H
#define WHITEBOARD_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QPainter>
#include <QVector>
#include <QPoint>
#include <QToolBar>
#include <QAction>
#include <QPalette>
#include <QColor>
#include <QMenu>
#include <QFileDialog>
#include <QTextEdit>
#include <QTextBrowser>
#include <QDateTime>
#include <QPushButton>

#include "sendtimer.h"

class WhiteBoard : public QMainWindow
{
    Q_OBJECT

public:
    explicit WhiteBoard(QWidget *parent, QTcpSocket *_myTcpSocket);
    ~WhiteBoard();

private:
    QTcpSocket *myTcpSocket;
    SendTimer *mySendTimer;
    QTextBrowser *msgBrowser;
    QTextEdit *msgEdit;
    QPushButton *sendButton;

public:
    void msgBrowserAppend(bool isLocal,QString msg);

private slots:
    void sendButtonClicked();

protected:
    void paintEvent(QPaintEvent *);//重写窗体重绘事件
    void mousePressEvent(QMouseEvent *);//重写鼠标按下事件
    void mouseReleaseEvent(QMouseEvent *);//重写鼠标释放事件
    void mouseMoveEvent(QMouseEvent *);//重写鼠标移动事件
    void contextMenuEvent(QContextMenuEvent *);//重写菜单事件
    void keyPressEvent(QKeyEvent *e); //重写按键事件
public:
private:
    int _lpress;//左键按下标志
    int _drag;//拖拽标志
    int _drawType;//描绘类型
    QMenu *_Rmenu;//右键菜单
    int _openflag;//打开图片
    QPixmap _pixmap;//画布图片
    QTextEdit *_tEdit;//文本输入框
    int _color;//绘画颜色
    int _size;//画笔粗细
public:
    QVector<QVector<QPoint> > _lines;//线条集合(一条线条可包含多个线段)
    QVector<QVector<QPoint> > _lines_remote;//线条集合(一条线条可包含多个线段)
    QVector<QRect> _rects;//矩形集合
    QVector<QRect> _rects_remote;//矩形集合
    QVector<QRect> _ellipse;//椭圆集合
    QVector<QRect> _ellipse_remote;//椭圆集合
    QVector<QRect>  _line;//直线集合
    QVector<QRect>  _line_remote;//直线集合
    QVector<QString>  _text;//文字集合
    QVector<QString>  _text_remote;//文字集合
    QVector<QPoint>  _tpoint;//文字位置集合
    QVector<QPoint>  _tpoint_remote;//文字位置集合
    QVector<int>  _shape;//图形类型集合，用于撤回功能
    QVector<int>  _shape_remote;//图形类型集合，用于撤回功能
    QPoint _begin;//鼠标按下坐标、用于最后一个图形移动
    QPoint _begin_remote;//鼠标按下坐标、用于最后一个图形移动
    QVector<int> _shape_colors;//各个图形颜色集合
    QVector<int> _shape_colors_remote;//各个图形颜色集合
    QVector<int> _shape_size;//各个图形线条粗细集合
    QVector<int> _shape_size_remote;//各个图形线条粗细集合

    const QVector<QColor> _colors={QColor(0,0,0),QColor(255,0,0),QColor(0,255,0),QColor(0,0,255),\
    QColor(255,255,0),QColor(255,0,255),QColor(0,255,255),QColor(255,255,255)};//颜色集合
    const QVector<int> _sizes={1,2,3,4,5,60};//画线粗细集合

signals:

public:
    void remoteLinesAppend(bool isEraser, bool isNewLine, double x, double y, int color, int size);
    void remoteRectsAppend(bool isNewRect, double x, double y, int color, int size);
    void remoteEllipseAppend(bool isNewEllipse, double x, double y, int color, int size);
    void remoteLineAppend(bool isNewLine, double x, double y, int color, int size);
    void remoteTextAppend(bool isNewText, double x, double y, QString text, int color, int size);
    void remoteUndo();
    void remoteMove(int type, double dx, double dy);
    void remoteOpenpic(QString pic);
    QString pixmapTostring( const QPixmap& pixmap );
    QPixmap stringTopixmap( const QString& pic );

public slots:
    void Lines();//铅笔画线
    void SavePic();//保存图片
    void Rects();//画矩形
    void Ellipses();//画椭圆
    void Line();//画直线
    void OpenPic();//打开图片
    void Texts();//文字
    void AddTexts();//添加文字
    void Erase();//橡皮擦

    void Color0();//黑色
    void Color1();//红色
    void Color2();//绿色
    void Color3();//蓝色
    void Color4();//黄色
    void Color5();//洋红色
    void Color6();//青色
    void Color7();//白色

    void Size0();
    void Size1();
    void Size2();
    void Size3();
    void Size4();
};

#endif // WHITEBOARD_H
