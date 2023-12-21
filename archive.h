#ifndef ARCHIVE_H
#define ARCHIVE_H

#include <QWidget>
#include <QSettings>
#include <QVariant>
#include <QDateTime>
#include <QString>
#include <QCloseEvent>

//存档

namespace Ui {
class archive;
}

class Archive : public QWidget
{
    Q_OBJECT

signals:
    void aboutToClose();

public:
    explicit Archive(QWidget *parent = nullptr);
    ~Archive();
public:
    static void saveSettings(const QString &filename, const QString &key, const QVariant &value);
    static QVariant loadSettings(const QString &filename, const QString &key, const QVariant &defaultValue = QVariant());
    QString qstr[7];
    int record[7];
    int coin[7];
    int c=0,dis=0;     //金币、距离
    QString filename;         //存档
    QString filenames[7];
    void close();

private:
    Ui::archive *ui;
};

#endif // ARCHIVE_H
