#include "prop.h"
#include "ui_prop.h"

#include <QDebug>
#include <QFontDatabase>

Prop::Prop(QWidget *parent) :
    QWidget(parent),
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


    ui->comboBox->addItem("更多金币");
    ui->comboBox->addItem("开局无敌");

}

Prop::~Prop()
{
    delete ui;

}

void Prop::setupUi() {
    // 设置 UI 属性
}

void Prop::setupConnections() {
    connect(ui->comboBox, &QComboBox::currentTextChanged, this, &Prop::onPropSelected);
    connect(ui->returnButton, &QPushButton::clicked, this, &Prop::on_returnButton_clicked);
}


void Prop::onPropSelected(const QString &propName) {
    //处理道具选择
    qDebug() << "Selected prop: " << propName;
    //释放信号
    emit propSelected(propName);
}
