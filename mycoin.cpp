#include "mycoin.h"

// MyCoin::MyCoin(QWidget *parent)
//     : QPushButton{parent}
// {}
MyCoin::MyCoin(QString btnImg){
    QPixmap pix;
    bool ret = pix.load(btnImg);
    if(!ret){
        QString str = QString("图片 %1加载失败").arg(btnImg);
        qDebug()<<str;
        return;
    }
    setFixedSize(pix.width(),pix.height());
    setStyleSheet("QPushButton{border:0px}");
    setIcon(QIcon(pix));
    setIconSize(QSize(pix.width(),pix.height()));
    timer1 = new QTimer(this);
    timer2 = new QTimer(this);

    //监听正面翻反面信号，并且翻转金币
    connect(timer1,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str  = QString(":/res/Coin000%1.png").arg(this->min++);
        pix.load(str);

        setFixedSize(pix.width(),pix.height());
        setStyleSheet("QPushButton{border:0px}");
        setIcon(QIcon(pix));
        setIconSize(QSize(pix.width(),pix.height()));
        //判断翻完了
        if(this->min > this->max){
            isAnimation = false;
            timer1->stop();
            this->min = 1;
        }
    });

    //监听反面翻正面信号，并且翻转金币
    connect(timer2,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str  = QString(":/res/Coin000%8.png").arg(this->max--);
        pix.load(str);

        setFixedSize(pix.width(),pix.height());
        setStyleSheet("QPushButton{border:0px}");
        setIcon(QIcon(pix));
        setIconSize(QSize(pix.width(),pix.height()));
        //判断翻完了
        if(this->max <this->min){
            isAnimation = false;
            timer2->stop();
            this->max = 8;
        }
    });
}

void MyCoin::changeFlag(){
    if(this->flag){
        this->flag = false;
        timer1->start(30);
        isAnimation = true;
    }
    else{
        this->flag = true;
        timer2->start(30);
        isAnimation = true;
    }
}
void MyCoin::mousePressEvent(QMouseEvent *event){
    if(this->isAnimation || this->isWin){
        return;
    }
    else{
        return QPushButton::mousePressEvent(event);
    }
}
