#ifndef CHARACTER_H
#define CHARACTER_H

#include <QWidget>
#include <QComboBox>
#include <QLabel>
#include <QPushButton>

namespace Ui {
class Character;
}

class Character : public QWidget
{
    Q_OBJECT

public:
    explicit Character(QWidget *parent = nullptr);
    ~Character();

private:
    Ui::Character *ui;
    void setupUi(); // 设置UI组件
    void setupConnections(); // 设置信号和槽的连接

private slots:
    void onCharacterSelected(const QString &characterName);
    void on_returnButton_clicked(); // 返回按钮的槽函数
};

#endif // CHARACTER_H
