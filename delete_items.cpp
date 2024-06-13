#include "delete_items.h"
#include "ui_delete_items.h"
#include "mainwindow.h"
#include <QSqlQuery>

delete_items::delete_items(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::delete_items)
{
    ui->setupUi(this);

    /////////////////////////////////////////////////////////////////

    connect(ui->PbCancel,&QAbstractButton::clicked,this,&delete_items::close);

    /////////////////////////////////////////////////////////////////

}

delete_items::~delete_items()
{
    delete ui;
}

void delete_items::on_PbDelete_clicked()
{
    QString id = ui->number->text();

    if (ui->RbDay->isChecked())
    {
        db.exec("delete from days where id='"+id+"'");
        db.exec("update days set id=id-1 where id > '"+id+"'");
    }

    else if (ui->RbSnapp->isChecked())
    {
        db.exec("delete from snapps where id='"+id+"'");
        db.exec("update snapps set id=id-1 where id > '"+id+"'");
    }


    this->close();
}

