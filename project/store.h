#ifndef STORE_H
#define STORE_H

#include <QWidget>
#include <QVariant>
#include <QString>

#include"character.h"


namespace Ui {
class Store;
}

class Store : public QWidget
{
    Q_OBJECT

public:
    explicit Store(QWidget *parent = nullptr);
    ~Store();

    Character *character=new Character;

private slots:
    void on_character_clicked();

private:
    Ui::Store *ui;
};

#endif // STORE_H
