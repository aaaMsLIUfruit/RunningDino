#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <QWidget>

namespace Ui {
class Background;
}

class Background : public QWidget
{
    Q_OBJECT

public:
    explicit Background(QWidget *parent = nullptr);
    ~Background();

private:
    Ui::Background *ui;
};

#endif // BACKGROUND_H
