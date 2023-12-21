#include "home.h"
#include "ui_home.h"
#include "config.h"

#include <QFontDatabase>

Home::Home(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Home)
{
    ui->setupUi(this);

    setFixedSize(GAME_WIDTH,GAME_HEIGHT);
    //设置字体
    int fontId=QFontDatabase::addApplicationFont(QStringLiteral(":/res/ark-pixel-12px-monospaced-zh_cn.ttf"));   //导入字体文件
    QStringList fontFamilies=QFontDatabase::applicationFontFamilies(fontId);
    QFont font1,font2;
    font1.setFamily(fontFamilies[0]);
    font2.setFamily(fontFamilies[0]);
    font1.setPointSize(42);
    font2.setPointSize(30);
    ui->homeTitle->setFont(font1);
    ui->startButton->setFont(font2);

    //设置按钮样式
    ui->startButton->setStyleSheet("QPushButton{background-color:rgba(0,0,0,0);}"
                                   "QPushButton:hover{color:rgb(140, 162, 188);}");

    //连接按钮的点击信号到槽函数
    connect(ui->startButton,&QPushButton::clicked,this,&Home::on_startButton_clicked);
}

Home::~Home()
{
    delete ui;
}

//切换到存档界面
void Home::on_startButton_clicked()
{
    emit switchToArc();
    QWidget::close();
}

