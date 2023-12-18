#include "character.h"
#include "ui_character.h"

#include <QDebug>
#include <QFontDatabase>

Character::Character(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Character)
{
    int fontId = QFontDatabase::addApplicationFont(QStringLiteral(":/res/ark-pixel-12px-monospaced-zh_cn.ttf"));
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    QFont font;
    font.setFamily(fontFamilies[0]);  // 选择字体族的第一个字体
    font.setPointSize(28);

    ui->setupUi(this);
    setupUi();
    setupConnections();

    ui->comboBox->setFont(font);
    ui->label->setFont(font);
    ui->returnButton->setFont(font);
    ui->label->setGeometry(100, 80, 351, 111);

    ui->comboBox->setGeometry(400, 70, 301, 71);
    ui->comboBox->addItem("经典小恐龙");
    ui->comboBox->addItem("说的道理");
    ui->comboBox->addItem("科比");
    ui->comboBox->addItem("摇晃小鸵鸟");
    ui->comboBox->addItem("超级马里奥");

    ui->returnButton->setGeometry(790, 60, 161, 61);

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
    // 处理角色选择
    qDebug() << "Selected character: " << characterName;
    emit characterSelected(characterName); // 触发信号
}
