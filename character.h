#ifndef CHARACTER_H
#define CHARACTER_H

#include <QWidget>
#include <QString>

class Store;

namespace Ui {
class Character;
}

// 定义角色枚举

class Character : public QWidget
{
    Q_OBJECT

public:
    explicit Character(QWidget *parent = nullptr, int coinValue = 0);
    ~Character();

    int coin;
    Store *storePtr = nullptr;

signals:
    void characterSelected(const QString &characterName);
    void coinChanged(const int &newCoinValue);

private slots:
    void onCharacterSelected(const QString &characterName);
    void on_returnButton_clicked();

private:
    Ui::Character *ui;

    void setupFont();         // 设置字体
    void setupUi();           // 设置UI元素
    void setupConnections();  // 设置信号和槽的连接
};

#endif // CHARACTER_H
