#include "dino.h"
#include <QDebug>
// Dino 类的构造函数

Dino::Dino(QWidget *parent){

    // 设置 Dino 的初始角色
//    setCharacter("经典小恐龙");
//    run_img[0].load(QString(":/res/DINO_RUN1.png"));
//    run_img[1].load(QString(":/res/DINO_RUN2.png"));
//    jump_img.load(JUMP_PATH);
//    current_run_img = 0;
//    run_Timer.setInterval(RUN_INTERVAL);
//    QObject::connect(&run_Timer, &QTimer::timeout, [this]() {
//        current_run_img = (++current_run_img) % 2;
//    });
//    jump_Timer.setInterval(JUMP_DURATION);
//    jump_Timer.setSingleShot(true);

    // 初始化跳跃和下落的参数
    fall_speed = INIT_FALL_SPEED;
    jump_once = false;
    jump_twice = false;

    // 初始化 Dino 的碰撞矩形大小和位置
    dino_Rect.setWidth(51);
    dino_Rect.setHeight(102);
    dino_Rect.moveTo(x+17, y+8);

    // 初始化 GIF 动画和其显示控件
    dinoGif = new QMovie(parent);
    dinoLabel = new QLabel(parent);
    dinoLabel->setGeometry(QRect(x, y, 100, 108));
    dinoLabel->show();
    // 默认隐藏 GIF 标签
    dinoLabel->raise();
    jumpSound = new QMediaPlayer(parent);
    setCharacter("经典小恐龙 free");
}

// 获取当前 Dino 的图像，基于其位置（跳跃或跑步）
QPixmap Dino::getImg() {


    if(chara=="经典小恐龙 free"){
        if (y >= DINO_ON_GROUNG_POS_Y) {
            // 当 Dino 在地面上时，返回跑步图像

            return dinorun_img[current_run_img];

        } else {
            // 当 Dino 在空中时，返回跳跃图像

            return dinojump_img;

        }
    }

   else if(chara=="超级马里奥 50coin"){
        if (y >= DINO_ON_GROUNG_POS_Y) {
            // 当 Dino 在地面上时，返回跑步图像

            return mariorun_img[current_run_img];

        } else {
            // 当 Dino 在空中时，返回跳跃图像

            return mariojump_img;
        }

   }
}






// Dino 的跳跃逻辑
void Dino::jump() {

    // 如果 Dino 在地面上，可以开始跳跃
    if (y == DINO_ON_GROUNG_POS_Y) {
        jump_once = false;
        jump_twice = false;
        fall_speed = INIT_FALL_SPEED;
    }

    // 控制双重跳跃的逻辑
    if (jump_twice || (jump_Timer.remainingTime() > 200 && jump_Timer.isActive())) {
        return;
    }

    // 开始跳跃动作
    if (y == DINO_ON_GROUNG_POS_Y) {
        jump_Timer.start();
        jump_once = true;
        jumpSound->play();// 播放跳跃音效
    }
    else if (y < DINO_ON_GROUNG_POS_Y && !jump_twice) {
        jump_Timer.start();
        jump_twice = true;
        jumpSound->play(); // 播放跳跃音效
    }
}

// 更新 Dino 的垂直位置
void Dino::updatePositionY() {

    // 控制跳跃的动态
    if (jump_Timer.isActive())
    {
        y -= jump_Timer.remainingTime() / 45;
    }
    // 控制下落的动态
    else
    {
        fall_speed += 0.03;
        y += fall_speed;
    }

    // 确保 Dino 不会穿过地面
    if (y >= DINO_ON_GROUNG_POS_Y)
    {
        y = DINO_ON_GROUNG_POS_Y;
    }

    // 更新 Dino 的碰撞矩形位置
    dino_Rect.moveTo(x+17, y+8);
    dinoLabel->move(x, y);
}

// 设置 Dino 的角色
void Dino::setCharacter(const QString &character) {

    chara=character;

    // 如果路径是 GIF 动画
    if (character=="说的道理 50coin")
    {
        dinoGif=new QMovie(":/res/Daoli.gif");
        dinoLabel->setMovie(dinoGif);
        dinoLabel->show();
        dinoGif->setScaledSize(dinoLabel->size());
        dinoGif->start();
        dinoLabel->update();
        run_Timer.setInterval(RUN_INTERVAL);
        jump_Timer.setInterval(JUMP_DURATION);
        jump_Timer.setSingleShot(true);

    }

    else if (character=="科比 50coin")
    {
        dinoGif=new QMovie(":/res/kobe.gif");
        dinoLabel->setMovie(dinoGif);
        dinoLabel->show();
        dinoGif->setScaledSize(dinoLabel->size());
        dinoGif->start();
        dinoLabel->update();
        run_Timer.setInterval(RUN_INTERVAL);
        jump_Timer.setInterval(JUMP_DURATION);
        jump_Timer.setSingleShot(true);

    }


    else if (character == "经典小恐龙 free")
    {
        dinoLabel->hide(); // 隐藏 GIF 动画显示控件

        // 加载静态图片
        dinorun_img[0].load(QString(":/res/DINO_RUN1.png"));
        dinorun_img[1].load(QString(":/res/DINO_RUN2.png"));
        dinojump_img.load(JUMP_PATH);
        current_run_img = 0;
        run_Timer.setInterval(RUN_INTERVAL);
        QObject::connect(&run_Timer, &QTimer::timeout, [this]() {
            current_run_img = (++current_run_img) % 2;
        });
        jump_Timer.setInterval(JUMP_DURATION);
        jump_Timer.setSingleShot(true);

        //初始化声音
//        jumpSound->setMedia(QUrl::fromLocalFile(":/res/JumpSound.wav"));

        windSound.setSource(QUrl::fromLocalFile(":/res/WindSound.mp3"));
        windSound.setVolume(50);
    }

    else if (character == "超级马里奥 50coin")
    {
        dinoLabel->hide(); // 隐藏 GIF 动画显示控件

        // 加载静态图片
        QPixmap mario1(":/res/Mario1.png");
        QPixmap mario2(":/res/Mario2.png");
        QPixmap mario3(":/res/Mario3.png");
        QPixmap mario4(":/res/Mario4.png");
        QPixmap mario5(":/res/Mario5.png");
        QPixmap mario6(":/res/Mario6.png");

        //调整人物大小
        mariorun_img[0] = mario1.scaled(100,110);
        mariorun_img[1] = mario2.scaled(100,110);
        mariorun_img[2] = mario3.scaled(100,110);
        mariorun_img[3] = mario4.scaled(100,110);
        mariorun_img[4] = mario5.scaled(100,110);
        mariorun_img[5] = mario6.scaled(100,110);
        current_run_img = 0;
        run_Timer.setInterval(RUN_INTERVAL);
        QObject::connect(&run_Timer, &QTimer::timeout, [this]() {
             current_run_img = (current_run_img + 1) % 6;
        });
        jump_Timer.setInterval(JUMP_DURATION);
        jump_Timer.setSingleShot(true);

          //初始化声音
//        jumpSound->setMedia(QUrl::fromLocalFile(":/res/JumpSound.wav"));

        windSound.setSource(QUrl::fromLocalFile(":/res/WindSound.mp3"));
        windSound.setVolume(50);

    }
}


Dino::~Dino() {


}
