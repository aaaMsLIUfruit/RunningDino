#include "barriers.h"
#include "config.h"
#include <QtMath>

#include <ctime>

Barriers::Barriers()
{

}

Cactus::Cactus()
{
    img.load(CACTUS_PATH);
    img2.load(CACTUS_PATH2);
    x=GAME_WIDTH;
    y=351;
    rect.setWidth(img.width()-10);
    rect.setHeight(img.height()-3);
    rect.moveTo(x+5,y+3);
}
void Cactus::updatePosition(){
    x-=SCENE_SCROLL_SPEED;
    rect.moveTo(x+5,y+3);
}
bool Cactus::isOut(){
    return x<-img.width();
}
int Cactus::collisionDetection(QRect r){
    if(rect.intersects(r)){
        return 1;
    }
    else
        return 0;
}
QPixmap Cactus::getImg(int i){
    if(i==0){
        return img;
    }
    else
        return img2;
}

Bird::Bird()
{
    img.load(BIRD_PATH);
    img2.load(BIRD_PATH2);
    x=GAME_WIDTH;
    srand((unsigned int)time(NULL));
    u=rand()%(10000);
    y=189+169*qCos(t/50+u);
    rect.setWidth(img.width()-23);
    rect.setHeight(img.height()-11);
    rect.moveTo(x+10,y+6);
}
void Bird::updatePosition(){
    x-=SCENE_SCROLL_SPEED;
    rect.moveTo(x+10,y+6);
}
void Bird::updateBirdY(){
    t+=1;
    y=189+169*qCos(t/50+u);
}
bool Bird::isOut(){
    return x<-img.width();
}
int Bird::collisionDetection(QRect r){
    if(rect.intersects(r)){
        return 1;
    }
    else
        return 0;
}
QPixmap Bird::getImg(int i){
    if(i==0){
        return img;
    }
    else
        return img2;
}

Yucha::Yucha()
{
    img.load(YUCHA_PATH);
    img2.load(YUCHA_PATH2);
    x=GAME_WIDTH;
    y=20;
    rect.setWidth(9);
    rect.setHeight(img.height());
    rect.moveTo(x+21,y);
}

void Yucha::updatePosition()
{
    x-=SCENE_SCROLL_SPEED;
    rect.moveTo(x+21,y);
}

bool Yucha::isOut()
{
    return x<-img.width();
}
int Yucha::collisionDetection(QRect r){
    if(rect.intersects(r)){
        return 1;
    }
    else
        return 0;
}
QPixmap Yucha::getImg(int i)
{
    if(i==0){
        return img;
    }
    else
        return img2;
}

Veget::Veget()
{
    img.load(LOLIPOP_PATH);
    x=GAME_WIDTH;
    y=rand()%(260)+40;
    rect.setWidth(img.width());
    rect.setHeight(img.height());
    rect.moveTo(x,y);
}

void Veget::updatePosition(){
    x-=SCENE_SCROLL_SPEED;
    rect.moveTo(x,y);
}
bool Veget::isOut(){
    return x<-img.width();
}

int Veget::collisionDetection(QRect r)
{
    if(rect.intersects(r)){
        return 2;
    }
    else
        return 0;
}

QPixmap Veget::getImg(int i)
{
    return img;
}

Apple::Apple(int i){
    img.load(COIN_PATH);
    x=GAME_WIDTH;
    if(i==1){
        x+=22;
        y=180;
    }
    if(i==2){
        y=rand()%240+50;
    }
    rect.setWidth(img.width());
    rect.setHeight(img.height());
    rect.moveTo(x,y);
}

void Apple::updatePosition()
{
    x-=SCENE_SCROLL_SPEED;
    rect.moveTo(x,y);
}

bool Apple::isOut()
{
    return x<-img.width();
}

int Apple::collisionDetection(QRect r)
{
    if(rect.intersects(r)){
        return 3;
    }
    else
        return 0;
}

QPixmap Apple::getImg(int i){
    return img;
}
