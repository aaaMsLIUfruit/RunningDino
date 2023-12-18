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
    font.setPointSize(28);

    ui->setupUi(this);
    setupUi();
    setupConnections();

    ui->comboBox->setFont(font);
    ui->label->setFont(font);
    ui->returnButton->setFont(font);

    ui->label->setGeometry(100, 80, 351, 111);
    ui->comboBox->setGeometry(400, 70, 301, 71);
    ui->returnButton->setGeometry(790, 60, 161, 61);

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
    qDebug() << "Selected background: " << backgroundName;
}

