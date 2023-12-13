#include "prop.h"
#include "ui_prop.h"

Prop::Prop(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Prop)
{
    ui->setupUi(this);
}

Prop::~Prop()
{
    delete ui;
}
