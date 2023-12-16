#include "character.h"
#include "ui_character.h"

#include <QDebug>

Character::Character(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Character)
{
    ui->setupUi(this);
    setupUi();
    setupConnections();
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
}


