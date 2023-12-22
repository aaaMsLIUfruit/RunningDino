#include <QFontDatabase>
#include <QPushButton>

#include "bossintro.h"
#include "ui_bossintro.h"

BossIntro::BossIntro(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BossIntro)
{
    ui->setupUi(this);

    //设置窗口标题
    setWindowTitle("游戏说明");

    //导入并设置字体
    int fontId = QFontDatabase::addApplicationFont(QStringLiteral(":/res/ark-pixel-12px-monospaced-zh_cn.ttf"));
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    QFont font;
    font.setFamily(fontFamilies[0]);
    font.setPointSize(16);

    //设置标签字体
    ui->BossPlayButton->setFont(font);
    ui->intro_1->setFont(font);
    ui->intro_2->setFont(font);
    ui->intro_3->setFont(font);
    ui->intro_4->setFont(font);

    //设置按钮样式
    ui->BossPlayButton->setStyleSheet("QPushButton{background-color:rgba(0,0,0,0);}"
                                   "QPushButton:hover{color:rgb(140, 162, 188);}");

    //连接点击事件到槽函数
    connect(ui->BossPlayButton,&QPushButton::clicked,this,[&](){
        emit BossPlayButton_clicked();
        close();
    });
}

BossIntro::~BossIntro()
{
    delete ui;
}
