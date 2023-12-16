#include "barriers.h"
#include "config.h"
#include <QtMath>

#include <ctime>

Barriers::Barriers()
{

}

Cactus::Cactus() {
    // 构造函数，初始化仙人掌对象
    img.load(CACTUS_PATH);  // 加载第一张图片
    img2.load(CACTUS_PATH2);  // 加载第二张图片
    x = GAME_WIDTH;  // 初始x位置设置为游戏窗口宽度，表示从右侧进入
    y = 351;  // 设置y坐标，表示仙人掌的垂直位置
    // 设置碰撞检测矩形的大小和位置
    rect.setWidth(img.width() - 10);
    rect.setHeight(img.height() - 3);
    rect.moveTo(x + 5, y + 3);

}

void Cactus::updatePosition() {
    // 更新仙人掌的位置
    x -= SCENE_SCROLL_SPEED;  // 根据场景滚动速度向左移动
    rect.moveTo(x + 5, y + 3);  // 更新碰撞检测矩形的位置

}

bool Cactus::isOut() {
    // 检查仙人掌是否移出屏幕
    return x < -img.width();  // 如果仙人掌完全离开屏幕，返回true

}

int Cactus::collisionDetection(QRect r) {
    // 碰撞检测函数
    if (rect.intersects(r)) {  // 如果碰撞矩形与传入的矩形相交
        return 1;  // 发生碰撞
    }
    else
        return 0;  // 无碰撞

}

QPixmap Cactus::getImg(int i) {
    // 获取仙人掌的图像
    if (i == 0) {
        return img;  // 返回第一张图片
    }
    else
        return img2;  // 返回第二张图片

}

Bird::Bird() {
    // 构造函数，初始化鸟对象

    img.load(BIRD_PATH);  // 加载第一张图片
    img2.load(BIRD_PATH2);  // 加载第二张图片
    x = GAME_WIDTH;  // 初始x位置设置为游戏窗口宽度，表示从右侧进入
    srand((unsigned int)time(NULL));  // 设置随机种子

    u = rand() % (10000);  // 随机值，用于计算y坐标
    y = 189 + 169 * qCos(t / 50 + u);  // 根据正弦波形设置y坐标
    // 设置碰撞检测矩形的大小和位置
    rect.setWidth(img.width() - 23);
    rect.setHeight(img.height() - 11);
    rect.moveTo(x + 10, y + 6);

}

void Bird::updatePosition() {
    // 更新鸟的位置
    x -= SCENE_SCROLL_SPEED;  // 根据场景滚动速度向左移动
    rect.moveTo(x + 10, y + 6);  // 更新碰撞检测矩形的位置
}

void Bird::updateBirdY() {
    // 更新鸟的垂直位置
    t += 1;  // 增加时间参数
    y = 189 + 169 * qCos(t / 50 + u);  // 根据正弦波形重新计算y坐标
}

bool Bird::isOut() {
    // 检查鸟是否移出屏幕
    return x < -img.width();  // 如果鸟完全离开屏幕，返回true
}

int Bird::collisionDetection(QRect r) {
    // 碰撞检测函数
    if (rect.intersects(r)) {  // 如果碰撞矩形与传入的矩形相交
        return 1;  // 发生碰撞
    }
    else
        return 0;  // 无碰撞
}

QPixmap Bird::getImg(int i) {
    // 获取鸟的图像
    if (i == 0) {
        return img;  // 返回第一张图片
    }
    else
        return img2;  // 返回第二张图片
}


Yucha::Yucha() {

    // 构造函数，初始化余茶对象
    img.load(YUCHA_PATH);  // 加载第一张图片
    img2.load(YUCHA_PATH2);  // 加载第二张图片
    x = GAME_WIDTH;  // 初始x位置设置为游戏窗口宽度，表示从右侧进入
    y = 20;  // 设置y坐标，表示余茶的垂直位置
    // 设置碰撞检测矩形的大小和位置
    rect.setWidth(9);  // 设置宽度为9
    rect.setHeight(img.height());  // 设置高度为图片的高度
    rect.moveTo(x + 21, y);  // 设置碰撞矩形的位置

}

void Yucha::updatePosition() {
    // 更新余茶的位置
    x -= SCENE_SCROLL_SPEED;  // 根据场景滚动速度向左移动
    rect.moveTo(x + 21, y);  // 更新碰撞检测矩形的位置
}

bool Yucha::isOut() {
    // 检查余茶是否移出屏幕
    return x < -img.width();  // 如果余茶完全离开屏幕，返回true
}

int Yucha::collisionDetection(QRect r) {
    // 碰撞检测函数
    if (rect.intersects(r)) {  // 如果碰撞矩形与传入的矩形相交
        return 1;  // 发生碰撞
    }

    else
        return 0;  // 无碰撞

}

QPixmap Yucha::getImg(int i) {
    // 获取余茶的图像
    if (i == 0) {
        return img;  // 返回第一张图片
    }

    else
        return img2;  // 返回第二张图片
}


Veget::Veget() {
    // 构造函数，初始化棒棒糖对象
    img.load(LOLIPOP_PATH);  // 加载棒棒糖图片
    x = GAME_WIDTH;  // 初始x位置设置为游戏窗口宽度，表示从右侧进入
    y = rand() % (260) + 40;  // 在一定范围内随机生成y坐标
    // 设置碰撞检测矩形的大小和位置
    rect.setWidth(img.width());  // 设置宽度为图片的宽度
    rect.setHeight(img.height());  // 设置高度为图片的高度
    rect.moveTo(x, y);  // 设置碰撞矩形的位置
}

void Veget::updatePosition() {
    // 更新棒棒糖的位置
    x -= SCENE_SCROLL_SPEED;  // 根据场景滚动速度向左移动
    rect.moveTo(x, y);  // 更新碰撞检测矩形的位置
}

bool Veget::isOut() {
    // 检查棒棒糖是否移出屏幕
    return x < -img.width();  // 如果棒棒糖完全离开屏幕，返回true
}

int Veget::collisionDetection(QRect r) {
    // 碰撞检测函数
    if (rect.intersects(r)) {  // 如果碰撞矩形与传入的矩形相交
        return 2;  // 发生碰撞，返回2表示特殊的棒棒糖碰撞
    }
    else
        return 0;  // 无碰撞
}

QPixmap Veget::getImg(int) {
    // 获取棒棒糖的图像
    return img;  // 因为只有一张图像，直接返回
}


Apple::Apple(int i) {
    // 构造函数，初始化金币对象
    img.load(COIN_PATH);  // 加载金币图片
    x = GAME_WIDTH;  // 初始x位置设置为游戏窗口宽度，表示从右侧进入
    if (i == 1) {
        x += 22;  // 根据传入的参数调整x坐标
        y = 180;  // 设置固定的y坐标
    }
    if (i == 2) {
        y = rand() % 240 + 50;  // 在一定范围内随机生成y坐标
    }
    // 设置碰撞检测矩形的大小和位置
    rect.setWidth(img.width());  // 设置宽度为图片的宽度
    rect.setHeight(img.height());  // 设置高度为图片的高度
    rect.moveTo(x, y);  // 设置碰撞矩形的位置
}

void Apple::updatePosition() {
    // 更新金币的位置
    x -= SCENE_SCROLL_SPEED;  // 根据场景滚动速度向左移动
    rect.moveTo(x, y);  // 更新碰撞检测矩形的位置
}

bool Apple::isOut() {
    // 检查金币是否移出屏幕
    return x < -img.width();  // 如果金币完全离开屏幕，返回true
}

int Apple::collisionDetection(QRect r) {
    // 碰撞检测函数
    if (rect.intersects(r)) {  // 如果碰撞矩形与传入的矩形相交
        return 3;  // 发生碰撞，返回3表示金币碰撞
    }
    else
        return 0;  // 无碰撞
}

QPixmap Apple::getImg(int) {
    // 获取金币的图像
    return img;  // 因为只有一张图像，直接返回
}

