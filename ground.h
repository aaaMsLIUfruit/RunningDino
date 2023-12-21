#ifndef GROUND_H
#define GROUND_H

#include <QPixmap>
#include <QRect>

//单张地图类
class Ground
{
public:
    Ground();
    void calculatePosition();   //计算坐标
public:
    QPixmap ground;   //地面图片对象
    int ground_posX;  //地面X坐标
    int ground_scroll_speed;
};

//地图类
class Grounds
{
public:
    Grounds();
    void calculatePositions();
public:
    Ground grounds[10];
    int distance;   //距离
};

#endif // GROUND_H
