#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPixmap>
#include <QPainter>
#include <QTimer>
#include <QMouseEvent>
#include <vector>
#include <QElapsedTimer>

#include "store.h"
#include "ground.h"
#include "introduction.h"
#include "dino.h"
#include "barriers.h"
#include "archive.h"
#include "home.h"
#include "bossmode.h"
#include "bossintro.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void initWindow();//初始化窗口
    void playAnimation();  //播放首页动画
    void paintEvent(QPaintEvent *event);  //绘图事件
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void playgame();   //开始游戏
    void gameover();   //游戏结束
    void updatePosition();   //更新坐标
    void collisionDetection(); //碰撞检测
    void sprint();          //角色冲刺 => 场景所有对象加速
    void addBarrier();      //添加障碍物

    std::vector<Barriers*>barriers;     //管理屏幕中的障碍物
    std::vector<Barriers*>::iterator it;

    QPixmap background;
    QTimer m_Timer;        //刷新屏幕计时器
    QTimer sprint_Timer;           //冲刺持续时间计时器
    QTimer sprint_interval_Timer;  //冲刺间隔时间计时器
    QTimer add_Barrier_interval_Timer; //生成障碍物计时器
    QTimer add_veget_intervai_Timer;   //生成兰纳罗间隔时间计时器
    QTimer protected_Timer;            //无敌时间
    QTimer jumpHome_Timer;      //首页动画计时器
    QElapsedTimer startgame_Timer;   //开始游戏计时器
    bool sprint_once;         //是否已经冲刺一次
    bool sprint_twice;        //是否已经冲刺两次
    bool wudi=false;     //开局无敌是否开启,默认关闭
    bool morecoin=false;   //更多金币是否开启,默认关闭
    int i;                    //障碍物类型
    int coin;           //金币
    int rec;               //纪录
    QString filename;           //存档

    Grounds grounds;  //地面对象

    Dino *dino;

    Home *home;  //首页界面
    Introduction *intro;   //游戏介绍窗口
    BossIntro *bossIntro;  //boss模式介绍界面
    Archive *arch;  //存档界面
    Store *store;  //商店界面
    Bossmode *bossmode; //打boss模式

    void initStartScreen();
    void showComponents();
    void showProtectedtime();
    void updateDinoCharacter(const QString &characterName);
    void updateBackground(const QString &backgroundName);
    void updateProp(const QString &propName);
    void quickupGame();

public slots:
    void updateCoin(const int &newCoinValue);

private slots:
    void switchToArchWindow();

    void on_start_clicked();

    void on_intro_clicked();

    void on_restart_clicked();

    void on_return_main_clicked();

    void on_store_clicked();

    void on_bossmode_clicked();

    void boss_closed();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
