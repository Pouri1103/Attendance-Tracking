#ifndef ADD_SNAPP_H
#define ADD_SNAPP_H

#include <QWidget>

namespace Ui {
class add_snapp;
}

class add_snapp : public QWidget
{
    Q_OBJECT

public:
    explicit add_snapp(QWidget *parent = nullptr);
    ~add_snapp();

private slots:
    void on_PbSave_clicked();

private:
    Ui::add_snapp *ui;
};

#endif // ADD_SNAPP_H
