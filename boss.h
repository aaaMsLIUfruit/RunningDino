#ifndef BOSS_H
#define BOSS_H

#include <QObject>
#include <QWidget>
#include<QTimer>

namespace Ui {
class Boss;
}

class Boss : public QWidget
{
    Q_OBJECT

public:

    explicit Boss(QWidget *parent = nullptr);

    int hp;
    int maxhp;
    bool live;
    bool ceshi;
    QPixmap jingzhi[4];
    QPixmap pugong[2];
    QPixmap jineng1[2];
    QPixmap jineng2[2];



    QTimer action;
    QTimer do_action;
    QTimer ji_action;
    QTimer hpp_Timer;

    int x;
    int y;
    int wid;
    int hei;
    bool jingzhi_;
    bool pugong_;
    bool jineng1_;
    bool jineng2_;
    void reducehp();
    int getbaifenzhihp();
    QPixmap getpic();
    int curjing;
    int curpu;
    int curji1;
    int curji2;

    //技能部分
    void do_pugong();
    void do_jingzhi();
    void do_jineng1();
    void do_jineng2();


    void die();
    ~Boss();


private:
    Ui::Boss *ui;
};

#endif // BOSS_H
