#ifndef DELETE_ITEMS_H
#define DELETE_ITEMS_H

#include <QWidget>

namespace Ui {
class delete_items;
}

class delete_items : public QWidget
{
    Q_OBJECT

public:
    explicit delete_items(QWidget *parent = nullptr);
    ~delete_items();

private slots:
    void on_PbDelete_clicked();

private:
    Ui::delete_items *ui;
};

#endif // DELETE_ITEMS_H
