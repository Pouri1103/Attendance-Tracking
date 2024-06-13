#include "edit_items.h"
#include "ui_edit_items.h"
#include "mainwindow.h"
#include <QSqlQuery>
#include <QString>
#include <QTime>

edit_items::edit_items(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::edit_items)
{
    ui->setupUi(this);

    /////////////////////////////////////////////////////////////////

    connect(ui->PbCancel,&QAbstractButton::clicked,this,&edit_items::close);

    /////////////////////////////////////////////////////////////////

}

edit_items::~edit_items()
{
    delete ui;
}

void edit_items::on_PbSave_clicked()
{
    QString id = ui->number->text();

    if (ui->RbDay->isChecked())
    {
        QString day = ui->LeDay->text();
        QString date = ui->LeDate->text();
        QString login = ui->LeLogin->text();
        QString exit = ui->LeExit->text();
        QString location = ui->LeLocation->text();
        QString lock = ui->LeLock->text();

        QTime loginT = QTime::fromString(login);
        QTime exitT = QTime::fromString(exit);
        QString total, min, hour;
        int totalT = loginT.secsTo(exitT);
        convertTime(totalT,min,hour);
        total = twoDigits(hour) + ":" + twoDigits(min);

        db.exec("update Days set day='"+day+"',date='"+date+"',login='"+login+"',exit='"+exit+"',"
        "total='"+total+"',location='"+location+"',lock='"+lock+"' where id='"+id+"'");
    }

    else if (ui->RbSnapp->isChecked())
    {
        QString s1 = ui->LeS1->text();
        QString s2 = ui->LeS2->text();
        QString s3 = ui->LeS3->text();
        QString s4 = ui->LeS4->text();

        db.exec("update snapps set one='"+s1+"',two='"+s2+"',three='"+s3+"',four='"+s4+"' where id='"+id+"'");
    }


    this->close();
}

