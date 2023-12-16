#include "dino.h"
#include <QDebug>
// Dino 类的构造函数

Dino::Dino() {

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
    dinoGif = new QMovie(this);
    dinoLabel = new QLabel(this);
    dinoLabel->setGeometry(QRect(x, y, 100, 108));
    dinoLabel->hide();
    // 默认隐藏 GIF 标签
    dinoLabel->raise();

    setCharacter("经典小恐龙");
}

// 获取当前 Dino 的图像，基于其位置（跳跃或跑步）
QPixmap Dino::getImg() {

    if (y >= DINO_ON_GROUNG_POS_Y) {
        // 当 Dino 在地面上时，返回跑步图像

        return run_img[current_run_img];
    } else {// 当 Dino 在空中时，返回跳跃图像

        return jump_img;
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
    } else if (y < DINO_ON_GROUNG_POS_Y && !jump_twice) {
        jump_Timer.start();
        jump_twice = true;
    }
}

// 更新 Dino 的垂直位置
void Dino::updatePositionY() {
    // 控制跳跃的动态
    if (jump_Timer.isActive()) {
        y -= jump_Timer.remainingTime() / 45;
    } else {
        // 控制下落的动态
        fall_speed += 0.03;
        y += fall_speed;
    }

    // 确保 Dino 不会穿过地面
    if (y >= DINO_ON_GROUNG_POS_Y) {
        y = DINO_ON_GROUNG_POS_Y;
    }

    // 更新 Dino 的碰撞矩形位置
    dino_Rect.moveTo(x+17, y+8);
    dinoLabel->move(x, y);
}

// 设置 Dino 的角色
void Dino::setCharacter(const QString &character) {

    // 如果路径是 GIF 动画
    if (character=="说的道理") {
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

    else {
        // 如果路径是静态图片
        if (character == "经典小恐龙") {
            dinoLabel->hide(); // 隐藏 GIF 动画显示控件

            // 加载静态图片
            run_img[0].load(QString(":/res/DINO_RUN1.png"));
            run_img[1].load(QString(":/res/DINO_RUN2.png"));
            jump_img.load(JUMP_PATH);
            current_run_img = 0;
            run_Timer.setInterval(RUN_INTERVAL);
            QObject::connect(&run_Timer, &QTimer::timeout, [this]() {
                current_run_img = (++current_run_img) % 2;
            });
            jump_Timer.setInterval(JUMP_DURATION);
            jump_Timer.setSingleShot(true);
        }
    }
}
