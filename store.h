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

class MainWindow;

class Store : public QWidget
{
    Q_OBJECT

signals:
    void characterChangedInStore(const QString &characterName);
    void backgroundChangedInStore(const QString &backgroundName);
    void propChangedInStore(const QString &propName);
    void coinChanged(const int &newCoinValue);

public:
    explicit Store(QWidget *parent = nullptr);
    ~Store();

    Character *character=new Character;
    Prop *prop = new Prop;
    Background *background = new Background;
    MainWindow *mainWindowPtr;
    int coin;

    void showComponents();

public slots:
    void onCharacterChanged(const QString &characterName);
    void onBackgroundChanged(const QString &backgroundName);
    void onPropChanged(const QString &propName);
    void onCoinChanged(const int &newCoinValue);

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
