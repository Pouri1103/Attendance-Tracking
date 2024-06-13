#ifndef EDIT_ITEMS_H
#define EDIT_ITEMS_H

#include <QWidget>

namespace Ui {
class edit_items;
}

class edit_items : public QWidget
{
    Q_OBJECT

public:
    explicit edit_items(QWidget *parent = nullptr);
    ~edit_items();

private slots:
    void on_PbSave_clicked();

private:
    Ui::edit_items *ui;
};

#endif // EDIT_ITEMS_H
