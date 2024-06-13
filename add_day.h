#ifndef ADD_DAY_H
#define ADD_DAY_H

#include <QWidget>

namespace Ui {
class add_day;
}

class add_day : public QWidget
{
    Q_OBJECT

public:
    explicit add_day(QWidget *parent = nullptr);
    ~add_day();

private slots:
    void on_PbSave_clicked();

private:
    Ui::add_day *ui;
};

#endif // ADD_DAY_H
