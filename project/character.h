#ifndef CHARACTER_H
#define CHARACTER_H

#include <QWidget>

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
};

#endif // CHARACTER_H
