#ifndef CONFIG_H
#define CONFIG_H

#define GAME_WIDTH 1000//宽度
#define GAME_HEIGHT 524//高度
#define GAME_TITLE "DinoRun"

#define GAME_RES_PATH "./img.rcc"            //rcc文件
#define GAME_ICON ":/res/icon.ico"           //游戏图标
#define BACKGROUND_PATH ":/res/background.png"   //背景图片路径
#define GROUND_PATH ":/res/Land.png"           //地面图片路径
#define JUMP_PATH ":/res/DINO_JUMP.png"                //跳跃图片路径
#define CACTUS_PATH ":/res/CACTUS_3.png"         //仙人掌
#define CACTUS_PATH2 ":/res/CACTUS_4.png"
#define BIRD_PATH ":/res/BIRD_DOWN.png"     //鸟
#define BIRD_PATH2 ":/res/BIRD_UP.png"
#define YUCHA_PATH ":/res/yucha.png"               //鱼叉
#define YUCHA_PATH2 ":/res/yucha2.png"
#define LOLIPOP_PATH ":res/lolipop.png"             //棒棒糖
#define APPLE_PATH ":/res/apple.png"               //苹果

#define SCENE_SCROLL_SPEED 3     //场景移动速度
#define GAME_RATE 8              //屏幕刷新间隔
#define RUN_INTERVAL 70          //奔跑图片刷新间隔
#define INIT_FALL_SPEED 3        //初始下落速度
#define DINO_ON_GROUNG_POS_Y 298   //角色位于地面上的Y轴坐标

#define JUMP_DURATION 380           //跳跃持续时间
#define SPRINT_DURATION 250         //冲刺持续时间
#define SPRINT_INTERVAL 1600        //冲刺间隔时间
#define ADD_BARRIER_INTERVAL 1300   //生成障碍物间隔时间
#define ADD_LOLIPOP_INTERVAL 16000    //生成棒棒糖间隔时间
#define PROTECTED_DURATION 5000     //无敌时间

#endif // CONFIG_H
