#ifndef EDIT_H
#define EDIT_H

#include <QWidget>

namespace Ui {
class edit;
}

class edit : public QWidget
{
    Q_OBJECT

public:
    explicit edit(QWidget *parent = nullptr);
    ~edit();

private slots:
    void on_PbSave_clicked();

private:
    Ui::edit *ui;
};

#endif // EDIT_H
