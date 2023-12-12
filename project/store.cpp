#include "store.h"
#include "ui_store.h"
#include "config.h"
#include"character.h"

#include <QFontDatabase>
#include<QObject>

Store::Store(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Store)
{
    ui->setupUi(this);

    setFixedSize(GAME_WIDTH,GAME_HEIGHT);
    int fontId=QFontDatabase::addApplicationFont(QStringLiteral(":/res/ark-pixel-12px-monospaced-zh_cn.ttf"));   //导入字体文件
    QStringList fontFamilies=QFontDatabase::applicationFontFamilies(fontId);
    QFont font1;
    QFont font;

    font.setFamily(fontFamilies[0]);
    font.setPointSize(20);
    font1.setFamily(fontFamilies[0]);
    font1.setPointSize(36);

    ui->head->setFont(font1);
    ui->characters->setFont(font);
    ui->props->setFont(font);
    ui->backgrounds->setFont(font);
    ui->returned->setFont(font);

    connect(ui->characters,SIGNAL(clicked()),this,SLOT(on_character_clicked()));

}

void Store::on_character_clicked()
{
    ui->props->hide();
    ui->characters->hide();
    ui->head->hide();
    ui->backgrounds->hide();

    character=new Character;
    character->setParent(this);
    character->show();
}

Store::~Store()
{
    delete ui;
}
