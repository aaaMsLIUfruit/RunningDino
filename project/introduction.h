#ifndef INTRODUCTION_H
#define INTRODUCTION_H

#include <QDialog>
#include<QIcon>
#include <QWidget>

namespace Ui {
class Introduction;
}

class Introduction : public QDialog
{
    Q_OBJECT

public:
    explicit Introduction(QWidget *parent = nullptr);
    ~Introduction();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;
    void showEvent(QShowEvent *event) override;

private:
    Ui::Introduction *ui;
};

#endif // INTRODUCTION_H
