#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QIcon>
#include <QKeyEvent>
#include <ctime>
#include <QFontDatabase>
#include <QString>
#include<QScreen>
#include<QStyle>

#include "config.h"
#include "dino.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->start->hide();
    ui->intro->hide();
    ui->store->hide();

    // 创建并展示存档界面
    arch = new Archive(this);
    arch->show();

    // 当存档界面关闭时，进行相应的处理
    connect(arch, &Archive::aboutToClose, [=]() {
    // 存档读取完成
        coin = arch->c;
        rec = arch->dis;
        filename = arch->filename;
        this->setFocus();
        arch->loadSettings(filename, "coin", coin);
        arch->loadSettings(filename, "record", rec);
        // 初始化开始界面
        initStartScreen();
        update();
    });

    initWindow();    //初始化窗口
}

MainWindow::~MainWindow()
{
    delete ui;
}

//初始化窗口
void MainWindow::initWindow(){
    setFixedSize(GAME_WIDTH,GAME_HEIGHT);  //大小
    setWindowTitle(GAME_TITLE);            //标题
    setWindowIcon(QIcon(GAME_ICON));       //图标
    background.load(BACKGROUND_PATH);    //加载背景
    update();

    int fontId=QFontDatabase::addApplicationFont(QStringLiteral(":/res/ark-pixel-12px-monospaced-zh_cn.ttf"));   //导入字体文件
    QStringList fontFamilies=QFontDatabase::applicationFontFamilies(fontId);
    QFont font;
    font.setFamily(fontFamilies[0]);
    ui->start->setFont(font);
    ui->intro->setFont(font);
    ui->store->setFont(font);
    ui->restart->setFont(font);
    ui->return_main->setFont(font);
    ui->coin->setFont(font);
    ui->distance->setFont(font);
    ui->over_score->setFont(font);
    ui->over_distance->setFont(font);
    ui->game_over->setFont(font);
    ui->record->setFont(font);

    ui->start->setGeometry(390,140,ui->start->width(),ui->start->height());      //大小
    ui->intro->setGeometry(390,260,ui->intro->width(),ui->intro->height());

    ui->start->setFocusPolicy(Qt::NoFocus);
    ui->intro->setFocusPolicy(Qt::NoFocus);
    ui->store->setFocusPolicy(Qt::NoFocus);
    ui->restart->setFocusPolicy(Qt::NoFocus);
    ui->return_main->setFocusPolicy(Qt::NoFocus);

    ui->coin->hide();
    ui->distance->hide();
    ui->groupBox->hide();
    ui->record->hide();

    m_Timer.setInterval(GAME_RATE);                    //主定时器设置
    sprint_Timer.setInterval(SPRINT_DURATION);         //冲刺定时器设置
    sprint_Timer.setSingleShot(true);
    sprint_interval_Timer.setInterval(SPRINT_INTERVAL);
    sprint_interval_Timer.setSingleShot(true);
    add_Barrier_interval_Timer.setInterval(ADD_BARRIER_INTERVAL); //障碍物计时器设置
    add_veget_intervai_Timer.setInterval(ADD_LOLIPOP_INTERVAL);     //棒棒糖计时器设置
    add_veget_intervai_Timer.setSingleShot(true);
    protected_Timer.setInterval(PROTECTED_DURATION);
    protected_Timer.setSingleShot(true);
    dino.y=DINO_ON_GROUNG_POS_Y;

    connect(&m_Timer,&QTimer::timeout,[=](){
        updatePosition();    //更新坐标
        collisionDetection();  //碰撞检测
        ui->coin->setText("Coin: "+QString::number(coin));   //更新金币数
        ui->distance->setText("Distance: "+QString::number(grounds.distance)+" m");
        ui->record->setText("Record: "+QString::number(rec)+" m");
        if(grounds.distance>rec){
            ui->record->setText("Record: "+QString::number(grounds.distance)+" m");
        }
        update();          //刷新屏幕
    });
    connect(&add_Barrier_interval_Timer,&QTimer::timeout,[=](){
        addBarrier();
    });

    grounds.distance=0;
    ui->coin->setText("Coin: "+QString::number(coin));
    ui->distance->setText("Distance: "+QString::number(grounds.distance)+" m");
    ui->record->setText("Record: "+QString::number(rec)+" m");

    sprint_once=false;
    sprint_twice=false;
}


void MainWindow::paintEvent(QPaintEvent *){                                  ////////paintEvent             //////////Event
    QPainter painter(this);
    painter.drawPixmap(0,0,background);    //绘制背景
    for(int i=0;i<9;i++){               //绘制地面
        painter.drawPixmap(grounds.grounds[i].ground_posX,356,grounds.grounds[i].ground);
    }
    painter.drawPixmap(dino.x,dino.y,dino.getImg());
    for(auto& barr:barriers)            //绘制障碍物
    {
        if(protected_Timer.isActive()){
            painter.drawPixmap(barr->x,barr->y,barr->getImg(1));
        }
        else{
            painter.drawPixmap(barr->x,barr->y,barr->getImg(0));
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event){                                 /////////keyPressEvent
    QKeyEvent *key=(QKeyEvent*) event;
    if(key->key()==Qt::Key_Space){                     //空格键跳跃
        dino.jump();
    }
    if(key->key()==Qt::Key_Shift){                     //shift键冲刺
        sprint();
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event){                             /////////mousePressEvent
    if(event->button()==Qt::LeftButton){
        dino.jump();
    }
    if(event->button()==Qt::RightButton){
        sprint();
    }
}


void MainWindow::playgame(){                                                                                      /////////playgame & gameover
    grounds.distance=0;
    dino.current_run_img=0;
    ui->coin->show();
    ui->distance->show();
    ui->record->show();
    m_Timer.start();            //启动计时器
    dino.run_Timer.start();
    add_Barrier_interval_Timer.start();
}

void MainWindow::gameover(){
    m_Timer.stop();
    sprint_Timer.stop();
    sprint_interval_Timer.stop();
    add_Barrier_interval_Timer.stop();
    add_veget_intervai_Timer.stop();
    dino.run_Timer.stop();
    protected_Timer.stop();
    ui->groupBox->setGeometry(330,0,ui->groupBox->width(),ui->groupBox->height());
    ui->over_score->setText("Coin: "+QString::number(coin));
    ui->over_distance->setText("Distance: "+QString::number(grounds.distance)+" m");
    arch->saveSettings(filename,"coin",coin);
    if(grounds.distance>rec){
        arch->saveSettings(filename,"record",grounds.distance);
    }
    QDateTime dateTime(QDateTime::currentDateTime());
    QString qStr = dateTime.toString("yyyy-MM-dd hh:mm:ss ddd");
    arch->saveSettings(filename,"time",qStr);
    ui->groupBox->show();
    update();
}


void MainWindow::updatePosition(){           //更新对象坐标
    grounds.calculatePositions();
    for(it=barriers.begin();it!=barriers.end();){
        if((*it)->isOut()){
            it=barriers.erase(it);
        }
        else{
            (*it)->updatePosition();
            (*it)->updateBirdY();     //对象为鸟，则更新Y坐标；对象不是鸟，则执行空函数
            it++;
        }
    }
    dino.updatePositionY();
    if(this->sprint_Timer.isActive()){
        grounds.calculatePositions();
        grounds.calculatePositions();
        for(auto& barr:barriers)
        {
            barr->updatePosition();
            barr->updatePosition();
        }
    }
}

void MainWindow::collisionDetection(){
    int i=0;
    for(it=barriers.begin();it!=barriers.end();){
        i=(*it)->collisionDetection(dino.dino_Rect);
        switch (i) {
        case 0:                       //无碰撞
            it++;
            break;
        case 1:{                      //障碍物
            it++;
            if(!protected_Timer.isActive()&&!sprint_Timer.isActive()){
                gameover();
            }
            break;
        }
        case 2:{                      //棒棒糖
            protected_Timer.start();
            it=barriers.erase(it);
            break;
        }
        case 3:{                      //金币
            it=barriers.erase(it);
            coin++;
            break;
        }
        default:
            break;
        }
    }
}

void MainWindow::sprint(){
    if(!sprint_interval_Timer.isActive()){
        sprint_once=false;
        sprint_twice=false;
    }
    if(sprint_twice||(sprint_Timer.remainingTime()>90&&sprint_Timer.isActive())){
        return;
    }
    if(!sprint_once){
        sprint_once=true;
        sprint_Timer.start();
        sprint_interval_Timer.start();
    }
    else if(!sprint_twice){
        sprint_twice=true;
        sprint_Timer.start();
    }
}

void MainWindow::addBarrier(){                        //生成障碍物
    srand((unsigned int)time(NULL));
    i=rand()%4;
    switch (i) {
    case 0:
        barriers.emplace_back(new Cactus);
        barriers.emplace_back(new Apple(1));
        break;
    case 1:
        barriers.emplace_back(new Bird);
        break;
    case 2:
        barriers.emplace_back(new Yucha);
        barriers.emplace_back(new Apple(2));
        break;
    case 3:
        if(add_veget_intervai_Timer.isActive()){
            barriers.emplace_back(new Apple(2));
            return;
        }
        add_veget_intervai_Timer.start();
        barriers.emplace_back(new Veget);
        break;
    default:
        break;
    }
}


void MainWindow::on_start_clicked()           //开始游戏按键                                    /////QButton
{
    ui->start->hide();
    ui->intro->hide();
    ui->store->hide();
//    arch=new Archive;
//    arch->setParent(this);
//    arch->show();
//    arch->setFocusPolicy(Qt::NoFocus);
//    connect(arch,&Archive::aboutToClose,[=](){
//        // 窗口已关闭
//        coin=arch->c;
//        rec=arch->dis;
//        filename=arch->filename;
//        this->setFocus();
//        arch->loadSettings(filename, "coin", coin);
//        arch->loadSettings(filename, "record", rec);
//        playgame();
//        update();
//    });
    playgame();
}

//游戏介绍按键
void MainWindow::on_intro_clicked()
{
    intro = new Introduction(this);
    intro->setWindowFlags(Qt::Window | Qt::WindowStaysOnTopHint | Qt::CustomizeWindowHint);
    intro->setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            intro->size(),
            qApp->primaryScreen()->availableGeometry()
        )
    );
    intro->setAttribute(Qt::WA_DeleteOnClose);
    intro->show();
}


void MainWindow::on_restart_clicked()
{
    ui->groupBox->hide();
    barriers.clear();
    dino.y=DINO_ON_GROUNG_POS_Y;
    playgame();
}

void MainWindow::on_store_clicked(){
    //点击商店
    ui->start->hide();
    ui->intro->hide();
    ui->store->hide();

    store=new Store;
    store->setParent(this);
    store->show();


}

void MainWindow::on_return_main_clicked()
{
    ui->groupBox->hide();
    ui->coin->hide();
    ui->distance->hide();
    ui->record->hide();
    ui->start->show();
    ui->intro->show();
    ui->store->hide();
    barriers.clear();
    dino.y=DINO_ON_GROUNG_POS_Y;
    dino.current_run_img=0;
    update();
}

void MainWindow::initStartScreen() {
    ui->start->show();
    ui->intro->show();
    ui->store->show();
    // 其他初始化开始界面的操作
}

