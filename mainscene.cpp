#include "mainscene.h"
#include "ui_mainscene.h"
#include<QPainter>
#include "mypushbutton.h"
#include<QTimer>
#include<QSoundEffect>
MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);
    //配置主场景
    setWindowIcon(QIcon(":/res/Coin001.png"));
    setWindowTitle("翻金币主场景");
    setFixedSize(320,588);
    //实现退出
    connect(ui->actionquit,&QAction::triggered,[=](){
        this->close();
    });
    //创建开始按钮音效
    QSoundEffect *startsound = new QSoundEffect(this);
    startsound->setSource(QUrl::fromLocalFile(":/res/TapButtonSound.wav"));

    //开始按钮
    MyPushButton *startbtn = new MyPushButton(":/res/MenuSceneStartButton.png");
    startbtn->setParent(this);
    //按钮放在正下方
    startbtn->move(this->width()*0.5-startbtn->width()*0.5,this->height()*0.7);
    //实例化关卡选择对象
    chooselevel =  new ChooseLevelScene;

    //监听选择关卡的返回按钮信号
    connect(chooselevel,&ChooseLevelScene::choosesceneBack,this,[=](){
        //设置场景的初始位置
        this->setGeometry(chooselevel->geometry());
        chooselevel->hide();//隐藏关卡选择场景
        this->show();//显示主场景
    });
    connect(startbtn,&MyPushButton::clicked,this,[=](){
        startbtn->zoom1();
        startsound->play();
        startbtn->zoom2();
        //延迟一段时间，方便显示开始按钮跳跃动画
        QTimer::singleShot(500,this,[=](){
            //优化 防止窗口位置变动
            chooselevel->setGeometry(this->geometry());
            //隐藏当前场景
            this->hide();
            //显示关卡选择场景
            chooselevel->show();


        });


    });
}
void MainScene::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix);

}

MainScene::~MainScene()
{
    delete ui;
}
