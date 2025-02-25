#include "chooselevelscene.h"
#include<QMenuBar>
#include<QDebug>
#include<QPainter>
#include<QTimer>
#include<QLabel>
#include<mypushbutton.h>
#include<QSoundEffect>
ChooseLevelScene::ChooseLevelScene(QWidget *parent)
    : QMainWindow{parent}
{
    //配置关卡选择场景
    this->setFixedSize(320,588);
    //设置窗口图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置窗口标题
    this->setWindowTitle("关卡选择窗口");
    //创建菜单栏
    QMenuBar *bar = new QMenuBar();
    //设置菜单栏
    setMenuBar(bar);
    //创建开始菜单
    QMenu *startmenu = bar->addMenu("开始");
    QAction *quitmenu = startmenu->addAction("退出");
    connect(quitmenu,&QAction::triggered,this,[=](){
        this->close();
    });
    //创建选择关卡点击音效
    QSoundEffect *choosesound = new QSoundEffect(this);
    choosesound->setSource(QUrl::fromLocalFile(":/res/TapButtonSound.wav"));
    //创建返回按钮点击音效
    QSoundEffect *backsound = new QSoundEffect(this);
    backsound->setSource(QUrl::fromLocalFile(":/res/BackButtonSound.wav"));

    //返回按钮
    MyPushButton *backBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    //设置返回按钮位置
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());
    //点击返回按钮
    connect(backBtn,&MyPushButton::clicked,[=](){
        //qDebug()<<"点击了返回按钮";
        backsound->play();
        QTimer::singleShot(500,this,[=](){//延时返回，在这里点击后过0.5s再发送信号
            emit this->choosesceneBack();
        });

    });

    //创建选择关卡的按钮
    for(int i = 0;i<20;i++){
        MyPushButton *selectBtn = new MyPushButton(":/res/LevelIcon.png");
        selectBtn->setParent(this);
        selectBtn->move(i%4*70+26,i/4*70+130);

        //点击关卡按钮
        connect(selectBtn,&MyPushButton::clicked,[=](){
            choosesound->play();
            QString str = QString ("您选择的关卡是第%1关").arg(i + 1);
            qDebug()<<str;

            play = new PlayScene(i+1);
            //隐藏当前界面
            this->hide();
            //设置游戏场景的初始位置
            play->setGeometry(this->geometry());
            //显示关卡界面
            play->show();
            connect(play,&PlayScene::choosesceneBack,this,[=](){
                //设置游戏场景的初始位置
                this->setGeometry(play->geometry());
                this->show();//监听到游戏界面返回后，显示关卡选择界面
                delete play;//每一关的游戏不同，直接delete掉即可
                play = NULL;
            });

        });

        QLabel *label = new QLabel;
        label->setParent(this);
        label->setText(QString::number(i+1));
        label->move(i%4*70+25,i/4*70+130);
        label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        label->setFixedSize(selectBtn->width(),selectBtn->height());
        label->setAttribute(Qt::WA_TransparentForMouseEvents);


    }



}
void ChooseLevelScene::paintEvent(QPaintEvent *){
    //画背景图
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //画图标
    pix.load(":/res/Title.png");
    painter.drawPixmap(this->width()*0.5-pix.width()*0.5,30,pix);
}
