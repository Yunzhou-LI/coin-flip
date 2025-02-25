#ifndef MYCOIN_H
#define MYCOIN_H
#include<QTimer>
#include <QWidget>
#include<QPushButton>
class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyCoin(QWidget *parent = nullptr);
    MyCoin(QString btnImg);

    //设置金币属性
    int posX;//x坐标
    int posY;//y坐标
    bool flag;//正反面标志 1正0反

    //改变标志的方法
    void changeFlag();
    QTimer *timer1;//正面翻反面定时器
    QTimer *timer2;//反面翻正面定时器
    int min = 1;
    int max = 8;
    bool isAnimation = false;//是否正在执行动画标志
    bool isWin = false;//是否已经胜利标识
    void mousePressEvent(QMouseEvent *event);
signals:
};

#endif // MYCOIN_H
