#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <QWidget>
#include <QComboBox>
#include <QPushButton>

namespace Ui {
class Background;
}

class Background : public QWidget
{
    Q_OBJECT

public:
    explicit Background(QWidget *parent = nullptr);
    ~Background();

private slots:
    void onBackgroundSelected(const QString &backgroundName);
    void on_returnButton_clicked();

private:
    Ui::Background *ui;
    void setupUi();
    void setupConnections();
};

#endif // BACKGROUND_H
