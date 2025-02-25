#include "playscene.h"
#include<QDebug>
#include<QMenuBar>
#include<QTimer>
#include<QPainter>
#include<QLabel>
#include<QPropertyAnimation>
#include<mycoin.h>
#include<dataconfig.h>
#include<QSoundEffect>
// PlayScene::PlayScene(QWidget *parent)
//     : QMainWindow{parent}
// {}
PlayScene::PlayScene(int levelNum){
    QString str = QString("进入了第%1关").arg(levelNum);
    QString str1 = QString("翻金币游戏-第%1关").arg(levelNum);
    qDebug()<<str;
    this->levelindex = levelNum;

    //设置窗口
    this->setFixedSize(320,588);
    //设置小图标
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    //设置标题
    this->setWindowTitle(str1);

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

    //创建返回按钮音效
    QSoundEffect *backsound = new QSoundEffect(this);
    backsound->setSource(QUrl::fromLocalFile(":/res/BackButtonSound.wav"));
    //创建翻金币音效
    QSoundEffect *flipsound = new QSoundEffect(this);
    flipsound->setSource(QUrl::fromLocalFile(":/res/ConFlipSound.wav"));
    //创建胜利音效
    QSoundEffect *winsound = new QSoundEffect(this);
    winsound->setSource(QUrl::fromLocalFile(":/res/LevelWinSound.wav"));
    //返回按钮
    MyPushButton *backBtn = new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    //设置返回按钮位置
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());
    //点击返回按钮
    connect(backBtn,&MyPushButton::clicked,[=](){
        qDebug()<<"翻金币场景中：点击了返回按钮";
        //播放返回音效
        backsound->play();
        QTimer::singleShot(500,this,[=](){//延时返回，在这里点击后过0.5s再发送信号
            emit this->choosesceneBack();
        });

    });
    //显示当前关卡数
    QLabel *label = new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    label->setFont(font);
    label->setGeometry(30,this->height() - 50,120,50);
    QString str2 = QString("level: %1").arg(levelindex);
    label->setText(str2);

    dataConfig config;
    //初始化每个关卡的二维数组
    for(int i = 0;i<4;i++){
        for(int j = 0;j<4;j++){
            gameArray[i][j] = config.mData[this->levelindex][i][j];
        }
    }

    //创建胜利动画
    QLabel *winlabel = new QLabel;
    winlabel->setParent(this);
    QPixmap tmppix;
    bool ret = tmppix.load(":/res/LevelCompletedDialogBg.png");
    if(!ret){
        qDebug()<<"胜利图片加载失败";
    }
    winlabel->setGeometry(0,0,tmppix.width(),tmppix.height());
    winlabel->setPixmap(tmppix);
    winlabel->move(this->width()*0.5 - tmppix.width()*0.5,-tmppix.height());




    //显示金币背景图
    for(int i = 0;i<4;i++){
        for(int j = 0;j<4;j++){
            //绘制背景图片
            QLabel *label = new QLabel;
            label->setParent(this);
            label->setGeometry(0,0,50,50);
            label->setPixmap(QPixmap(":/res/BoardNode.png"));
            label->move(57+i*50,200+j*50);

            QString Imgstr;//金币或银币路径
            if(gameArray[i][j] == 1){
                Imgstr = ":/res/Coin0001.png";
            }
            else{
                Imgstr= ":/res/Coin0008.png";
            }
            //创建金币
            MyCoin *coin = new MyCoin(Imgstr);
            coin->setParent(this);
            coin->move(59+i*50,203+j*50);
            coin->posX = i;
            coin->posY = j;
            coin->flag = this->gameArray[i][j];
            //将金币放入到金币的二维数组里，以便后期维护
            coinBtn[i][j] = coin;

            connect(coin,&MyCoin::clicked,[=](){
                //点击某一硬币时，禁止点击其他硬币，设为true状态
                for(int i = 0;i<4;i++){
                    for(int j = 0;j<4;j++){
                        this->coinBtn[i][j]->isWin = true;
                    }
                }
                flipsound->play();
                coin->changeFlag();
                gameArray[i][j] = gameArray[i][j] == 0 ? 1:0;

                //翻转周围硬币
                QTimer::singleShot(300,[=](){
                    if(coin->posX+1<=3){//右侧金币
                        coinBtn[coin->posX+1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX+1][coin->posY] = this->gameArray[coin->posX+1][coin->posY] == 0 ? 1:0;
                    }
                    if(coin->posX-1>=0){//左侧金币
                        coinBtn[coin->posX-1][coin->posY]->changeFlag();
                        this->gameArray[coin->posX-1][coin->posY] = this->gameArray[coin->posX-1][coin->posY] == 0 ? 1:0;
                    }
                    if(coin->posY-1>=0){//上方金币
                        coinBtn[coin->posX][coin->posY-1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY-1] = this->gameArray[coin->posX][coin->posY-1] == 0 ? 1:0;
                    }
                    if(coin->posY+1<=3){//下方金币
                        coinBtn[coin->posX][coin->posY+1]->changeFlag();
                        this->gameArray[coin->posX][coin->posY+1] = this->gameArray[coin->posX][coin->posY+1] == 0 ? 1:0;
                    }

                    for(int i = 0;i<4;i++){
                        for(int j = 0;j<4;j++){
                            this->coinBtn[i][j]->isWin = false;
                        }
                    }
                    this->isWin = true;
                    for(int i = 0;i<4;i++){
                        for(int j = 0;j<4;j++){
                            qDebug()<<coinBtn[i][j]->flag;
                            if(coinBtn[i][j]->flag == false){
                                this->isWin = false;
                                break;
                            }
                        }
                    }

                    if(this->isWin == true){
                        qDebug()<<"游戏胜利了";
                        for(int i = 0;i<4;i++){
                            for(int j = 0;j<4;j++){
                                //qDebug()<<gameArray[i][j]<<coinBtn[i][j];
                                coinBtn[i][j]->isWin = true;
                            }
                        }
                        QPropertyAnimation *animation = new QPropertyAnimation(winlabel,"geometry");
                        //设置时间间隔
                        animation->setDuration(1000);
                        //起始位置
                        animation->setStartValue(QRect(winlabel->x(),winlabel->y(),winlabel->width(),winlabel->height()));
                        //结束为止
                        animation->setEndValue(QRect(winlabel->x(),winlabel->y()+144,winlabel->width(),winlabel->height()));
                        //动画效果
                        animation->setEasingCurve(QEasingCurve::OutBounce);
                        //开始动画
                        animation->start();
                        //播放游戏胜利音效
                        winsound->play();

                    }
                });

            });
        }
    }
}
//设置背景
void PlayScene::paintEvent(QPaintEvent *){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);

    //加载标题
    pix.load(":/res/Title.png");
    pix = pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);
}

