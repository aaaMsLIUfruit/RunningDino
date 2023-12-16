#include "store.h"
#include "ui_store.h"
#include "config.h"
#include "character.h"
#include "prop.h"
#include "background.h"

#include <QFontDatabase>
#include <QObject>

Store::Store(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Store),
    parentWidget(parent)
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
    connect(ui->props,SIGNAL(clicked()),this,SLOT(on_prop_clicked()));
    connect(ui->backgrounds,SIGNAL(clicked()),this,SLOT(on_background_clicked()));

}

void Store::on_character_clicked()
{
    ui->props->hide();
    ui->characters->hide();
    ui->head->hide();
    ui->backgrounds->hide();
    ui->returned->hide();

    character=new Character(this);
    character->setParent(this);

    character->show();
}

void Store::on_prop_clicked()
{
    ui->props->hide();
    ui->characters->hide();
    ui->head->hide();
    ui->backgrounds->hide();
    ui->returned->hide();

    prop=new Prop(this);
    prop->setParent(this);

    prop->show();
}

void Store::on_background_clicked()
{
    ui->props->hide();
    ui->characters->hide();
    ui->head->hide();
    ui->backgrounds->hide();
    ui->returned->hide();

    background=new Background(this);
    background->setParent(this);

    background->show();
}

void Store::showComponents() {
    // 显示所有需要的 UI 元素

    ui->props->show();
    ui->characters->show();
    ui->head->show();
    ui->backgrounds->show();
    ui->returned->show();

}

void Character::on_returnButton_clicked()
{
    this->hide(); // 隐藏当前窗口

    QWidget* parent = this->parentWidget();
    if (parent != nullptr) {
        // 尝试将父窗口转换为 Store 类型
        Store* storeWindow = qobject_cast<Store*>(parent);
        if (storeWindow) {
                storeWindow->showComponents(); // 显示 Store 窗口的组件
        }
    }
}

void Prop::on_returnButton_clicked()
{
    this->hide(); // 隐藏当前窗口

    QWidget* parent = this->parentWidget();
    if (parent != nullptr) {
        // 尝试将父窗口转换为 Store 类型
        Store* storeWindow = qobject_cast<Store*>(parent);
        if (storeWindow) {
                storeWindow->showComponents(); // 显示 Store 窗口的组件
        }
    }
}

void Background::on_returnButton_clicked()
{
    this->hide(); // 隐藏当前窗口

    QWidget* parent = this->parentWidget();
    if (parent != nullptr) {
        // 尝试将父窗口转换为 Store 类型
        Store* storeWindow = qobject_cast<Store*>(parent);
        if (storeWindow) {
                storeWindow->showComponents(); // 显示 Store 窗口的组件
        }
    }
}

Store::~Store()
{
    delete ui;
}
