#ifndef STORE_H
#define STORE_H

#include <QWidget>
#include <QVariant>
#include <QString>

#include "character.h"
#include "prop.h"
#include "background.h"

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
    Prop *prop = new Prop;
    Background *background = new Background;

    void showComponents();

private slots:
    void on_character_clicked();
    void on_prop_clicked();
    void on_background_clicked();
    void on_returned_clicked();

private:
    Ui::Store *ui;
    QWidget *parentWidget;
};

#endif // STORE_H
