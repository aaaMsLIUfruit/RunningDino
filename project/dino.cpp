#include "dino.h"

Dino::Dino()
{

    run_img[0].load(QString(":/res/DINO_RUN1.png"));
    run_img[1].load(QString(":/res/DINO_RUN2.png"));
    jump_img.load(JUMP_PATH);
    current_run_img=0;
    run_Timer.setInterval(RUN_INTERVAL);
    QObject::connect(&run_Timer,&QTimer::timeout,[this]()
    {
        current_run_img=(++current_run_img)%2;
    });
    jump_Timer.setInterval(JUMP_DURATION);
    jump_Timer.setSingleShot(true);

    fall_speed=INIT_FALL_SPEED;
    jump_once=false;
    jump_twice=false;
    dino_Rect.setWidth(51);        //初始化角色边框
    dino_Rect.setHeight(102);
    dino_Rect.moveTo(x+17,y+8);
}

//根据位置获取角色状态图片
QPixmap Dino::getImg()
{
    if(y>=DINO_ON_GROUNG_POS_Y){
        return run_img[current_run_img];
    }
    else return jump_img;
}

void Dino::jump(){
    if(y==DINO_ON_GROUNG_POS_Y){
        jump_once=false;
        jump_twice=false;
        fall_speed=INIT_FALL_SPEED;
    }
    if(jump_twice||(jump_Timer.remainingTime()>200&&jump_Timer.isActive())){
        return;
    }
    if(y==DINO_ON_GROUNG_POS_Y)
    {
        jump_Timer.start();
        jump_once=true;
    }
    if(y<DINO_ON_GROUNG_POS_Y&&!jump_twice)
    {
        jump_Timer.start();
        jump_twice=true;
    }
}

void Dino::updatePositionY(){
    if(jump_Timer.isActive()){
        y-=jump_Timer.remainingTime()/45;
    }
    else{
        fall_speed+=0.03;              //下落加速度
        y+=fall_speed;
    }
    if(y>=DINO_ON_GROUNG_POS_Y)
    {
        y=DINO_ON_GROUNG_POS_Y;
    }
    dino_Rect.moveTo(x+17,y+8);
}
