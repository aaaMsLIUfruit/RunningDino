#ifndef BOSSINTRO_H
#define BOSSINTRO_H

#include <QDialog>

namespace Ui {
class BossIntro;
}

class BossIntro : public QDialog
{
    Q_OBJECT

public:
    explicit BossIntro(QWidget *parent = nullptr);
    ~BossIntro();

signals:
    void BossPlayButton_clicked();

private:
    Ui::BossIntro *ui;
};

#endif // BOSSINTRO_H
