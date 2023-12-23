#include "prop.h"
#include "ui_prop.h"

#include <QDebug>
#include <QFontDatabase>
#include <QMessageBox>

Prop::Prop(QWidget *parent, int coinValue) :
    QWidget(parent),
    coin(coinValue),
    ui(new Ui::Prop)
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

    ui->comboBox->setGeometry(400, 100, 350, 71);
    ui->label->setGeometry(100, 80, 351, 111);
    ui->returnButton->setGeometry(700, 350, 161, 61);

    ui->comboBox->addItem("无");
    ui->comboBox->addItem("复活卡 30coin");
    ui->comboBox->addItem("加速卡 30coin");
    ui->comboBox->addItem("更多金币 30coin");
    ui->comboBox->addItem("开局无敌 30coin");

    //设置焦点策略，防止UI元素抢占键盘焦点
    ui->returnButton->setFocusPolicy(Qt::NoFocus);
    ui->comboBox->setFocusPolicy(Qt::NoFocus);


}

Prop::~Prop()
{
        delete ui;

}

void Prop::setupUi() {
    // 设置 UI 属性
}

void Prop::onPropSelected(const QString &propName)
{
    int propCost = 0;

    // 根据角色名称设置相应的金币花费
    if (propName == "复活卡 30coin" ||
        propName == "加速卡 30coin" ||
        propName == "开局无敌 30coin"||
        propName == "更多金币 30coin")
    {
        propCost = 30;
    }

    if (propCost > 0) {
        // 如果有金币花费
        if (coin >= propCost) {
            // 如果有足够金币，则发出信号
            qDebug() << "Selected prop: " << propName;
            QMessageBox::information(this, "Sufficient Coins", "购买成功！");

            coin -= propCost;

            emit propSelected(propName);
            emit coinChanged(coin);

        } else
        {
            // 如果金币不足，提示用户
            qDebug() << "Insufficient coins!";
            // 这里可以使用 QMessageBox 进行提示
            QMessageBox::critical(this, "Insufficient Coins", "金币数量不足！");
        }
    } else {
        // 无需花费金币的道具，直接发出信号
        qDebug() << "Selected prop: " << propName;
        emit propSelected(propName);
    }
}



void Prop::setupConnections() {
    connect(ui->comboBox, &QComboBox::currentTextChanged, this, &Prop::onPropSelected);
    connect(ui->returnButton, &QPushButton::clicked, this, &Prop::on_returnButton_clicked);
}
