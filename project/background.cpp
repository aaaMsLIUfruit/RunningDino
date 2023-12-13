#include "background.h"
#include "ui_background.h"

Background::Background(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Background)
{
    ui->setupUi(this);
}

Background::~Background()
{
    delete ui;
}
