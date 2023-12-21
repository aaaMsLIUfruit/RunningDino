#include "ground.h"
#include "config.h"


Ground::Ground()
{
    ground.load(GROUND_PATH);   //初始化加载地面对象
    ground_posX=-30;         //设置初始坐标
    ground_scroll_speed=SCENE_SCROLL_SPEED;
}
//计算坐标
void Ground::calculatePosition(){
    ground_posX-=ground_scroll_speed;
}
Grounds::Grounds()
{
    for(int i=0;i<10;i++){
        grounds[i].ground_posX+=132*i;
    }
}
void Grounds::calculatePositions(){
    for(int i=0;i<10;i++){
        grounds[i].calculatePosition();
        if(grounds[i].ground_posX<=-grounds[i].ground.width()){
            grounds[i].ground_posX+=132*9;
            distance+=5;
        }
    }
}
