#include "archive.h"
#include "ui_archive.h"

archive::archive(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::archive)
{
    ui->setupUi(this);
}

archive::~archive()
{
    delete ui;
}
