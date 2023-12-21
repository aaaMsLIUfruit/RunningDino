#ifndef INTRODUCTION_H
#define INTRODUCTION_H

#include <QDialog>
#include<QIcon>
#include <QWidget>

namespace Ui {
class Introduction;
}

class Introduction : public QDialog {
    Q_OBJECT

public:
    // 构造函数
    explicit Introduction(QWidget *parent = nullptr);
    // 析构函数
    ~Introduction();

protected:
    // 事件过滤器，用于处理窗口移动事件
    bool eventFilter(QObject *obj, QEvent *event) override;
    // 显示事件处理，用于调整窗口位置
    void showEvent(QShowEvent *event) override;

private:
    Ui::Introduction *ui; // 指向UI界面的指针
};


#endif // INTRODUCTION_H
