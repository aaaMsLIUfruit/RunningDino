#include "background.h"
#include "ui_background.h"

#include <QDebug>
#include <QFontDatabase>

Background::Background(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Background)
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

    ui->label->setGeometry(60, 80, 450, 111);
    ui->comboBox->setGeometry(540, 100, 300, 71);
    ui->returnButton->setGeometry(790, 350, 161, 61);

    ui->comboBox->addItem("经典像素");
    ui->comboBox->addItem("马里奥世界");

    //设置焦点策略，防止UI元素抢占键盘焦点
    ui->comboBox->setFocusPolicy(Qt::NoFocus);
    ui->returnButton->setFocusPolicy(Qt::NoFocus);

}

Background::~Background()
{
    delete ui;
}

void Background::setupUi() {
    // 设置 UI 属性
}

void Background::setupConnections() {

    connect(ui->comboBox, &QComboBox::currentTextChanged, this, &Background::onBackgroundSelected);
    connect(ui->returnButton, &QPushButton::clicked, this, &Background::on_returnButton_clicked);

}

void Background::onBackgroundSelected(const QString &backgroundName) {
    //处理背景选择
    qDebug() << "Selected background: " << backgroundName;

    // 触发信号
    emit backgroundSelected(backgroundName);
}

