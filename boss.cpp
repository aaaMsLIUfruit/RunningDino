#include "boss.h"

#include<QTimer>
#include<bossmode.h>
#include<QDebug>

#define jingzhi_1 ":/res/jingzhi1.png"
#define jingzhi_2 ":/res/jingzhi2.png"
#define jingzhi_3 ":/res/jingzhi3.png"
#define jingzhi_4 ":/res/jingzhi4.png"

#define pugong_1 ":/res/pugong1.png"
#define pugong_2 ":/res/pugong2.png"

#define jineng_11 ":/res/qishoushi.png"
#define jineng_12 ":/res/jineng1.png"

#define jineng_21 ":/res/qishoushi.png"
#define jineng_22 ":/res/jineng2.png"

#include "ui_boss.h"

static int boss_ac=0;

Boss::Boss(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Boss)
{
    ui->setupUi(this);
    action.setInterval(300);
    do_action.setInterval(5000);
    ji_action.setInterval(100);
    x=750;
    y=0;
    wid=340;
    hei=450;
    hp=10000;
    maxhp=10000;
    jingzhi_=1;
    pugong_=0;
    jineng1_=0;
    jineng2_=0;

    live=0;

    //加载图片
    for(int i=0;i<4;i++)
    {
        jingzhi[i].load(QString(":/res/jingzhi%1.png").arg(i+1));
    }
    for(int i=0;i<2;i++)
    {
        pugong[i].load(QString(":/res/pugong%1.png").arg(i+1));
    }
    for(int i=0;i<2;i++)
    {
        jineng1[i].load(QString(":/res/jineng1%1.png").arg(i+1));
    }
    for(int i=0;i<2;i++)
    {
        jineng2[i].load(QString(":/res/jineng2%1.png").arg(i+1));
    }

    curjing=0;
    curpu=0;
    curji1=0;
    curji2=0;


    connect(&action,&QTimer::timeout,
            [=]()
            {
                if(jingzhi_)
                {
                    curjing=(curjing+1)%4;
                }
                else if(pugong_)
                {
                    curpu++;
                    curpu=curpu%2;
                }
                else if(jineng1_)
                {
                    curji1=(curji1+1)%2;
                }
                else if(jineng2_)
                {
                    curji2=(curji2+1)%2;
                }




            }
            );

    hpp_Timer.setInterval(20);  //设定每帧时长
    connect(&hpp_Timer,&QTimer::timeout,
            [=]()
            {
                if(hp<maxhp)
                {
                    hp+=10 ;
                }

            }
            );
}

void Boss::reducehp()
{
    hp-=200;
}

int Boss::getbaifenzhihp()
{
    return this->hp*100/this->maxhp;
}

QPixmap Boss::getpic()
{
    QPixmap pic;
    /*    if(boss_ac==30)
    {
        boss_ac=0;
        jingzhi_=1;
        pugong_=0;
        jineng1_=0;
        jineng2_=0;
    }
*/
    if(jingzhi_)
    {
        //qDebug()<<"w";
        pic=jingzhi[curjing];
    }
    else if(pugong_)
    {
        //qDebug()<<"ww";
        boss_ac++;
        pic=pugong[curpu];
    }
    else if(jineng1_)
    {
        //qDebug()<<"www";
        boss_ac++;
        pic=jineng1[curji1];
    }
    else if(jineng2_)
    {
        //qDebug()<<"wwww";
        boss_ac++;
        pic=jineng2[curji2];
    }

    return pic;
}

void Boss::die()
{
    if(this->hp<=0)live=0;
}

Boss::~Boss()
{
    delete ui;
}
