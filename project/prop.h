#ifndef PROP_H
#define PROP_H

#include <QWidget>

namespace Ui {
class Prop;
}

class Prop : public QWidget
{
    Q_OBJECT

public:
    explicit Prop(QWidget *parent = nullptr);
    ~Prop();

private:
    Ui::Prop *ui;
};

#endif // PROP_H
