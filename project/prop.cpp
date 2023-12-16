#include "prop.h"
#include "ui_prop.h"

#include <QDebug>

Prop::Prop(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Prop)
{
    ui->setupUi(this);
    setupUi();
    setupConnections();
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
    qDebug() << "Selected prop: " << propName;
}
