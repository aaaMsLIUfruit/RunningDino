#include "store.h"
#include "ui_store.h"
#include "config.h"
#include "character.h"
#include "prop.h"
#include "background.h"
#include "mainwindow.h"

#include <QFontDatabase>
#include <QObject>

Store::Store(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Store),
    parentWidget(parent)
{
    ui->setupUi(this);

    mainWindowPtr=qobject_cast<MainWindow*>(parent);
    coin = mainWindowPtr->coin;
    ui->coin->setText("Coin: " + QString::number(coin));

    setFixedSize(GAME_WIDTH,GAME_HEIGHT);
    int fontId=QFontDatabase::addApplicationFont(QStringLiteral(":/res/ark-pixel-12px-monospaced-zh_cn.ttf"));   //导入字体文件
    QStringList fontFamilies=QFontDatabase::applicationFontFamilies(fontId);
    QFont font1;
    QFont font;

    font.setFamily(fontFamilies[0]);
    font.setPointSize(20);
    font1.setFamily(fontFamilies[0]);
    font1.setPointSize(36);

    ui->coin->setFont(font);
    ui->head->setFont(font1);
    ui->characters->setFont(font);
    ui->props->setFont(font);
    ui->backgrounds->setFont(font);
    ui->returned->setFont(font);

    connect(ui->characters,SIGNAL(clicked()),this,SLOT(on_character_clicked()));
    connect(ui->props,SIGNAL(clicked()),this,SLOT(on_prop_clicked()));
    connect(ui->backgrounds,SIGNAL(clicked()),this,SLOT(on_background_clicked()));

    //设置焦点策略，防止UI元素抢占键盘焦点
    ui->returned->setFocusPolicy(Qt::NoFocus);
    ui->characters->setFocusPolicy(Qt::NoFocus);
    ui->props->setFocusPolicy(Qt::NoFocus);
    ui->backgrounds->setFocusPolicy(Qt::NoFocus);

}

void Store::on_character_clicked()
{

    ui->props->hide();
    ui->characters->hide();
    ui->head->hide();
    ui->backgrounds->hide();
    ui->returned->hide();

    character=new Character(this, coin);
    character->setAttribute(Qt::WA_DeleteOnClose);

    character->show();

    connect(character, &Character::characterSelected, this, &Store::onCharacterChanged);
    connect(character,&Character::coinChanged,this,&Store::onCoinChanged);
}

void Store::on_prop_clicked()
{

    ui->props->hide();
    ui->characters->hide();
    ui->head->hide();
    ui->backgrounds->hide();
    ui->returned->hide();

    prop=new Prop(this,coin);
    prop->setAttribute(Qt::WA_DeleteOnClose);

    prop->show();

    connect(prop, &Prop::propSelected, this, &Store::onPropChanged);
    connect(prop,&Prop::coinChanged,this,&Store::onCoinChanged);
}

void Store::on_background_clicked()
{
    ui->props->hide();
    ui->characters->hide();
    ui->head->hide();
    ui->backgrounds->hide();
    ui->returned->hide();

    background=new Background(this);
    background->setAttribute(Qt::WA_DeleteOnClose);

    connect(background, &Background::backgroundSelected, this, &Store::onBackgroundChanged);

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

void Store::onCharacterChanged(const QString &characterName) {
    emit characterChangedInStore(characterName);

}

void Store::onBackgroundChanged(const QString &backgroundName){
    emit backgroundChangedInStore(backgroundName);
}

void Store::onCoinChanged(const int &newCoinValue) {
    emit coinChanged(newCoinValue);
    coin = mainWindowPtr->coin;
    ui->coin->setText("Coin: " + QString::number(coin));
}

void Store::onPropChanged(const QString &propName){
    emit propChangedInStore(propName);
}

Store::~Store()
{
    delete ui;
}
