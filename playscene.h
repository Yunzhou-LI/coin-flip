#ifndef PLAYSCENE_H
#define PLAYSCENE_H
#include<mycoin.h>
#include <QMainWindow>
#include<mypushbutton.h>
class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    //explicit PlayScene(QWidget *parent = nullptr);

    PlayScene(int levelNum);
    int levelindex;//记录所选关卡
    void paintEvent(QPaintEvent *event);
    int gameArray[4][4];//二维数组，维护每一关的关卡数据
    MyCoin *coinBtn[4][4];//二维数组指针，维护每一个金币
    //判断胜利的标志
    bool isWin;
signals:
    void choosesceneBack();
};

#endif // PLAYSCENE_H
