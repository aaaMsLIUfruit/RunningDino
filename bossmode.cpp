#include "bossmode.h"
#include <bossplayer.h>
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>
#include <QVector>
#include <vector>
#include <time.h>
#include <QTime>
#include <ctime>
#include <QMessageBox>
#include <QFile>
//#include <QSound>
#include <QDesktopServices>
#include <QTimer>
#include <QFontDatabase>


#include "bossmode.h"
#include "ui_bossmode.h"

#define start_ui ":/res/start_ui.PNG"
#define back_game ":/res/background.png"
#define ground_pic ":/res/Land.png"
#define hurtpic ":/res/hurt.png"
#define gameover ":/res/death.JPG"
#define pause ":/res/pause.png"

//音效
#define jump ":/res/jump.wav"
#define coin_pic ":/res/coin.wav"
#define over ":/res/over.wav"
#define collision ":/res/collision.wav"

Bossmode::Bossmode(QWidget *parent,int wid ,int hei) :
    QWidget(parent),
    ui(new Ui::Bossmode)
{
    ui->setupUi(this);
    this->resize(wid, hei); // 设置场景的宽度和高度
    // 假设 this 是子窗口，parentWidget() 返回其父窗口

    //    if (parent) {
    //        QRect parentGeometry = parent->geometry();
    //        int x = parentGeometry.x() + (parentGeometry.width() - this->width()) / 2;
    //        int y = parentGeometry.y() + (parentGeometry.height() - this->height()) / 2;
    //        this->move(x, y);

    //    }


    ground_Y = hei - 120; // 设置地面的垂直位置，假设地面高度为 120

    // 加载游戏所需的图像资源
    background.load(back_game); // 加载背景图片
    before_start.load(start_ui);  // 加载游戏开始前的图片
    ground.load(ground_pic);    // 加载地面的图片
    hurtImg.load(hurtpic);      // 加载角色受伤时的图片
    pauseImg.load(pause);       // 加载暂停游戏时的图片
    gameOverImg.load(gameover); // 加载游戏结束时的图片

    // 初始化玩家角色的按键操作状态
    up = down = left = right = 0; // 初始化方向键为未按下状态
    difficulty = 0;                // 初始化难度级别为0

    // 初始化游戏的状态变量
    isRuning = 0;   // 游戏是否正在运行，0 表示不在运行
    isPause = 0;    // 游戏是否暂停，0 表示未暂停
    ground_speed = 1; // 设置地面移动的速度
    ground_X = 0;     // 设置地面的初始水平位置
    Score = 0;        // 初始化玩家的得分
    beforegame = 1;   // 游戏开始前的状态标志，1 表示游戏尚未开始
    Coinnum = 0;      // 初始化收集到的金币数量

    remove.setInterval(17); // 设置定时器的时间间隔，用于定时更新游戏场景

    this->grabKeyboard(); // 获取键盘输入，确保可以接收玩家的按键操作

    //时间事件处理
    /*
    connect(&r->zidan_Timer,&QTimer::timeout,[=]()
    {
        r->addzidan();
    });
*/

    //按钮设置
    backButton = new QPushButton("返回",this);
    restartButton = new QPushButton("重来",this);
    continueButton = new QPushButton("继续",this);
    connect(backButton,&QPushButton::clicked,this,&Bossmode::backButton_clicked);
    connect(restartButton,&QPushButton::clicked,this,&Bossmode::restartButton_clicked);
    connect(continueButton,&QPushButton::clicked,this,&Bossmode::gamecontinue);
    backButton->setGeometry(450,300,100,40);
    restartButton->setGeometry(450,360,100,40);
    continueButton->setGeometry(450,360,100,40);
    backButton->hide();
    restartButton->hide();
    continueButton->hide();


    connect(&remove, &QTimer::timeout, [=]()
            {
                // 重新装弹逻辑
                connect(&r->zidan_Timer, &QTimer::timeout, [=]()
                        {
                            r->addbullet(); // 调用角色 r 的 addzidan 方法添加子弹
                        });

                // Boss 行为判断逻辑
                connect(&rr->do_action, &QTimer::timeout, [=]()
                        {
                            int xxx = rand() % 4; // 随机选择一个数字来决定 Boss 的行动
                            // 根据随机数改变 Boss 的状态
                            rr->jingzhi_ = (xxx == 0);
                            rr->pugong_ = (xxx == 1);
                            rr->jineng1_ = (xxx == 2);
                            rr->jineng2_ = (xxx == 3);
                        });

                // 控制角色 r 的移动
                r->move(up, down, right, left);

                // 游戏难度增加逻辑
                if (difficulty <= 80)
                {
                    difficulty += 0.001; // 游戏难度逐渐增加，直到达到上限 80
                }
                else
                {
                    difficulty = 80; // 难度上限
                }

                // 处理忍币障碍物
                for (auto i = obstacle1.begin(); i != obstacle1.end(); )
                {
                    if ((*i)->done()) // 检查忍币是否超出屏幕范围
                    {
                        delete *i;//释放内存
                        i = obstacle1.erase(i); // 超出屏幕的忍币被删除
                    }
                    else
                    {
                        // 检查忍币是否与角色 r 发生碰撞
                        if ((*i)->collided(r->getx() - 5, r->gety() - 5, r->getwid() - 5, r->getwid() - 5))
                        {
                            //                    QSound::play(coin_pic); // 播放金币收集声音
                            r->setScore(2000);// 角色吃币加分
                            delete *i;//释放内存
                            i = obstacle1.erase(i); // 删除已经收集的忍币
                            Coinnum++; // 增加收集到的忍币数量
                            break; // 跳出循环，因为迭代器已被修改
                        }
                        else
                        {
                            (*i)->move(); // 如果没有碰撞，则移动忍币
                            ++i; // 迭代器前进
                        }
                    }
                }
                //飞箭
                // 遍历飞箭障碍物列表
                for(auto i = obstacle2.begin(); i != obstacle2.end(); )
                {
                    if ((*i)->done()) // 检查飞箭是否超出屏幕范围
                    {
                        delete *i;//释放内存
                        i = obstacle2.erase(i); // 如果是，从列表中删除飞箭
                    }
                    else
                    {
                        // 检查飞箭是否与角色发生碰撞
                        if ((*i)->collided(r->getx() - 5, r->gety() - 5, r->getwid() - 5, r->getwid() - 5))
                        {
                            //                    QSound::play(collision); // 播放碰撞声音
                            r->reducehp(); // 角色减少生命值

                            // 根据玩家的得分进行相应的处理
                            if (r->getScore() > 2000)
                                goto K; // 如果得分超过2000，跳转到标签 K
                            if (r->getScore() >= 100)
                                r->setScore(-100); // 如果得分大于等于100，减少100分
                            else
                                r->setScore(0); // 否则得分设置为0
                        K:; // 标签 K

                            hurtImgAlpha = 255; // 设置受伤图片的透明度
                            delete *i;//释放内存
                            i = obstacle2.erase(i); // 清空飞箭列表

                            break; // 处理完碰撞后退出循环
                        }
                        if (!obstacle2.empty())
                        {
                            (*i)->move(); // 如果列表不为空，则移动飞箭
                            ++i; // 迭代器前进
                        }
                    }
                }

                //飞镖
                // 遍历飞镖障碍物列表
                for(auto i = obstacle3.begin(); i != obstacle3.end(); )
                {
                    if ((*i)->done()) // 检查飞镖是否超出屏幕范围
                    {
                        delete *i;//释放内存
                        i = obstacle3.erase(i); // 如果是，从列表中删除飞镖
                    }
                    else
                    {
                        // 检查飞镖是否与角色发生碰撞
                        if ((*i)->collided(r->getx() - 5, r->gety() - 5, r->getwid() - 5, r->getwid() - 5))
                        {
                            //                    QSound::play(collision); // 播放碰撞声音
                            r->reducehp(); // 角色减少生命值

                            // 根据玩家的得分进行相应的处理
                            if (r->getScore() > 2000)
                                goto Kk; // 如果得分超过2000，跳转到标签 Kk
                            if (r->getScore() >= 100)
                                r->setScore(-100); // 如果得分大于等于100，减少100分
                            else
                                r->setScore(0); // 否则得分设置为0
                        Kk:; // 标签 Kk

                            hurtImgAlpha = 255; // 设置受伤图片的透明度
                            delete *i;//释放内存
                            i = obstacle3.erase(i); // 清空飞镖列表

                            break; // 处理完碰撞后退出循环
                        }
                        if (!obstacle3.empty())
                        {
                            (*i)->move(); // 如果列表不为空，则移动飞镖
                            ++i; // 迭代器前进
                        }
                    }
                }

                //子弹
                // 遍历子弹障碍物列表
                //子弹
                for (auto p = obstacle4.begin(); p != obstacle4.end(); )
                {
                    if ((*p)->done())
                    {
                        delete *p;//释放内存
                        p = obstacle4.erase(p); // 如果子弹超出屏幕范围，删除子弹
                    }
                    else
                    {
                        bool collisionOccurred = false;

                        // 检查子弹是否与飞箭发生碰撞
                        for (auto i = obstacle2.begin(); i != obstacle2.end() && !collisionOccurred; ++i)
                        {
                            if ((*p)->collided((*i)->getx() - 5, (*i)->gety() - 5, (*i)->getwid() - 5, (*i)->getwid() - 5))
                            {
                                //                        QSound::play(collision);
                                (*p)->sety(2000); // 将子弹移出屏幕
                                (*i)->sety(-50);  // 将飞箭移出屏幕
                                collisionOccurred = true;
                            }
                        }

                        // 检查子弹是否与飞镖发生碰撞
                        for (auto i = obstacle3.begin(); i != obstacle3.end() && !collisionOccurred; ++i)
                        {
                            if ((*p)->collided((*i)->getx() - 5, (*i)->gety() - 5, (*i)->getwid() - 5, (*i)->getwid() - 5))
                            {
                                //                        QSound::play(collision);
                                (*p)->sety(2000); // 将子弹移出屏幕
                                (*i)->sety(-50);  // 将飞镖移出屏幕
                                collisionOccurred = true;
                            }
                        }

                        // 检查子弹是否与 Boss 发生碰撞
                        if (!collisionOccurred && (*p)->collided(rr->x - 5, rr->y - 5, rr->wid - 5, rr->hei - 5))
                        {
                            //                    QSound::play(collision);
                            (*p)->sety(2000); // 将子弹移出屏幕
                            rr->reducehp();   // 减少 Boss 的生命值
                            collisionOccurred = true;
                        }

                        if (!collisionOccurred)
                        {
                            (*p)->move(); // 如果没有发生碰撞，则移动子弹
                            ++p;
                        }
                        else
                        {
                            delete *p;//释放内存
                            p = obstacle4.erase(p); // 删除发生碰撞的子弹
                        }
                    }
                }


                //普攻
                // 遍历普攻障碍物列表
                for(auto i = obstacle5.begin(); i != obstacle5.end(); )
                {
                    if ((*i)->done()) // 检查普攻是否超出屏幕范围
                    {
                        delete *i;//释放内存
                        i = obstacle5.erase(i); // 如果是，从列表中删除普攻
                    }
                    else
                    {
                        // 检查普攻是否与角色发生碰撞
                        if ((*i)->collided(r->getx() - 5, r->gety() - 5, r->getwid() - 5, r->getwid() - 5))
                        {
                            //                    QSound::play(collision); // 播放碰撞声音
                            r->reducehp(); // 角色减少生命值

                            // 根据玩家的得分进行相应的处理
                            if (r->getScore() >= 100)
                                r->setScore(-100); // 如果得分大于等于100，减少100分
                            else
                                r->setScore(0); // 否则得分设置为0

                            hurtImgAlpha = 255; // 设置受伤图片的透明度
                            delete *i;//释放内存
                            i = obstacle5.erase(i); // 删除已处理的普攻

                            break; // 处理完碰撞后退出循环
                        }
                        if (!obstacle5.empty())
                        {
                            (*i)->move(); // 如果列表不为空，则移动普攻
                            ++i; // 迭代器前进
                        }
                    }
                }

                //技能1
                // 遍历技能1障碍物列表
                for(auto i = obstacle6.begin(); i != obstacle6.end(); )
                {
                    if ((*i)->done()) // 检查技能1是否超出屏幕范围
                    {
                        delete *i;//释放内存
                        i = obstacle6.erase(i); // 如果是，从列表中删除技能1
                    }
                    else
                    {
                        // 检查技能1是否与角色发生碰撞
                        if ((*i)->collided(r->getx() - 5, r->gety() - 5, r->getwid() - 5, r->getwid() - 5))
                        {
                            //                    QSound::play(collision); // 播放碰撞声音
                            r->reducehp(); // 角色减少生命值

                            // 根据玩家的得分进行相应的处理
                            if (r->getScore() >= 100)
                                r->setScore(-100); // 如果得分大于等于100，减少100分
                            else
                                r->setScore(0); // 否则得分设置为0

                            hurtImgAlpha = 255; // 设置受伤图片的透明度
                            delete *i;//释放内存
                            i = obstacle6.erase(i); // 删除已处理的技能1

                            break; // 处理完碰撞后退出循环
                        }
                        if (!obstacle6.empty())
                        {
                            (*i)->move(); // 如果列表不为空，则移动技能1
                            ++i; // 迭代器前进
                        }
                    }
                }


                //技能2
                static int hurttime = 30; // 设置一个静态变量，用于控制受伤的计时

                // 遍历技能2障碍物列表
                for(auto i = obstacle7.begin(); i != obstacle7.end(); )
                {
                    if ((*i)->done()) // 检查技能2是否超出屏幕范围
                    {
                        delete *i;//释放内存
                        i = obstacle7.erase(i); // 如果是，从列表中删除技能2
                    }
                    else
                    {
                        if (hurttime > 1) goto LI; // 如果受伤计时未结束，跳转到标签 LI

                        // 检查技能2是否与角色发生碰撞
                        if ((*i)->collided(r->getx() - 5, r->gety() - 5, r->getwid() - 5, r->getwid() - 5))
                        {
                            //                    QSound::play(collision); // 播放碰撞声音
                            r->reducehp(); // 角色减少生命值
                            hurttime = 30; // 重置受伤计时
                            hurtImgAlpha = 255; // 设置受伤图片的透明度
                            delete *i;//释放内存
                            i = obstacle7.erase(i); // 删除已处理的技能2
                            break; // 处理完碰撞后退出循环
                        }
                    LI: // 标签 LI
                        if (!obstacle7.empty())
                        {
                            hurttime--; // 受伤计时递减
                            (*i)->move(); // 如果列表不为空，则移动技能2
                            ++i; // 迭代器前进
                        }
                    }
                }


                //红心
                // 遍历红心障碍物列表
                for(auto i = obstacle8.begin(); i != obstacle8.end(); )
                {
                    if ((*i)->done()) // 检查红心是否超出屏幕范围
                    {
                        delete *i;//释放内存
                        i = obstacle8.erase(i); // 如果是，从列表中删除红心
                    }
                    else
                    {
                        // 检查红心是否与角色发生碰撞
                        if ((*i)->collided(r->getx() - 5, r->gety() - 5, r->getwid() - 5, r->getwid() - 5))
                        {
                            r->increasehp(300); // 角色增加生命值
                            delete *i;//释放内存
                            i = obstacle8.erase(i); // 删除已处理的红心
                            break; // 处理完碰撞后退出循环
                        }
                        if (!obstacle8.empty())
                        {
                            (*i)->move(); // 如果列表不为空，则移动红心
                            ++i; // 迭代器前进
                        }
                    }
                }








                if(isRuning)
                {
                    if(r->gethp()<=0)
                    {
                        gameIsOver();//结束游戏
                    }

                    addobstacle();//增加障碍物函数
                }

                //音乐部分




            });



}

Bossmode::~Bossmode()
{
    delete ui;
}

//绘制地图
void Bossmode::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    if(isRuning==0&&beforegame==1)//首页
    {
        painter.drawPixmap(0,0,this->width(),this->height(),QPixmap(before_start));
    }
    else if(GameOver==1)//结束
    {
        painter.drawPixmap(QRect(0,0,this->width(),this->height()),gameOverImg);
    }
    else//游戏中
    {
        //背景图片

        /*      painter.drawPixmap(QRect(0,0,this->width(),this->height())
                     ,background
                     ,QRect(backImgX[0],0,this->width(),this->height()));  //在指定区域绘制指定尺寸的图片
        if(backImgX[0]>0)
        {
            painter.drawPixmap(QRect(background.width()-backImgX[0],0,this->width()-(background.width()-backImgX[0]),this->height())
                         ,background
                         ,QRect(0,0,this->width()-(background.width()-backImgX[0]),this->height()));   //补充右边的空白区域
        }
        if(backImgX[0]>=background.width())
        {
              backImgX[0]-=background.width();
        }
        if(isRuning&&isPause==false)
        {
            backImgX[0]+=imgSpeed[0]; //图片剪切区域x起点
        }
*/

        // 绘制背景
        painter.drawPixmap(QRect(0, 0, this->width(), this->height()), background);

        // 绘制地面
        painter.drawPixmap(QRect(0, ground_Y, this->width(), this->height() - ground_Y),
                           ground, QRect(ground_X, 0, this->width(), this->height() - ground_Y));

        // 如果地面的宽度不足以覆盖整个屏幕，补充绘制地面的剩余部分
        if (ground_X > ground.width() - this->width())
        {
            painter.drawPixmap(QRect(ground.width() - ground_X, this->ground_Y, this->width() - (ground.width() - ground_X), this->height() - this->ground_Y),
                               ground,
                               QRect(0, 0, this->width() - (ground.width() - ground_X), this->height() - this->ground_Y));
        }

        // 如果地面移动到尽头，从头开始循环
        if (ground_X >= ground.width())
        {
            ground_X -= ground.width();
        }

        // 如果游戏正在运行且未暂停，地面移动
        if (isRuning && !isPause)
        {
            ground_X += ground_speed;
        }

        // 绘制人物
        painter.drawPixmap(QRect(r->getx(), r->gety(), r->getwid(), r->gethei()), r->getpic());

        // 绘制受伤效果
        if (hurtImgAlpha != 0)
        {
            QPixmap temp(hurtImg.size());
            temp.fill(Qt::transparent); // 使用透明色填充临时图像
            QPainter p2(&temp);
            p2.setCompositionMode(QPainter::CompositionMode_Source);
            p2.drawPixmap(0, 0, hurtImg); // 绘制受伤图片
            p2.setCompositionMode(QPainter::CompositionMode_DestinationIn);
            p2.fillRect(temp.rect(), QColor(0, 0, 0, hurtImgAlpha)); // 应用透明度
            painter.drawPixmap(QRect(0, 0, this->width(), this->height()), temp); // 绘制到主画布
            hurtImgAlpha -= 3; // 逐渐减少受伤图片的透明度
        }


        //血量、金币、分数

        //导入并设置字体
        //        int fontId = QFontDatabase::addApplicationFont(QStringLiteral(":/res/ark-pixel-12px-monospaced-zh_cn.ttf"));
        //        QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
        //        QFont font;
        //        font.setFamily(fontFamilies[0]);
        //        font.setPointSize(20);

        ///我用这个太卡了，换个狗市字体。///

        QFont font;
        font.setFamily("Consolas");
        font.setPointSize(20);



        //血量
        //        painter.drawRect(QRect(600,50,150,10));
        //        painter.drawLine(600,50,1050,60);
        //        painter.drawLine(600,50,1100,60);   //划线


        QPainter hp_painter(this);
        QBrush red_brush( QColor("#F20900") );//把刷子设置为红色
        hp_painter.setBrush(red_brush);//应用刷子
        float rate = 1.0*r->gethp()/r->maxhp;//计算比例
        float bo_rate=1.0*rr->hp/rr->maxhp;
        hp_painter.drawRect(150,457,rate*100,30);//绘制人物血量

        //QPen pen1(Qt::white);
        painter.setFont(font);
        //pen1.setColor(Qt::white);
        painter.setPen(Qt::black);
        painter.drawText(100,480,QString("HP:       %1%").arg(r->gethppercent()));



        //金币数量
        painter.drawText(100,50,QString("Coinnum:%1").arg(Coinnum)) ;

        //分数
        painter.drawText(100,150,QString("Score:%1").arg(r->getScore()));


        //子弹数显示
        painter.drawText(100,100,QString("Bullet:%1").arg(r->getbullet()));




        //障碍物
        // 遍历金币障碍物列表
        for(auto i = obstacle1.begin(); i != obstacle1.end(); i++)
        {
            // 使用 QPainter 绘制每个金币障碍物
            painter.drawPixmap(QRect((*i)->getx(), (*i)->gety(), (*i)->getwid(), (*i)->gethei()), (*i)->getpic());
        }

        for(auto i=obstacle2.begin();i!=obstacle2.end();i++)
        {
            painter.drawPixmap(QRect((*i)->getx(),(*i)->gety(),(*i)->getwid(),(*i)->gethei()),(*i)->getpic());
        }
        for(auto i=obstacle3.begin();i!=obstacle3.end();i++)
        {
            painter.drawPixmap(QRect((*i)->getx(),(*i)->gety(),(*i)->getwid(),(*i)->gethei()),(*i)->getpic());
        }
        //子弹
        for(auto i=obstacle4.begin();i!=obstacle4.end();i++)
        {
            painter.drawPixmap(QRect((*i)->getx(),(*i)->gety(),(*i)->getwid(),(*i)->gethei()),(*i)->getpic());
        }

        //技能、普攻
        for(auto i=obstacle5.begin();i!=obstacle5.end();i++)
        {
            painter.drawPixmap(QRect((*i)->getx(),(*i)->gety(),(*i)->getwid(),(*i)->gethei()),(*i)->getpic());
            //qDebug()<<"pg";
        }
        for(auto i=obstacle6.begin();i!=obstacle6.end();i++)
        {
            if((*i)->getx()<=600)
            {
                (*i)->speed=100;
            }
            painter.drawPixmap(QRect((*i)->getx(),(*i)->gety(),(*i)->getwid(),(*i)->gethei()),(*i)->getpic());
        }
        for(auto i=obstacle7.begin();i!=obstacle7.end();i++)
        {
            painter.drawPixmap(QRect((*i)->getx(),(*i)->gety(),(*i)->getwid(),(*i)->gethei()),(*i)->getpic());
        }

        //红心
        for(auto i=obstacle8.begin();i!=obstacle8.end();i++)
        {
            painter.drawPixmap(QRect((*i)->getx(),(*i)->gety(),(*i)->getwid(),(*i)->gethei()),(*i)->getpic());
        }



        //        //暂停画面
        //        if(isPause&&!GameOver)
        //        {
        //            painter.drawPixmap(QRect(0,0,this->width(),this->height()),pauseImg);
        //        }



        //BOSS出场
        if(Coinnum > 0 && rr->hp > 0)
        {
            rr->live = 1;  // 设置Boss为活跃状态

            //qDebug() << "Drawing Boss";
            // 绘制Boss的图像
            painter.drawPixmap(QRect(rr->x, rr->y, rr->wid, rr->hei), rr->getpic());
            //qDebug() << "Boss drawn";

            // 绘制Boss血量条
            hp_painter.drawRect(390, 50, bo_rate * 400, 30);

            // 创建一个新的画笔用于绘制Boss血量文本
            QPainter bo_painter(this);
            bo_painter.setFont(font); // 设置字体
            bo_painter.setPen(Qt::black); // 设置画笔颜色为黑色
            // 绘制Boss血量文本
            bo_painter.drawText(300, 75, QString("Boss:                        %1%").arg(rr->getbaifenzhihp()));
        }
        rr->die(); // 调用Boss的死亡处理函数

        update();  // 请求更新窗口，将会触发重绘
    }
}

//添加障碍物
void Bossmode::addobstacle()
{
    static int Lastcoin_time; // 静态变量，用于记录上一次生成金币后经过的时间

    // 判断是否到达生成新金币的时间
    if (Lastcoin_time >= 30 - difficulty)
    {
        int x = this->width() + 5;             // 设置金币的起始 x 坐标（屏幕右侧外）
        int y = ground_Y - 18 - rand() % 300;  // 随机设置金币的起始 y 坐标

        // 在忍币列表中添加一个新的金币对象
        obstacle1.push_back(new coin(x, y, 20, 20));

        Lastcoin_time = 0; // 重置时间计数器
    }
    Lastcoin_time++; // 时间计数器自增，记录自上次生成金币后经过的时间


    // 红心生成逻辑
    static int Lastheart_time; // 上次生成红心的时间
    if (Lastheart_time >= 120 - difficulty) // 根据难度和时间间隔判断是否生成红心
    {
        int x = this->width() + 5; // 设置红心的水平起始位置
        int y = ground_Y - 18 - rand() % 300; // 设置红心的垂直位置，随机化以增加多样性
        obstacle8.push_back(new redheart(x, y, 40, 40)); // 创建红心对象并加入障碍物列表
        Lastheart_time = 0; // 重置红心生成计时器
    }
    Lastheart_time++; // 更新红心生成计时器

    // 飞箭生成逻辑
    static int Lastfarrow_time; // 上次生成飞箭的时间
    if (Lastfarrow_time >= 100 - difficulty) // 根据难度和时间间隔判断是否生成飞箭
    {
        int x = this->width() + 100; // 设置飞箭的水平起始位置
        int y = ground_Y - 90 - rand() % 400; // 设置飞箭的垂直位置
        obstacle2.push_back(new farrow(x, y, 200, 50)); // 创建飞箭对象并加入障碍物列表
        Lastfarrow_time = 0; // 重置飞箭生成计时器
    }
    Lastfarrow_time++; // 更新飞箭生成计时器

    // 飞镖生成逻辑
    static int Lastfbbb_time; // 上次生成飞镖的时间
    if (Lastfbbb_time >= 220 - difficulty) // 根据难度和时间间隔判断是否生成飞镖
    {
        int x = this->width() + 100; // 设置飞镖的水平起始位置
        int y = ground_Y - 90 - rand() % 400; // 设置飞镖的垂直位置
        obstacle3.push_back(new fbbb(x, y, 70, 70)); // 创建飞镖对象并加入障碍物列表
        Lastfbbb_time = 0; // 重置飞镖生成计时器
    }
    Lastfbbb_time += 2; // 更新飞镖生成计时器，以较慢的速度增长

    // 普攻生成逻辑
    static int pugong_time; // 上次生成普攻的时间
    if (rr->live && rr->pugong_ && pugong_time > 60) // 如果Boss活着且处于普攻状态，且时间间隔满足条件
    {
        int x = rr->x; // 设置普攻的水平位置
        int y = 400; // 设置普攻的垂直位置
        obstacle5.push_back(new pug(x, y, 200, 80)); // 创建普攻对象并加入障碍物列表
        pugong_time = 0; // 重置普攻生成计时器
    }
    pugong_time++; // 更新普攻生成计时器
    if (!rr->pugong_) // 如果Boss不再进行普攻
    {
        obstacle5.clear(); // 清除所有普攻对象
    }

    // 技能1生成逻辑
    static int jineng1_time; // 上次生成技能1的时间
    if (rr->live && rr->jineng1_ && jineng1_time > 80) // 如果Boss活着且处于技能1状态，且时间间隔满足条件
    {
        int x = rr->x; // 设置技能1的水平位置
        int y = ground_Y - rand() % 400; // 设置技能1的垂直位置
        jin1 *ppp = new jin1(x, y, 300, 100); // 创建技能1对象
        ppp->jineng_Timer.start(); // 启动技能1的定时器
        obstacle6.push_back(ppp); // 将技能1对象加入障碍物列表
        jineng1_time = 0; // 重置技能1生成计时器
    }
    jineng1_time++; // 更新技能1生成计时器
    if (!rr->jineng1_) // 如果Boss不再进行技能1
    {
        obstacle6.clear(); // 清除所有技能1对象
    }


    static int jineng2_time;
    static int jineng2_num=0;
    if(rr->live&&rr->jineng2_&&jineng2_time>80)
    {
        if(jineng2_num==1)goto LO;
        int x=rr->x;
        int y=400;
        jin2 *ppp=new jin2(x,y,300,100);
        ppp->jineng_Timer.start();
        obstacle7.push_back(ppp);
        jineng2_time=0;
        jineng2_num=1;
    }
LO:
    jineng2_time++;
    if(!rr->jineng2_)
    {
        jineng2_num=0;
        obstacle7.clear();
    }





}

void Bossmode::start_game()
{
    r=new Bossplayer(this);
    r->run_Timer.start();
    remove.start();
    r->hp_Timer.start();
    r->zidan_Timer.start();

    rr=new Boss();
    rr->action.start();
    rr->do_action.start();\



    GameOver=0;
    beforegame=0;
    isRuning=1;
    Coinnum=0;
    isPause=0;
    update();
}

//键盘响应
void Bossmode::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_W)
    {
        up=true;
        //        QSound::play(jump);
    }
    else if(event->key()==Qt::Key_S)
    {
        down=true;
    }
    else if(event->key()==Qt::Key_D)
    {
        right=true;
    }
    else if(event->key()==Qt::Key_A)
    {
        left=true;
    }
    else if(event->key()==Qt::Key_J)
    {
        shott();
    }
    else if(!GameOver&&event->key()==Qt::Key_Escape)
    {
        if(isPause==false)
        {
            r->hp_Timer.stop();
            gamepause();

        }
        else
        {
            r->hp_Timer.start();
            gamecontinue()  ;
        }
    }
    else if(!GameOver && isRuning&&!isPause&&event->key()==Qt::Key_Q)
    {
        r->dashmove_() ;
    }
    else if(GameOver && event->key()==Qt::Key_R)
    {
        start_game();
    }
    //    else if(GameOver&&event->key()==Qt::Key_B)
    //    {
    //        back();
    //    }
    else
    {
        return QWidget::keyPressEvent(event);
    }

}

//void Bossmode::back()
//{
//    beforegame=1;
//    button->move(900,400);
//    button_2->show();
//    update();
//}

void Bossmode::gamepause()
{
    isPause = true;
    remove.stop() ;
    backButton->show();
    continueButton->show();
    r->pauseplayer();
    rr->action.stop();
    rr->do_action.stop();

}

void Bossmode::gamecontinue()
{
    isPause = false;
    remove.start() ;
    backButton->hide();
    continueButton->hide();
    r->continueplayer();
    rr->action.stop();
    rr->do_action.stop();

}

//键盘松开的时候进行的复位操作
void Bossmode::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_W)
    {
        up=false;
        //qDebug()<<up;
    }
    else if(event->key()==Qt::Key_S)
    {
        down=false;
    }
    else if(event->key()==Qt::Key_D)
    {
        right=false;
    }
    else if(event->key()==Qt::Key_A)
    {
        left=false;
    }
    else
    {
        return QWidget::keyPressEvent(event);
    }

}

void Bossmode::gameIsOver()
{
    //    QSound::play(over);
    Score=r->getScore();



    isRuning=0;
    GameOver=1;


    backButton->show();
    restartButton->show();


    remove.stop();
    obstacle1.clear();
    obstacle2.clear();
    obstacle3.clear();


    r->run_Timer.stop();
    r->zidan_Timer.stop();
    rr->action.stop();
    rr->do_action.stop();


    delete r;
    delete rr;
    update();
}

void Bossmode::shott()
{
    if(!r->shot())return;
    r->zidanshu--;
    bullet *p=new bullet(r->getx()+20,r->gety(),20,20);
    obstacle4.push_back(p);

}

void Bossmode::backButton_clicked(){
    emit boss_close();
    this->close();
}

void Bossmode::restartButton_clicked(){
    start_game();
    backButton->hide();
    restartButton->hide();
}



