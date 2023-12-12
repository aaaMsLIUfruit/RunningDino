#ifndef BARRIERS_H
#define BARRIERS_H

#include <QPixmap>

//基类
class Barriers
{
public:
    Barriers();
    virtual void updatePosition()=0;
    virtual void updateBirdY()=0;
    virtual bool isOut()=0;
    virtual int collisionDetection(QRect)=0;           //碰撞检测情况处理超过两种，定义返回值为int
    virtual QPixmap getImg(int)=0;
public:
    int x,y;
    QPixmap img;
    QRect rect;
};

//派生类
class Cactus:public Barriers
{
public:
    Cactus();
    void updatePosition();
    void updateBirdY(){}
    bool isOut();
    int collisionDetection(QRect);
    QPixmap getImg(int);
public:
    QPixmap img2;
};

class Bird:public Barriers
{
public:
    Bird();
    void updatePosition();
    void updateBirdY();
    bool isOut();
    int collisionDetection(QRect);
    QPixmap getImg(int);
public:
    QPixmap img2;
    double t=0;       //作为余弦函数的时间变量
    double u;            //作为余弦函数的初相
};

class Yucha:public Barriers
{
public:
    Yucha();
    void updatePosition();
    void updateBirdY(){}
    bool isOut();
    int collisionDetection(QRect);
    QPixmap getImg(int);
public:
    QPixmap img2;
};

class Veget:public Barriers
{
public:
    Veget();
    void updatePosition();
    void updateBirdY(){}
    bool isOut();
    int collisionDetection(QRect);
    QPixmap getImg(int);
};

class Apple:public Barriers
{
public:
    Apple(int);
    void updatePosition();
    void updateBirdY(){}
    bool isOut();
    int collisionDetection(QRect);
    QPixmap getImg(int);
};

#endif // BARRIERS_H
