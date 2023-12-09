#include "archive.h"
#include "ui_archive.h"
#include "config.h"

#include <QFontDatabase>
Archive::Archive(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::archive)
{
    ui->setupUi(this);

    int fontId=QFontDatabase::addApplicationFont(QStringLiteral(":/res/ark-pixel-12px-monospaced-zh_cn.ttf"));   //导入字体文件
    QStringList fontFamilies=QFontDatabase::applicationFontFamilies(fontId);
    QFont font;
    font.setFamily(fontFamilies[0]);
    ui->pushButton_1->setFont(font);
    ui->pushButton_2->setFont(font);
    ui->pushButton_3->setFont(font);
    ui->pushButton_4->setFont(font);
    ui->pushButton_5->setFont(font);
    ui->pushButton_6->setFont(font);

    //QDateTime dateTime(QDateTime::currentDateTime());
    //QString qStr = dateTime.toString("yyyy-MM-dd hh:mm:ss ddd");


    // 定义文件名
    for(int i=1;i<=6;i++){
        filenames[i] = QString("settings%1.ini").arg(i);
    }

    // 保存设置到不同的文件
//    archive::saveSettings(filenames[1], "time", "0");//初始化为"0"
//    archive::saveSettings(filenames[2], "time", "0");
//    archive::saveSettings(filenames[3], "time", "0");
//    archive::saveSettings(filenames[4], "time", "0");
//    archive::saveSettings(filenames[5], "time", "0");
//    archive::saveSettings(filenames[6], "time", "0");


    QPushButton *btn[7];
    btn[1]=ui->pushButton_1;
    btn[2]=ui->pushButton_2;
    btn[3]=ui->pushButton_3;
    btn[4]=ui->pushButton_4;
    btn[5]=ui->pushButton_5;
    btn[6]=ui->pushButton_6;


    for(int i=1;i<=6;i++){//加载按钮上的内容
        QVariant varitime=loadSettings(filenames[i],"time","0");
        QVariant varirecord=loadSettings(filenames[i],"record",0);
        QVariant varicoin=loadSettings(filenames[i],"coin",0);


        if (varitime.canConvert<QString>()) {
            qstr[i] = varitime.toString();
        }
        else {
            qstr[i] = "出错啦，嘻嘻。";// 处理无法转换的情况
        }

        if (varirecord.canConvert<int>()) {
            record[i] = varirecord.toInt();
        }
        else {
            record[i] = 0;// 处理无法转换的情况
        }

        if (varicoin.canConvert<int>()) {
            coin[i] = varicoin.toInt();
        }
        else {
            coin[i] = 0;// 处理无法转换的情况
        }

        if(qstr[i]!="0"){
            btn[i]->setText("Coin: "+QString::number(coin[i])+", "+QString::number(record[i])+"m"+"\n"+qstr[i]);
        }
        else{
            btn[i]->setText("null");
        }
    }

    for(int i=1;i<=6;i++){
        connect(btn[i],&QPushButton::clicked,[=](){
            c=coin[i];
            dis=record[i];
            filename=filenames[i];
            this->close();
        });
    }


}

// 在archive类的cpp文件中
void Archive::close() {
    emit aboutToClose();
    QWidget::close();
}

void Archive::saveSettings(const QString &filename, const QString &key, const QVariant &value) {//存数据
    QSettings settings(filename, QSettings::IniFormat);
    settings.setValue(key, value);
}

QVariant Archive::loadSettings(const QString &filename, const QString &key, const QVariant &defaultValue) {//读取数据
    QSettings settings(filename, QSettings::IniFormat);
    return settings.value(key, defaultValue);
}

Archive::~Archive()
{
    delete ui;
}
