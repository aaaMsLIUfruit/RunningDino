#include "character.h"
#include "ui_character.h"

Character::Character(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Character)
{
    ui->setupUi(this);
}

Character::~Character()
{
    delete ui;
}
