#include "character.h"
#include "ui_character.h"
#include "archive.h"


#include <QDebug>
#include <QFontDatabase>
#include <QMessageBox>

Character::Character(QWidget *parent, int coinValue) :
    QWidget(parent),
    coin(coinValue),
    ui(new Ui::Character)

{

    int fontId = QFontDatabase::addApplicationFont(QStringLiteral(":/res/ark-pixel-12px-monospaced-zh_cn.ttf"));
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    QFont font;
    font.setFamily(fontFamilies[0]);  // 选择字体族的第一个字体
    font.setPointSize(20);

    ui->setupUi(this);
    setupUi();
    setupConnections();

    ui->comboBox->setFont(font);
    ui->label->setFont(font);
    ui->returnButton->setFont(font);


    ui->comboBox->addItem("经典小恐龙 free");
    ui->comboBox->addItem("说的道理 50coin");
    ui->comboBox->addItem("科比 50coin");
    ui->comboBox->addItem("超级马里奥 50coin");


    ui->comboBox->setGeometry(400, 100, 400, 71);
    ui->label->setGeometry(100, 80, 351, 111);
    ui->returnButton->setGeometry(790, 350, 161, 61);

    //设置焦点策略，防止UI元素抢占键盘焦点
    ui->comboBox->setFocusPolicy(Qt::NoFocus);
    ui->returnButton->setFocusPolicy(Qt::NoFocus);

}

Character::~Character()
{
    delete ui;
}

void Character::setupUi()
{
    // 设置UI属性
}

void Character::setupConnections()
{
    connect(ui->comboBox, &QComboBox::currentTextChanged, this, &Character::onCharacterSelected);
    connect(ui->returnButton, &QPushButton::clicked, this, &Character::on_returnButton_clicked);
}

void Character::onCharacterSelected(const QString &characterName)
{
    int characterCost = 0;

        // 根据角色名称设置相应的金币花费
        if (characterName == "说的道理 50coin" ||
            characterName == "科比 50coin" ||
            characterName == "超级马里奥 50coin") {
            characterCost = 50;
        }

        if (characterCost > 0) {
            // 如果有金币花费
            if (coin >= characterCost) {
                // 如果有足够金币，则发出信号
                qDebug() << "Selected character: " << characterName;
                QMessageBox::information(this, "Sufficient Coins", "购买成功！");

                coin -= characterCost;

                emit characterSelected(characterName);
                emit coinChanged(coin);

            } else {
                // 如果金币不足，提示用户
                qDebug() << "Insufficient coins!";
                // 这里可以使用 QMessageBox 进行提示
                QMessageBox::critical(this, "Insufficient Coins", "金币数量不足！");
            }
        } else {
            // 无需花费金币的角色，直接发出信号
            qDebug() << "Selected character: " << characterName;
            emit characterSelected(characterName);
        }
}
