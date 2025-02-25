#include "mypushbutton.h"
#include<QPixmap>
#include<QDebug>
#include<QPropertyAnimation>
// MyPushButton::MyPushButton(QWidget *parent)
//     : QPushButton{parent}
// {}
MyPushButton::MyPushButton(QString normalImg,QString pressImg){
    this->normalImgPath = normalImg;
    this->pressImgPath = pressImg;
    QPixmap pix;
    bool ret = pix.load(normalImgPath);
    if(!ret){
        qDebug()<<"图片加载失败";
        return;
    }
    //设置按钮固定大小
    this->setFixedSize(pix.width(),pix.height());
    //设置不规则样式
    this->setStyleSheet("QPushButton{border:0px}");
    //设置图标
    this->setIcon(pix);
    //设置图标大小
    this->setIconSize(QSize(pix.width(),pix.height()));

}
void MyPushButton::zoom1(){
    //创建动画对象
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry");
    //设置动画间隔时间
    animation->setDuration(200);
    //起始位置
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    //结束位置
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}
void MyPushButton::zoom2(){
    //创建动画对象
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry");
    //设置动画间隔时间
    animation->setDuration(200);
    //起始位置
    animation->setStartValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    //结束位置
    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    animation->start();
}

//重写鼠标点击事件
void MyPushButton::mousePressEvent(QMouseEvent *e){
    if(pressImgPath != ""){
        QPixmap pix;
        bool ret = pix.load(pressImgPath);
        if(!ret){
            qDebug()<<"退出时点击图片加载失败";
            return;
        }
        //设置按钮固定大小
        this->setFixedSize(pix.width(),pix.height());
        //设置不规则样式
        this->setStyleSheet("QPushButton{border:0px}");
        //设置图标
        this->setIcon(pix);
        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    //让父类去做其他的事情
    return QPushButton::mousePressEvent(e);
}
//重写鼠标释放事件
void MyPushButton::mouseReleaseEvent(QMouseEvent *e){
    if(pressImgPath != ""){
        QPixmap pix;
        bool ret = pix.load(normalImgPath);
        if(!ret){
            qDebug()<<"退出时点击后释放按钮图片加载失败";
            return;
        }
        //设置按钮固定大小
        this->setFixedSize(pix.width(),pix.height());
        //设置不规则样式
        this->setStyleSheet("QPushButton{border:0px}");
        //设置图标
        this->setIcon(pix);
        //设置图标大小
        this->setIconSize(QSize(pix.width(),pix.height()));
    }
    //让父类去做其他的事情
    return QPushButton::mouseReleaseEvent(e);
}
