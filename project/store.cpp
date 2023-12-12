#include "store.h"
#include "ui_store.h"
#include "config.h"

#include <QFontDatabase>

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
    font.setPointSize(24);
    font1.setFamily(fontFamilies[0]);
    font1.setPointSize(36);

    ui->text->setFont(font1);
    ui->characters->setFont(font);
    ui->props->setFont(font);
    ui->backgrounds->setFont(font);



}

Store::~Store()
{
    delete ui;
}
