#include "add_snapp.h"
#include "ui_add_snapp.h"
#include "mainwindow.h"
#include <QSqlQuery>
#include <QString>
#include <QTime>

add_snapp::add_snapp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::add_snapp)
{
    ui->setupUi(this);

    /////////////////////////////////////////////////////////////////

    connect(ui->PbCancel,&QAbstractButton::clicked,this,&add_snapp::close);

    /////////////////////////////////////////////////////////////////

}

add_snapp::~add_snapp()
{
    delete ui;
}

void add_snapp::on_PbSave_clicked()
{
    QString row = QString::number(rowSnapp + 1);
    QString s1 = ui->LeS1->text();
    QString s2 = ui->LeS2->text();
    QString s3 = ui->LeS3->text();
    QString s4 = ui->LeS4->text();

    db.exec("insert into snapps values('"+row+"','"+s1+"','"+s2+"','"+s3+"','"+s4+"')");


    this->close();
}

