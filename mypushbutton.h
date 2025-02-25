#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyPushButton(QWidget *parent = nullptr);
    //构造函数 参数1：正常显示的按钮图片  参数2：按下按键时显示的图片
    MyPushButton(QString normalImg,QString pressImg = "");//给一个默认值是由于有些按键不会按下时切换图片，方便封装在一起
    //成员属性 保存正常和按下时图片路径
    QString normalImgPath;
    QString pressImgPath;
    //按钮跳跃
    void zoom1();//向下跳
    void zoom2();//向上跳

    //重写鼠标点击事件
    void mousePressEvent(QMouseEvent *e);
    //重写鼠标释放事件
    void mouseReleaseEvent(QMouseEvent *e);
signals:
};

#endif // MYPUSHBUTTON_H
