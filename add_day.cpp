#include "add_day.h"
#include "ui_add_day.h"
#include "mainwindow.h"
#include <QSqlQuery>
#include <QString>
#include <QTime>

add_day::add_day(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::add_day)
{
    ui->setupUi(this);

    /////////////////////////////////////////////////////////////////

    connect(ui->PbCancel,&QAbstractButton::clicked,this,&add_day::close);

    /////////////////////////////////////////////////////////////////    

}

add_day::~add_day()
{
    delete ui;
}

void add_day::on_PbSave_clicked()
{
    QString row = QString::number(rowDays + 1);
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

    db.exec("insert into Days values('"+row+"','"+day+"','"+date+"','"+login+"','"+exit+"','"+total+"','"+location+"','"+lock+"')");


    this->close();
}

