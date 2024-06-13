#ifndef WINSIZE_H
#define WINSIZE_H

#include <QWidget>

namespace Ui {
class winsize;
}

class winsize : public QWidget
{
    Q_OBJECT

public:
    explicit winsize(QWidget *parent = nullptr);
    ~winsize();

private slots:
    void on_PbSave_clicked();

private:
    Ui::winsize *ui;
};

#endif // WINSIZE_H
