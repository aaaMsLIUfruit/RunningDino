#ifndef PROP_H
#define PROP_H

#include <QWidget>
#include <QComboBox>
#include <QPushButton>

namespace Ui {
class Prop;
}

class Prop : public QWidget
{
    Q_OBJECT

public:
    explicit Prop(QWidget *parent = nullptr);
    ~Prop();

private slots:
    void onPropSelected(const QString &propName);
    void on_returnButton_clicked();

private:
    Ui::Prop *ui;
    void setupUi();
    void setupConnections();
};

#endif // PROP_H
