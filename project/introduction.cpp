#include "introduction.h"
#include "ui_introduction.h"
#include "config.h"

#include <QFontDatabase>
#include<QPushButton>
#include <QHBoxLayout>
#include <QMoveEvent>

Introduction::Introduction(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Introduction)
{
    ui->setupUi(this);

    setWindowTitle("游戏介绍");
    setWindowIcon(QIcon(GAME_ICON));

    int fontId=QFontDatabase::addApplicationFont(QStringLiteral(":/res/ark-pixel-12px-monospaced-zh_cn.ttf"));   //导入字体文件
    QStringList fontFamilies=QFontDatabase::applicationFontFamilies(fontId);
    QFont font;
    font.setFamily(fontFamilies[0]);
    ui->label->setFont(font);
    ui->label_2->setFont(font);
    ui->label_3->setFont(font);
    ui->label_4->setFont(font);
    ui->label_5->setFont(font);
    ui->label_6->setFont(font);
    ui->label_7->setFont(font);

    QPushButton *closeButton = new QPushButton("关闭介绍", this);
    if (!fontFamilies.isEmpty())
    {
        QFont font(fontFamilies[0]);
        closeButton->setFont(font);
    }

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(closeButton, 0, Qt::AlignTop | Qt::AlignRight);

    connect(closeButton, &QPushButton::clicked, this, &Introduction::close);

    setFixedSize(630,350);

    //为父窗口安装事件过滤器
    if (parent) {
            parent->installEventFilter(this);
        }
}

bool Introduction::eventFilter(QObject *obj, QEvent *event) {
    if (obj == parent() && event->type() == QEvent::Move) {
        QWidget *parentWidget = qobject_cast<QWidget *>(parent());
        if (parentWidget) {
            QRect parentGeometry = parentWidget->geometry();
            int x = parentGeometry.x() + (parentGeometry.width() - width()) / 2;
            int y = parentGeometry.y() + (parentGeometry.height() - height()) / 2;
            move(x, y);
        }
    }

    return QWidget::eventFilter(obj, event);
}

void Introduction::showEvent(QShowEvent *event) {
    QDialog::showEvent(event);

    if (parentWidget()) {
        QRect parentGeometry = parentWidget()->geometry();
        int x = parentGeometry.x() + (parentGeometry.width() - width()) / 2;
        int y = parentGeometry.y() + (parentGeometry.height() - height()) / 2;
        move(x, y);
    }
}


Introduction::~Introduction()
{
    delete ui;
}
