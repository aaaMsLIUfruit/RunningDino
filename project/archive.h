#ifndef ARCHIVE_H
#define ARCHIVE_H

#include <QWidget>

namespace Ui {
class archive;
}

class archive : public QWidget
{
    Q_OBJECT

public:
    explicit archive(QWidget *parent = nullptr);
    ~archive();

private:
    Ui::archive *ui;
};

#endif // ARCHIVE_H
