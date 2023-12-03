#ifndef INTRODUCTION_H
#define INTRODUCTION_H

#include <QDialog>
#include<QIcon>
namespace Ui {
class Introduction;
}

class Introduction : public QDialog
{
    Q_OBJECT

public:
    explicit Introduction(QWidget *parent = nullptr);
    ~Introduction();

private:
    Ui::Introduction *ui;
};

#endif // INTRODUCTION_H
