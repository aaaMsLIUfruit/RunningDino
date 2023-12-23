#ifndef PROP_H
#define PROP_H

#include <QWidget>
#include <QComboBox>
#include <QPushButton>

class Store;

namespace Ui {
class Prop;
}

class Prop : public QWidget
{
    Q_OBJECT

public:
    explicit Prop(QWidget *parent = nullptr, int coinValue = 0);
    ~Prop();

    int coin;
    Store *storePtr = nullptr;

signals:
    void propSelected(const QString &propName);
    void coinChanged(const int &newCoinValue);

private slots:
    void onPropSelected(const QString &propName);
    void on_returnButton_clicked();

private:
    Ui::Prop *ui;
    void setupUi();
    void setupConnections();  // 设置信号和槽的连接
};

#endif // PROP_H
