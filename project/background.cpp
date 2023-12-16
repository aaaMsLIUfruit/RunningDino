#include "background.h"
#include "ui_background.h"

#include <QDebug>

Background::Background(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Background)
{
    ui->setupUi(this);
    setupUi();
    setupConnections();
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

