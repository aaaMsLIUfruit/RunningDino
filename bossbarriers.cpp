#include "bossbarriers.h"

#include<QTimer>
#include<QDebug>


#define coin_1 ":/res/coin.png"
#define fj ":/res/feijian.png"
#define fb ":/res/feibiao.png"
#define bullet_pic ":/res/bullet.png"
#define pug_ ":/res/pugong.png"
#define redhea ":/res/blood.png"

//基类
// Bossbarriers 类的构造函数，用于初始化障碍物的位置和尺寸
Bossbarriers::Bossbarriers(int x, int y, int width, int height)
{
    this->x = x; // 设置障碍物的水平位置
    this->y = y; // 设置障碍物的垂直位置
    this->width = width; // 设置障碍物的宽度
    this->height = height; // 设置障碍物的高度
    curji = 0; // 初始化当前技能图片索引
    jineng_Timer.setInterval(100); // 设置技能切换的定时器间隔（毫秒）
    // 连接定时器的timeout信号以更新技能图片
    connect(&jineng_Timer, &QTimer::timeout,
            [=]()
            {
                curji = (curji + 1) % 4; // 循环更新技能图片索引
            }
            );
}

// 获取障碍物的水平位置
int Bossbarriers::getx()
{
    return this->x;
}

// 获取障碍物的垂直位置
int Bossbarriers::gety()
{
    return this->y;
}

// 设置障碍物的水平位置
void Bossbarriers::setx(int x)
{
    this->x = x;
}

// 设置障碍物的垂直位置
void Bossbarriers::sety(int y)
{
    this->y = y;
}

// 获取障碍物的宽度
int Bossbarriers::getwid()
{
    return this->width;
}

// 获取障碍物的高度
int Bossbarriers::gethei()
{
    return this->height;
}


//金币
// coin 类的构造函数，用于初始化硬币的位置、尺寸和图像
coin::coin(int x, int y, int wid, int hei) : Bossbarriers(x, y, wid, hei)
{
    this->pic.load(coin_1); // 加载硬币的图像
}

// 获取硬币的 QPixmap 图像
QPixmap coin::getpic()
{
    return this->pic; // 返回硬币的图像
}

// 硬币的碰撞检测函数
bool coin::collided(int lx, int ly, int wid, int hei)
{
    // 创建一个矩形表示硬币当前位置和尺寸
    QRect rect_1(this->getx(), this->gety(), this->getwid() - 20, this->gethei() + 20);
    // 创建一个矩形表示其他对象的位置和尺寸
    QRect rect_2(lx, ly, wid, hei);
    // 检查两个矩形是否相交（即是否发生碰撞）
    return rect_1.intersects(rect_2);
}

// 移动硬币的位置
void coin::move()
{
    // 水平向左移动硬币
    this->setx(this->getx() - 5);
}

// 检查硬币是否已经离开屏幕
bool coin::done()
{
    // 如果硬币的 x 坐标小于 -10，认为它已经离开屏幕
    if (this->getx() < -10)
    {
        return true; // 已离开屏幕
    }
    else
    {
        return false; // 未离开屏幕
    }
}

//红心
redheart::redheart(int x, int y, int wid, int hei):Bossbarriers(x,y,wid,hei)
{
    this->pic.load(redhea);
}

QPixmap redheart::getpic()
{
    return this->pic;
}

bool redheart::collided(int lx, int ly, int wid, int hei)
{
    QRect rect_1(this->getx(),this->gety(),this->getwid()-20,this->gethei()+20);
    QRect rect_2(lx,ly,wid,hei);
    return rect_1.intersects(rect_2);    //返回两个矩形是否发生碰撞的结果
}


void redheart::move()
{
    this->setx(this->getx()-5);
}

bool redheart::done()
{
    if(this->getx()<-10)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


//飞箭
farrow::farrow(int x, int y, int wid, int hei):Bossbarriers(x,y,wid,hei)
{
    this->pic.load(fj);

}

QPixmap farrow::getpic()
{
    return this->pic;
}


bool farrow::collided(int lx, int ly, int wid, int hei)
{
    QRect rect_1(this->getx(),this->gety(),this->getwid(),this->gethei());
    QRect rect_2(lx,ly,wid,hei);
    return rect_1.intersects(rect_2);    //返回两个矩形是否发生碰撞的结果

}

void farrow::move()
{
    this->setx(this->getx()-10);
}
bool farrow::done()
{
    if(this->getx()<-10)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
//飞镖

fbbb::fbbb(int x, int y, int wid, int hei):Bossbarriers(x,y,wid,hei)
{
    this->pic.load(fb);

}

QPixmap fbbb::getpic()
{
    return this->pic;
}

bool fbbb::collided(int lx, int ly, int wid, int hei)
{
    QRect rect_1(this->getx(),this->gety(),this->getwid()-100,this->gethei()-20);
    QRect rect_2(lx,ly,wid,hei);
    return rect_1.intersects(rect_2);    //返回两个矩形是否发生碰撞的结果

}

void fbbb::move()
{
    this->setx(this->getx()-10);
}
bool fbbb::done()
{
    if(this->getx()<-10)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

//子弹
bullet::bullet(int x, int y, int wid, int hei):Bossbarriers(x,y,wid,hei)
{
    this->pic.load(bullet_pic);

}

QPixmap bullet::getpic()
{
    return this->pic;
}

bool bullet::collided(int lx, int ly, int wid, int hei)
{
    QRect rect_1(this->getx(),this->gety(),this->getwid()-100,this->gethei()-20);
    QRect rect_2(lx,ly,wid,hei);
    return rect_1.intersects(rect_2);    //返回两个矩形是否发生碰撞的结果

}

void bullet::move()
{
    this->setx(this->getx()+10);
}
bool bullet::done()
{
    if(this->getx()<+10)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}


//普攻
pug::pug(int x, int y, int wid, int hei) : Bossbarriers(x, y, wid, hei)
{
    this->pic.load(pug_); // 加载普攻的图像
}

// 获取普攻的 QPixmap 图像
QPixmap pug::getpic()
{
    return this->pic; // 返回普攻的图像
}

// 普攻的碰撞检测函数
bool pug::collided(int lx, int ly, int wid, int hei)
{
    // 创建一个矩形表示普攻当前位置和尺寸
    QRect rect_1(this->getx(), this->gety(), this->getwid(), this->gethei());
    // 创建一个矩形表示其他对象的位置和尺寸
    QRect rect_2(lx, ly, wid, hei);
    // 检查两个矩形是否相交（即是否发生碰撞）
    return rect_1.intersects(rect_2);
}

// 移动普攻的位置
void pug::move()
{
    // 水平向左移动普攻
    this->setx(this->getx() - 10);
}

// 检查普攻是否已经离开屏幕
bool pug::done()
{
    // 如果普攻的 x 坐标小于 -210，认为它已经离开屏幕
    if (this->getx() < -210)
    {
        return true; // 已离开屏幕
    }
    else
    {
        return false; // 未离开屏幕
    }
}



//技能1
jin1::jin1(int x, int y, int wid, int hei) : Bossbarriers(x, y, wid, hei)
{
    // 加载技能1的图像序列，用于动画效果
    for(int i = 0; i < 4; i++)
    {
        pic[i].load(QString(":/res/1%1.png").arg(i + 1));
    }
    this->speed = 0; // 初始化技能移动速度
}

// 获取技能1当前应显示的 QPixmap 图像
QPixmap jin1::getpic()
{
    return this->pic[curji]; // 返回当前帧的图像
}

// 技能1的碰撞检测函数
bool jin1::collided(int lx, int ly, int wid, int hei)
{
    // 创建一个矩形表示技能1当前位置和尺寸
    QRect rect_1(this->getx(), this->gety(), this->getwid(), this->gethei());
    // 创建一个矩形表示其他对象的位置和尺寸
    QRect rect_2(lx, ly, wid, hei);
    // 检查两个矩形是否相交（即是否发生碰撞）
    return rect_1.intersects(rect_2);
}

// 移动技能1的位置
void jin1::move()
{
    // 根据技能速度移动技能1
    this->setx(this->getx() - 3 - speed);
}

// 检查技能1是否已经离开屏幕
bool jin1::done()
{
    // 如果技能1的 x 坐标小于 -10，认为它已经离开屏幕
    if (this->getx() < -10)
    {
        return true; // 已离开屏幕
    }
    else
    {
        return false; // 未离开屏幕
    }
}


// 'jin2' 类的构造函数，用于初始化技能2的位置、尺寸和图像序列
jin2::jin2(int x, int y, int wid, int hei) : Bossbarriers(x, y, wid, hei)
{
    // 加载技能2的图像序列，用于动画效果
    for(int i = 0; i < 4; i++)
    {
        pic[i].load(QString(":/res/2%1.png").arg(i + 1));
    }
    // 初始化移动方向的标志
    zuo = 1; // 初始向左移动
    shang = 0; // 不向上移动
    you = 0; // 不向右移动
    xia = 0; // 不向下移动
}

// 获取技能2当前应显示的 QPixmap 图像
QPixmap jin2::getpic()
{
    return this->pic[curji]; // 返回当前帧的图像
}

// 技能2的碰撞检测函数
bool jin2::collided(int lx, int ly, int wid, int hei)
{
    // 创建一个矩形表示技能2当前位置和尺寸
    QRect rect_1(this->getx(), this->gety(), this->getwid(), this->gethei());
    // 创建一个矩形表示其他对象的位置和尺寸
    QRect rect_2(lx, ly, wid, hei);
    // 检查两个矩形是否相交（即是否发生碰撞）
    return rect_1.intersects(rect_2);
}

// 移动技能2的位置
void jin2::move()
{
    // 根据当前的移动方向标志移动技能2
    if (zuo)
    {
        this->setx(this->getx() - 15); // 向左移动
    }
    else if (shang)
    {
        this->sety(this->gety() - 15); // 向上移动
    }
    else if (you)
    {
        this->setx(this->getx() + 15); // 向右移动
    }
    else if (xia)
    {
        this->sety(this->gety() + 15); // 向下移动
    }

    // 检查并更新移动方向
    if (zuo && this->getx() < -10)
    {
        zuo = 0; shang = 1; // 从向左改为向上移动
    }
    else if (shang && this->gety() < -10)
    {
        shang = 0; you = 1; // 从向上改为向右移动
    }
    else if (you && this->getx() > 650)
    {
        you = 0; xia = 1; // 从向右改为向下移动
    }
    else if (xia && this->gety() > 350)
    {
        xia = 0; zuo = 1; // 从向下改为向左移动
    }
}

// 检查技能2是否已经离开屏幕
bool jin2::done()
{
    // 如果技能2的 x 坐标小于 -100，认为它已经离开屏幕
    if (this->getx() < -100)
    {
        return true; // 已离开屏幕
    }
    else
    {
        return false; // 未离开屏幕
    }
}
