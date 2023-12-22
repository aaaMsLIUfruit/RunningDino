#include "bossplayer.h"
#include <QTimer>
#include "bossmode.h"
#include <QDebug>

#define run_1 ":/res/DINO_RUN1.png"
#define run_2 ":/res/DINO_RUN2.png"
//#define run_3 ":/res/DINO_RUN1.png"
//#define run_4 ":/res/DINO_RUN2.png"
//#define run_5 ":/res/DINO_RUN1.png"
#define jump ":/res/DINO_JUMP.png"


Bossplayer::Bossplayer(QWidget *parent)
    :QWidget(parent)

{

    this->hp=7200;
    this->maxhp=7200;
    this->wid=50;
    this->hei=50;
    this->x=100;
    this->y=20;
    jump_once=0;
    jump_twice=0;
    twice_jumpready=0;
    in_fall=0;
    jump_h=100;//跳跃高度
    fall_speed=0;
    jump_speed=20;
    fallspeed_a=1;

    zidanshu=4;

    zidan_Timer.setInterval(10000);


    jump_Timer.setInterval(400);
    jump_Timer.setSingleShot(true);

    //加载图片
    for(int i=0;i<2;i++)
    {
        run_pic[i].load(QString(":/res/DINO_RUN%1.png").arg(i+1));
    }
    jump_pic.load(jump);
    currunpic=0;
    run_Timer.setInterval(100);//设定每帧时长

    connect(&run_Timer,&QTimer::timeout,
            [=]()
            {
               currunpic=(currunpic+1)%2;

            }
      );//跑步图片的切换


    //下面设定生命恢复
    hp_Timer.setInterval(20);  //设定每帧时长
    connect(&hp_Timer,&QTimer::timeout,
            [=]()
            {
                    if(hp<maxhp)
                    {
                        hp+=1 ;
                    }

            }
      );

}


//最最最重要的，人物移动部分
void Bossplayer::move(bool up, bool down, bool right, bool left)
{
    if(this->y==400)
    {
        twice_jumpready=1;//610是地面高度
        fall_speed=0;
    }
    if(up)
    {
        //一段跳
        if(this->y==400)
        {
            jump_Timer.start();
            jump_once=0;

        }
        //二段跳判断
        if(this->y<400 && twice_jumpready && jump_once)
        {
            jump_Timer.start();
            fall_speed=0;
            twice_jumpready=0;
        }
        if(jump_Timer.isActive())
        {
            //this->y-=jump_Timer.remainingTime()/400;
            this->y-=jump_speed*jump_Timer.remainingTime()/400;
        }

    }
    else
    {
        jump_Timer.stop();
        jump_once=true;

    }

    //下落
    this->y+=fall_speed;

    //位置限定
    if(this->y>400)
    {
        this->y=400;
    }
    if(this->y<20)
    {
        this->y=20;

    }
    if(this->x<20)
    {
        this->x=20;
    }
    if(this->x>980)
    {
        this->x=980;
    }

    //下落判断
    if(!jump_Timer.isActive())
    {
        fall_speed +=fallspeed_a;
    }
    else
    {
        fall_speed=0;
    }

    //加速下落
    if(down)
    {
        if(this->y<600-196&&!jump_Timer.isActive())
        {
            fall_speed+=fallspeed_a*2;

        }
    }

    //向右加速跑
    if(right)
    {
        this->x+=5;
    }
    else
    {
        this->x-=1;
    }
    //向左
    if(left)
    {
        this->x-=5;
    }
    else
    {
        this->x+=1;
    }


    this->score++;


}

int Bossplayer::getx()
{
    return this->x;
}
int Bossplayer::gety()
{
    return this->y;
}
int Bossplayer::getwid()
{
    return this->wid;
}
int Bossplayer::gethei()
{
    return this->hei;
}
void Bossplayer::setScore(int n)
{
    this->score+=n;
}
int Bossplayer::getScore()
{
    return this->score;
}


QPixmap Bossplayer::getpic()
{
    QPixmap pic;
    if(this->y<400||this->y>400)
    {
        pic=jump_pic;
    }
    else
    {
        pic=run_pic[currunpic];
    }
    return pic;

}

void Bossplayer::pauseplayer()
{
    run_Timer.stop();
    zidan_Timer.stop();
}
void Bossplayer::continueplayer()
{
    run_Timer.start();
    zidan_Timer.start();
}

//血量操作
void Bossplayer::reducehp()
{
    this->hp-=600;
    if(this->hp<=0)this->hp=0;
}
int Bossplayer::gethp()
{
    return this->hp;
}
int Bossplayer::getbaifenzhihp()
{
    return this->hp*100/this->maxhp;
}
void Bossplayer::increasehp(int n)
{
    this->hp+=n;
    if(this->hp>this->maxhp)this->hp=this->maxhp;
}


//dash
void Bossplayer::dashmove_()
{
    x+=400;
}
void Bossplayer::addscore(int s)
{
    this->score+=s;
}

//射击
bool Bossplayer::shot()
{
    if(zidanshu==0)return 0;
    return 1;
}
void Bossplayer::addzidan()
{
    if(zidanshu==4)return;
    zidanshu++;
}
int Bossplayer::getzidan()
{
    return this->zidanshu;
}
