#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QIcon>
#include <QKeyEvent>
#include <ctime>
#include <QFontDatabase>
#include <QString>
#include <QScreen>
#include <QStyle>

#include "config.h"
#include "dino.h"
#include "bossmode.h"
#include "archive.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->start->hide();
    ui->intro->hide();
    ui->store->hide();
    ui->bossmode->hide();

    //创建存档界面
    arch = new Archive(this);
    arch->hide();

    //创建并展示主界面
    home = new Home(this);
    home->show();

    dino = new Dino(this);

    //连接home的信号到槽函数
    connect(home,&Home::switchToArc,this,&MainWindow::switchToArchWindow);

    initWindow();    //初始化窗口

    playAnimation();//主页动画

}


//初始化窗口
// 初始化窗口的函数定义
void MainWindow::initWindow() {
    // 设置游戏窗口的固定大小，使用在config.h文件中定义的常量
    setFixedSize(GAME_WIDTH, GAME_HEIGHT);

    // 设置窗口的标题
    setWindowTitle(GAME_TITLE);

    // 设置窗口的图标
    setWindowIcon(QIcon(GAME_ICON));

    // 调用update函数，强制窗口重绘，确保背景被正确加载和显示
    update();

    // 添加字体文件，返回字体ID
    int fontId = QFontDatabase::addApplicationFont(QStringLiteral(":/res/ark-pixel-12px-monospaced-zh_cn.ttf"));
    // 从字体数据库中获取字体家族名称
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    // 创建字体对象，并设置字体家族
    QFont font;
    font.setFamily(fontFamilies[0]);

    // 为UI元素设置字体
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
    ui->bossmode->setFont(font);
    ui->countdownLabel->setFont(font);

    // 设置UI元素的几何位置
    ui->start->setGeometry(390, 140, ui->start->width(), ui->start->height());
    ui->intro->setGeometry(390, 260, ui->intro->width(), ui->intro->height());

    // 设置焦点策略，防止UI元素抢占键盘焦点
    ui->start->setFocusPolicy(Qt::NoFocus);
    ui->intro->setFocusPolicy(Qt::NoFocus);
    ui->store->setFocusPolicy(Qt::NoFocus);
    ui->restart->setFocusPolicy(Qt::NoFocus);
    ui->return_main->setFocusPolicy(Qt::NoFocus);
    ui->bossmode->setFocusPolicy(Qt::NoFocus);

    // 隐藏某些UI元素，这些元素在游戏开始时不应该显示
    ui->coin->hide();
    ui->distance->hide();
    ui->groupBox->hide();
    ui->record->hide();

    // 设置定时器的间隔时间，并启用定时器
    m_Timer.setInterval(GAME_RATE);
    sprint_Timer.setInterval(SPRINT_DURATION);
    sprint_Timer.setSingleShot(true);
    sprint_interval_Timer.setInterval(SPRINT_INTERVAL);
    sprint_interval_Timer.setSingleShot(true);
    add_Barrier_interval_Timer.setInterval(ADD_BARRIER_INTERVAL);
    add_veget_intervai_Timer.setInterval(ADD_LOLIPOP_INTERVAL);
    add_veget_intervai_Timer.setSingleShot(true);
    protected_Timer.setInterval(PROTECTED_DURATION);
    protected_Timer.setSingleShot(true);
    jumpHome_Timer.setInterval(JUMP_INTERVAL);

    // Dino对象的初始Y坐标设置为地面位置
    dino->y = DINO_ON_GROUNG_POS_Y;

    // 连接信号和槽，以便在定时器超时时更新游戏状态
    connect(&m_Timer, &QTimer::timeout, this, [&]() {
    updatePosition(); // 更新游戏内物体的位置
    collisionDetection(); // 检测碰撞
    showProtectedtime();

    // 更新金币和距离的显示
    ui->coin->setText("Coin: " + QString::number(coin));
    ui->distance->setText("Distance: " + QString::number(grounds.distance) + " m");
    ui->record->setText("Record: " + QString::number(rec) + " m");

     // 如果当前距离超过了记录，则更新记录
    if (grounds.distance > rec) {
        ui->record->setText("Record: " + QString::number(grounds.distance) + " m");
    }

     // 刷新屏幕，以便更改能够显示出来
        update();
        });

        connect(&add_Barrier_interval_Timer, &QTimer::timeout, this, [&]() {
            addBarrier(); // 添加新的障碍物
        });


     // 初始化距离和金币的显示
        grounds.distance = 0;
        ui->coin->setText("Coin: " + QString::number(coin));
        ui->distance->setText("Distance: " + QString::number(grounds.distance) + " m");
        ui->record->setText("Record: " + QString::number(rec) + " m");

     // 初始化冲刺状态为false
        sprint_once = false;
        sprint_twice = false;
}

//更新角色
void MainWindow::updateDinoCharacter(const QString &characterName) {
    dino->setCharacter(characterName);
    update();
}

//更新背景
void MainWindow::updateBackground(const QString &backgroundName){
    if(backgroundName=="经典像素"){
        background.load(":/res/background.png");
    }
    else if(backgroundName=="马里奥世界"){
        background.load(":/res/mariobackground.png");
        background = background.scaled(1000, 530);
    }
    update();
}

void MainWindow::playAnimation() {
    m_Timer.start();
    jumpHome_Timer.start();
    dino->run_Timer.start();
    connect(&dino->run_Timer,&QTimer::timeout,this,[&](){
        update();     //刷新屏幕
    });
    connect(&jumpHome_Timer,&QTimer::timeout,this,[&](){
        dino->jump();
    });
}

//绘制游戏
void MainWindow::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, background); // 绘制背景


    for (int i = 0; i < 9; i++) {
       painter.drawPixmap(grounds.grounds[i].ground_posX, 356, grounds.grounds[i].ground);
    }


    // 如果 Dino 使用的是静态图片，则在这里绘制
    if (dino->dinoLabel->isHidden()) {
        painter.drawPixmap(dino->x, dino->y, dino->getImg());
    }
    // 注意：如果 Dino 正在使用 GIF 动画，那么 dinoLabel 已经负责显示了
    //dino.dinoLabel->move(dino.x, dino.y);
    //dino.dinoLabel->show();

    for (auto &barr : barriers) {
        if (protected_Timer.isActive()) {
            painter.drawPixmap(barr->x, barr->y, barr->getImg(1));
        } else {
            painter.drawPixmap(barr->x, barr->y, barr->getImg(0));
        }
    }
}

// 当用户按键时触发的事件处理函数
void MainWindow::keyPressEvent(QKeyEvent *event) {
    // 将event强制转换为QKeyEvent，以便获取更详细的按键信息
    QKeyEvent *key = static_cast<QKeyEvent*>(event);

    // 检查是否按下了空格键
    if (key->key() == Qt::Key_Space) {
        // 空格键被按下，调用Dino对象的jump方法使角色跳跃
        dino->jump();
    }

    // 检查是否按下了Shift键
    if (key->key() == Qt::Key_Shift) {
        // Shift键被按下，调用当前类的sprint方法使角色进行冲刺
        sprint();
    }
}

// 当用户点击鼠标时触发的事件处理函数
void MainWindow::mousePressEvent(QMouseEvent *event) {
    // 检查是否点击了鼠标左键
    if (event->button() == Qt::LeftButton) {
        // 鼠标左键被点击，调用Dino对象的jump方法使角色跳跃
        dino->jump();
    }

    // 检查是否点击了鼠标右键
    if (event->button() == Qt::RightButton) {
        // 鼠标右键被点击，调用当前类的sprint方法使角色进行冲刺
        sprint();
    }
}

// 开始游戏的函数
void MainWindow::playgame() {
    // 重置游戏距离为0
    grounds.distance = 0;

    if(dino->chara=="经典小恐龙"&&dino->chara=="超级马里奥"){
        // 重置Dino对象的当前运行图像索引为0
        dino->current_run_img = 0;
    }

    // 显示游戏中的金币和距离UI元素
    ui->coin->show();
    ui->distance->show();
    ui->record->show();

    // 启动各种定时器以开始游戏循环
    m_Timer.start();
    dino->run_Timer.start();
    add_Barrier_interval_Timer.start();
}

// 游戏结束的函数
void MainWindow::gameover() {
    // 停止所有定时器，暂停游戏循环
    m_Timer.stop();
    sprint_Timer.stop();
    sprint_interval_Timer.stop();
    add_Barrier_interval_Timer.stop();
    add_veget_intervai_Timer.stop();
    dino->run_Timer.stop();
    protected_Timer.stop();

    // 显示游戏结束时的分数和距离
    ui->over_score->setText("Coin: " + QString::number(coin));
    ui->over_distance->setText("Distance: " + QString::number(grounds.distance) + " m");

    // 保存游戏设置，如金币数和最远距离
    arch->saveSettings(filename, "coin", coin);
    if (grounds.distance > rec) {
        arch->saveSettings(filename, "record", grounds.distance);
    }

    // 获取当前日期时间，并保存
    QDateTime dateTime = QDateTime::currentDateTime();
    QString qStr = dateTime.toString("yyyy-MM-dd hh:mm:ss ddd");
    arch->saveSettings(filename, "time", qStr);

    // 显示游戏结束的UI组件
    ui->groupBox->show();

    // 刷新屏幕以更新UI变化
    update();
}


// 更新游戏中所有对象的位置
void MainWindow::updatePosition() {
    // 计算地面的新位置，用于动画效果
    grounds.calculatePositions();

    // 遍历所有障碍物
    for (it = barriers.begin(); it != barriers.end(); ) {
        // 如果障碍物已经离开屏幕，则移除它
        if ((*it)->isOut()) {
            it = barriers.erase(it);
        } else {
            // 否则，更新障碍物的位置
            (*it)->updatePosition();
            // 如果障碍物是鸟类，还需要更新它的飞行高度
            (*it)->updateBirdY();
            it++;
        }
    }

    // 更新恐龙的垂直位置
    dino->updatePositionY();

    // 如果正在进行冲刺，需要加速地面和障碍物的移动速度
    if (this->sprint_Timer.isActive()) {
        // 通过再次调用计算位置函数加速移动
        grounds.calculatePositions();
        grounds.calculatePositions();
        for (auto &barr : barriers) {
            barr->updatePosition();
            barr->updatePosition();
        }
    }
}

// 碰撞检测函数
void MainWindow::collisionDetection() {
    if(wudi==true)//检测无敌道具是否成功使用
    {
        protected_Timer.start();
        if(startgame_Timer.elapsed() >= 15000){
            protected_Timer.stop();
        }
    }

    // 遍历所有障碍物以检测与恐龙的碰撞
    for (it = barriers.begin(); it != barriers.end(); ) {
        // 检查当前障碍物是否与恐龙的碰撞矩形发生碰撞
        int collisionType = (*it)->collisionDetection(dino->dino_Rect);

        // 根据碰撞类型处理结果
        switch (collisionType) {
        case 0: // 无碰撞
            it++;
            break;
        case 1: // 碰到障碍物
            it++;
            // 如果没有保护且不在冲刺状态，游戏结束
            if (!protected_Timer.isActive() && !sprint_Timer.isActive()) {
                gameover();
            }
            break;
        case 2: // 捡到棒棒糖，获得保护
            protected_Timer.start();
            it = barriers.erase(it);
            break;
        case 3: // 捡到金币，增加金币数量
            it = barriers.erase(it);
            coin++;
            break;
        default:
            break;
        }
    }
}

// 冲刺功能的实现
void MainWindow::sprint() {
    // 如果冲刺间隔定时器未激活，允许再次冲刺
    if (!sprint_interval_Timer.isActive()) {
        sprint_once = false;
        sprint_twice = false;
    }

    // 如果已经进行了第二次冲刺，或者第一次冲刺的剩余时间过长，则不再冲刺
    if (sprint_twice || (sprint_Timer.remainingTime() > 90 && sprint_Timer.isActive())) {
        return; // 退出函数，不再执行冲刺
    }

    // 启动第一次冲刺
    if (!sprint_once) {
        sprint_once = true;
        sprint_Timer.start();
        sprint_interval_Timer.start();
        if(dino->chara=="经典小恐龙"){
            dino->windSound.play();
        }
    }
    // 启动第二次冲刺
    else if (!sprint_twice) {
        sprint_twice = true;
        sprint_Timer.start();
        if(dino->chara=="经典小恐龙"){
            dino->windSound.play();
        }
    }
}


// 生成障碍物的函数
void MainWindow::addBarrier() {
    srand((unsigned int)time(NULL)); // 初始化随机数生成器，基于当前时间
    i = rand() % 4; // 生成一个0到3之间的随机数，用于决定添加哪种障碍物

    if(morecoin){
        // 根据随机数选择添加的障碍物类型
        switch (i) {
        case 0:
            // 添加仙人掌和苹果作为障碍物
            barriers.emplace_back(new Cactus1);
            barriers.emplace_back(new Coin(1));
            barriers.emplace_back(new Coin(2));
            break;
        case 1:
            // 添加鸟类作为障碍物
            barriers.emplace_back(new Bird);
            break;
        case 2:
            // 添加鱼叉和苹果作为障碍物
            barriers.emplace_back(new Yucha);
            barriers.emplace_back(new Coin(2));
            barriers.emplace_back(new Coin(2));
            break;
        case 3:
            // 检查是否可以添加蔬菜类障碍物
            if (add_veget_intervai_Timer.isActive()) {
                // 如果定时器激活，仅添加苹果
                barriers.emplace_back(new Coin(2));
                return;
            }
            // 启动蔬菜添加间隔计时器，并添加蔬菜作为障碍物
            add_veget_intervai_Timer.start();
            barriers.emplace_back(new Veget);
            break;
        default:
            // 默认情况下不执行任何操作
            break;
        }
    }

    else if(!morecoin){
        // 根据随机数选择添加的障碍物类型
        switch (i) {
        case 0:
            // 添加仙人掌和苹果作为障碍物
            barriers.emplace_back(new Cactus1);
            barriers.emplace_back(new Coin(1));
            break;
        case 1:
            // 添加鸟类作为障碍物
            barriers.emplace_back(new Bird);
            break;
        case 2:
            // 添加鱼叉和苹果作为障碍物
            barriers.emplace_back(new Yucha);
            barriers.emplace_back(new Coin(2));
            break;
        case 3:
            // 检查是否可以添加蔬菜类障碍物
            if (add_veget_intervai_Timer.isActive()) {
                // 如果定时器激活，仅添加苹果
                barriers.emplace_back(new Coin(2));
                return;
            }
            // 启动蔬菜添加间隔计时器，并添加蔬菜作为障碍物
            add_veget_intervai_Timer.start();
            barriers.emplace_back(new Veget);
            break;
        default:
            // 默认情况下不执行任何操作
            break;
        }
    }
}

// 开始游戏按钮点击事件处理
void MainWindow::on_start_clicked() {
    // 隐藏开始、介绍和商店按钮
    ui->start->hide();
    ui->intro->hide();
    ui->store->hide();
    ui->bossmode->hide();
    startgame_Timer.start();//游戏内计时器启动

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
    // 开始游戏的主要逻辑
    playgame(); // 调用playgame函数来开始游戏
}

// 游戏介绍按钮点击事件处理
void MainWindow::on_intro_clicked() {
    // 创建游戏介绍的窗口实例
    intro = new Introduction(this);
    // 设置窗口样式，使其始终位于顶部
    intro->setWindowFlags(Qt::Window | Qt::WindowStaysOnTopHint | Qt::CustomizeWindowHint);
    // 设置窗口位置和大小
    intro->setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            intro->size(),
            qApp->primaryScreen()->availableGeometry()
        )
    );
    intro->setAttribute(Qt::WA_DeleteOnClose); // 设置窗口关闭时自动删除
    intro->show(); // 显示游戏介绍窗口
}



void MainWindow::on_restart_clicked() {
    // 当点击重启游戏按钮时触发
    ui->groupBox->hide();
    // 隐藏游戏结束的界面
    barriers.clear();
    // 清空所有障碍物
    dino->y = DINO_ON_GROUNG_POS_Y;
    // 重置恐龙的位置到地面
    playgame();
    // 调用playgame函数重新开始游戏
}


void MainWindow::on_store_clicked() {
    // 当点击商店按钮时触发
    // 隐藏主界面上的按钮
    ui->start->hide();
    ui->intro->hide();
    ui->store->hide();
    ui->bossmode->hide();

    // 创建商店界面，并设置其为主窗口的子窗口
    store = new Store(this);
    store->show(); // 显示商店界面
    store->setAttribute(Qt::WA_DeleteOnClose); //设置窗口关闭时自动删除

    connect(store, &Store::characterChangedInStore, this, &MainWindow::updateDinoCharacter);
    connect(store, &Store::backgroundChangedInStore, this, &MainWindow::updateBackground);
    connect(store, &Store::coinChanged, this, &MainWindow::updateCoin);
    connect(store, &Store::propChangedInStore, this, &MainWindow::updateProp);
}


void MainWindow::on_return_main_clicked() {
    // 当点击返回主界面按钮时触发

    ui->groupBox->hide();  // 隐藏游戏结束界面
    // 隐藏游戏中的信息显示
    ui->coin->hide();
    ui->distance->hide();
    ui->record->hide();
    // 显示主界面上的按钮
    ui->start->show();
    ui->intro->show();
    ui->store->show();
    ui->bossmode->show();
    barriers.clear();  // 清空所有障碍物
    // 重置恐龙的位置和动画帧
    dino->y = DINO_ON_GROUNG_POS_Y;
    dino->current_run_img = 0;
    update();  // 刷新界面，显示变更
}

void MainWindow::initStartScreen() {
    ui->start->show();
    ui->intro->show();
    ui->store->show();
    ui->bossmode->show();
    // 其他初始化开始界面的操作
}

//切换到存档页面函数实现
void MainWindow::switchToArchWindow(){
    // 创建并展示存档界面
    arch->show();

    //动画停止
    dino->run_Timer.stop();
    jumpHome_Timer.stop();
    m_Timer.stop();
    dino->y=DINO_ON_GROUNG_POS_Y;

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
        arch->hide();
        update();
    });
}

void Store::on_returned_clicked()
{
    this->hide(); // 隐藏当前窗口

    if (parentWidget) {
        // 显示主窗口的相关组件
        MainWindow* mainWindow = qobject_cast<MainWindow*>(parentWidget);
        if (mainWindow) {
            mainWindow->showComponents();
            // 在 MainWindow 中定义的方法
        }
        parentWidget->show();
        // 显示父窗口
    }
}



void MainWindow::showComponents() {
    ui->start->show();
    ui->intro->show();
    ui->store->show();
    ui->bossmode->show();
    // 显示其他需要的组件
}

void MainWindow::on_bossmode_clicked(){
    ui->start->hide();
    ui->intro->hide();
    ui->store->hide();
    ui->bossmode->hide();

    //创建并展示boss模式
    bossmode = new Bossmode(this);
    bossmode->setAttribute(Qt::WA_DeleteOnClose);//设置窗口关闭时自动删除
    bossmode->show();

    //创建boss模式介绍窗口
    bossIntro = new BossIntro(this);
    bossIntro->setAttribute(Qt::WA_DeleteOnClose);//设置窗口关闭时自动删除
    bossIntro->show();

    //连接boss介绍界面信号到槽
    connect(bossIntro,&BossIntro::BossPlayButton_clicked,[=](){
        bossmode->start_game();
    });
    //连接boss模式按钮信号
    connect(bossmode,&Bossmode::boss_close,this,&MainWindow::boss_closed);

}


void MainWindow::updateCoin(const int &newCoinValue) {
    coin = newCoinValue;
    update();
}

void MainWindow::updateProp(const QString &propName){
    if(propName == "复活卡 30coin")
    {
        //gameRevive();
    }
    else if(propName == "加速卡 30coin")
    {
        quickupGame();
    }
    else if(propName == "开局无敌 30coin"){
        wudi = true;
    }
    else if(propName == "更多金币 30coin"){
        morecoin = true;
    }
}

//显示保护状态倒计时
void MainWindow::showProtectedtime(){

    if (protected_Timer.isActive())
    {
        int remainingTime = protected_Timer.remainingTime();
        int seconds = remainingTime / 1000;

        ui->countdownLabel->setText("protection:"+QString::number(seconds) + "s");
        ui->countdownLabel->show();
    }
    else
    {
        ui->countdownLabel->hide();
    }
}


void MainWindow::quickupGame(){

    // 通过再次调用计算位置函数加速移动
    grounds.calculatePositions();
    grounds.calculatePositions();
    for (auto &barr : barriers) {
        barr->updatePosition();
        barr->updatePosition();
    }
}

void MainWindow::boss_closed(){
    ui->start->show();
    ui->intro->show();
    ui->store->show();
    ui->bossmode->show();

}

MainWindow::~MainWindow()
{
    delete ui;

}
