#ifndef BOSSBARRIERS_H
#define BOSSBARRIERS_H


#include<QPixmap>
#include<QTimer>
#include<QWidget>
#include<boss.h>

//障碍物类设置
class Bossbarriers:public QWidget
{
private:
    int x,y;
    int width,height;
public:
    Bossbarriers(int x,int y,int wid,int hei);
    int getx();
    int gety();
    void setx(int x);
    void sety(int y);
    int getwid();
    int gethei();

    int curji;
    int speed;
    QTimer jineng_Timer;
};

//派生忍币
class coin:public Bossbarriers
{
private:
    QPixmap pic;
public:
    int speed;
    coin(int x,int y,int wid,int hei);
    QPixmap getpic();
    bool ispengzhuang(int lx,int ly,int wid,int hei);
    //判断碰撞
    void move();//障碍移动
    bool done();//判断是不是过去了

};

//派生红心
class redheart:public Bossbarriers
{
private:
    QPixmap pic;
public:
    int speed;
    redheart(int x,int y,int wid,int hei);
    QPixmap getpic();
    bool ispengzhuang(int lx,int ly,int wid,int hei);
    //判断碰撞
    void move();//障碍移动
    bool done();//判断是不是过去了

};


//派生飞箭
class farrow:public Bossbarriers
{
private:
    QPixmap pic;
public:
    int speed;
    farrow(int x,int y,int wid,int hei);
    QPixmap getpic();
    bool ispengzhuang(int lx,int ly,int wid,int hei);
    //判断碰撞
    void move();//障碍移动
    bool done();//判断是不是过去了

};

//派生飞镖
class fbbb:public Bossbarriers
{
private:
    QPixmap pic;
public:
    int speed;
    fbbb(int x,int y,int wid,int hei);
    QPixmap getpic();
    bool ispengzhuang(int lx,int ly,int wid,int hei);
    //判断碰撞
    void move();//障碍移动
    bool done();//判断是不是过去了
};

//派生子弹
class bullet:public Bossbarriers
{
private:
    QPixmap pic;
public:
    int speed;
    bullet(int x,int y,int wid,int hei);
    QPixmap getpic();
    bool ispengzhuang(int lx,int ly,int wid,int hei);

    void move();
    bool done();

};

//派生普攻
class pug:public Bossbarriers
{
private:
    QPixmap pic;
public:
    int speed;
    pug(int x,int y,int wid,int hei);
    QPixmap getpic();
    bool ispengzhuang(int lx,int ly,int wid,int hei);
    //判断碰撞
    void move();//障碍移动
    bool done();//判断是不是过去了

};


//派生技能1
class jin1:public Bossbarriers
{
private:
    QPixmap pic[4];
public:
    int speed;
    jin1(int x,int y,int wid,int hei);
    QPixmap getpic();
    bool ispengzhuang(int lx,int ly,int wid,int hei);
    //判断碰撞
    void move();//障碍移动
    bool done();//判断是不是过去了

};

//派生技能2
class jin2:public Bossbarriers
{

private:
    QPixmap pic[4];

public:
    int speed;
    jin2(int x,int y,int wid,int hei);
    QPixmap getpic();
    bool ispengzhuang(int lx,int ly,int wid,int hei);
    //判断碰撞
    void move();//障碍移动
    bool done();//判断是不是过去了

    bool zuo;
    bool shang;
    bool you;
    bool xia;

};




#endif // BOSSBARRIERS_H
