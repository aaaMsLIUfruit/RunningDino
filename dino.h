#ifndef DINO_H
#define DINO_H

#include <QPixmap>
#include <QTimer>
#include <QMovie>
#include <QLabel>
#include <QSoundEffect>
#include <QMediaPlayer>


#include "config.h"


class Dino: public QWidget
{
public:
    explicit Dino(QWidget *parent = nullptr);
    Dino();
    QPixmap getImg();
    void jump();               //跳跃
    void updatePositionY();    //更新Y轴坐标
    void setCharacter(const QString &Path); // 设置图片
    ~Dino();

public:
    QPixmap dinorun_img[2];  //小恐龙奔跑图片
    QPixmap dinojump_img;     //小恐龙跳跃图片
    QPixmap mariorun_img[6];  //马里奥奔跑图片
    QPixmap mariojump_img;    //马里奥跳跃图片
    QTimer run_Timer;       //奔跑图片切换计时器
    QTimer jump_Timer;      //跳跃时间计时器
    int x=100;                  //角色坐标
    int y=DINO_ON_GROUNG_POS_Y;
    int current_run_img;        //小恐龙奔跑图片下标
    int mcurrent_run_img;   //马里奥奔跑图片下标
    double fall_speed;     //下落速度
    bool jump_once;        //已经跳跃一次
    bool jump_twice;       //已经跳跃两次

    QRect dino_Rect;    //角色边框  用于碰撞检测
    QMovie *dinoGif;
    QLabel *dinoLabel;
    QString chara;
    QMediaPlayer *jumpSound;
    QSoundEffect windSound;


};

#endif // DINO_H
