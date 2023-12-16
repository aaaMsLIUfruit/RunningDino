#include "introduction.h"
#include "ui_introduction.h"
#include "config.h"

#include <QFontDatabase>
#include<QPushButton>
#include <QHBoxLayout>
#include <QMoveEvent>

Introduction::Introduction(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Introduction) {
    // 构造函数，初始化游戏介绍窗口
    ui->setupUi(this);  // 设置UI

    // 设置窗口标题和图标
    setWindowTitle("游戏介绍");
    setWindowIcon(QIcon(GAME_ICON));

    // 导入并设置字体
    int fontId = QFontDatabase::addApplicationFont(QStringLiteral(":/res/ark-pixel-12px-monospaced-zh_cn.ttf"));
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
    QFont font;
    font.setFamily(fontFamilies[0]);  // 选择字体族的第一个字体

    // 设置标签字体
    ui->label->setFont(font);
    ui->label_2->setFont(font);
    ui->label_3->setFont(font);
    ui->label_4->setFont(font);
    ui->label_5->setFont(font);
    ui->label_6->setFont(font);
    ui->label_7->setFont(font);

    // 创建关闭按钮
    QPushButton *closeButton = new QPushButton("关闭介绍", this);
    if (!fontFamilies.isEmpty()) {
        QFont font(fontFamilies[0]);
        closeButton->setFont(font);  // 设置按钮字体
    }

    // 设置布局，并添加关闭按钮
    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->addWidget(closeButton, 0, Qt::AlignTop | Qt::AlignRight);

    // 连接关闭按钮的点击信号到关闭事件
    connect(closeButton, &QPushButton::clicked, this, &Introduction::close);

    // 设置固定窗口大小
    setFixedSize(630, 350);

    // 为父窗口安装事件过滤器，用于调整窗口位置
    if (parent) {
        parent->installEventFilter(this);
    }
}

bool Introduction::eventFilter(QObject *obj, QEvent *event) {
    // 事件过滤器，用于处理窗口移动事件
    if (obj == parent() && event->type() == QEvent::Move) {
        QWidget *parentWidget = qobject_cast<QWidget *>(parent());
        if (parentWidget) {
            QRect parentGeometry = parentWidget->geometry();
            int x = parentGeometry.x() + (parentGeometry.width() - width()) / 2;
            int y = parentGeometry.y() + (parentGeometry.height() - height()) / 2;
            move(x, y);  // 移动窗口以保持居中
        }
    }

    return QWidget::eventFilter(obj, event);  // 返回事件处理结果
}

void Introduction::showEvent(QShowEvent *event) {
    // 显示事件处理
    QDialog::showEvent(event);

    // 确保窗口在父窗口居中
    if (parentWidget()) {
        QRect parentGeometry = parentWidget()->geometry();
        int x = parentGeometry.x() + (parentGeometry.width() - width()) / 2;
        int y = parentGeometry.y() + (parentGeometry.height() - height()) / 2;
        move(x, y);  // 调整位置以居中
    }
}

Introduction::~Introduction() {
    // 析构函数，释放UI资源
    delete ui;
}
