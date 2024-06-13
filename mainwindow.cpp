#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "edit.h"
#include "winsize.h"
#include "add_day.h"
#include "add_snapp.h"
#include "edit_items.h"
#include "delete_items.h"
#include <QFileDialog>
#include <QFile>
#include <QIODevice>
#include <QMessageBox>
#include <QTextStream>
#include <QLocale>
#include <QTime>
#include <QTimer>
#include <QtMath>

#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QSqlQueryModel>


////////////////////////////////////
//   values

QSqlDatabase db;

int moneyTime, moneyGhofl;
int rowDays, rowSnapp;

////////////////////////////////////

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /////////////////////////////////////////////////////////////////
    //   connections

    connect(ui->actionExit,&QAction::triggered,this,&MainWindow::close);
    connect(ui->actionOpen,&QAction::triggered,this,&MainWindow::openDB);
    connect(ui->actionSave,&QAction::triggered,this,&MainWindow::saveDB);

    /////////////////////////////////////////////////////////////////
    //   exist database & set tables

    QFile exist("DataDB.db");
    //-------------------------------------
    if (exist.exists())
    {
        database("DataDB.db");
        readMoneys();
        if (moneyTime==0 || moneyGhofl==0)
            QTimer::singleShot(2000,[this]{editShow();});
    }
    //-------------------------------------
    else {
        database("DataDB.db");

        db.exec("create table Days(ID integer primary key, Day text, Date text, Login real, Exit real,Total real, Location text, Lock integer)");

        db.exec("create table snapps(ID integer primary key,one integer,two integer,three integer,four integer)");

        db.exec("create table settings(Name text, ValuesInt integer)");

        setZero();

        editShow();
    }
    //-------------------------------------

//    db.exec("insert into Days values(1,'شنبه','1402/05/07', '09:10', '18:25', '9:15', 'چیتگر', 120)");
//    db.exec("insert into Days values(2,'سه شنبه','1402/06/22' , '10:50', '22:40', '11:50', 'هنگام', 60)");

//    db.exec("insert into snapps values(1,200,54,0,0)");
//    db.exec("insert into snapps values(2,0,110,33,0)");
//    db.exec("insert into snapps values(3,90,32,1,44)");

    /////////////////////////////////////////////////////////////////

    mainCode();

    /////////////////////////////////////////////////////////////////

}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::database(QString addressDB)
{
    db= db.addDatabase("QSQLITE");
    db.setDatabaseName(addressDB);
    db.open();
}

void MainWindow::mainCode()
{
    /////////////////////////////////////////////////////////////////
    //   read table days

    QSqlQuery qDay;
    qDay.exec("select * from Days");
    QSqlQueryModel *m = new QSqlQueryModel;
    m->setQuery(std::move(qDay)); //setQuery(qDay);
    ui->tableView_2->setModel(m);

    /////////////////////////////////////////////////////////////////
    //   read table snapps

    QSqlQuery qSnapp;
    qSnapp.exec("select * from snapps");
    QSqlQueryModel *m2 = new QSqlQueryModel;
    m2->setQuery(std::move(qSnapp));  //setQuery(qSnapp);
    ui->tableView->setModel(m2);

    /////////////////////////////////////////////////////////////////
    //   set color table

    ui->tableView->setAlternatingRowColors(true);
    ui->tableView_2->setAlternatingRowColors(true);

    /////////////////////////////////////////////////////////////////
    //   sum and set snapps

    int sumSnapp=0;
    rowSnapp = m2->rowCount();

    QSqlQuery qSumSnapp;
    qSumSnapp.exec("select one,two,three,four from snapps");

    for (int row=1; row<=rowSnapp;row++)
        if (qSumSnapp.next()) {
            sumSnapp += qSumSnapp.value(0).toInt();
            sumSnapp += qSumSnapp.value(1).toInt();
            sumSnapp += qSumSnapp.value(2).toInt();
            sumSnapp += qSumSnapp.value(3).toInt();
        }

    ui->lebSnapp->setText(QString::number(rowSnapp));
    ui->lebSnappTotal->setText(QLocale().toString(sumSnapp * 1000));

    /////////////////////////////////////////////////////////////////
    //   sum and set ghofl

    int sumGhofl=0;
    rowDays=m->rowCount();

    QSqlQuery qSumGhofl;
    qSumGhofl.exec("select Lock from Days");

    for (int row2=1; row2<=rowDays;row2++)
        if (qSumGhofl.next())
            sumGhofl += qSumGhofl.value(0).toInt();

    ui->lebGhofl->setText(QLocale().toString(sumGhofl));
    ui->lebGhoflTotal->setText(QLocale().toString(sumGhofl * moneyGhofl));

    /////////////////////////////////////////////////////////////////
    //   sum and set time

    int total=0;
    QString min, hour;
    QTime loginT;
    QTime exitT;

    QSqlQuery qtime;
    qtime.exec("select Login,Exit from Days");
    for (int row3=1; row3<=rowDays;row3++)
    {
        if (qtime.next()) {
            loginT = qtime.value(0).toTime();
            exitT = qtime.value(1).toTime();
            total += loginT.secsTo(exitT);
        }
    }
    convertTime(total, min, hour);
    ui->lebTime->setText(twoDigits(hour) + ":" + twoDigits(min));

    /////////////////////////////////////////////////////////////////
    //   set money for time

    double timeTotal = hour.toInt() + min.toFloat()/60;

    ui->lebTimeTotal->setText(QLocale().toString(qCeil(timeTotal*moneyTime / 1000) * 1000));

    /////////////////////////////////////////////////////////////////
    //   sum and set all total

    int allSum=  ui->lebTimeTotal->text().toInt() +
                 sumGhofl * moneyGhofl +
                 sumSnapp * 1000 +
                 qCeil(timeTotal*moneyTime / 1000) * 1000;

    ui->allTotal->setText(QLocale().toString(allSum));

    /////////////////////////////////////////////////////////////////

}

void MainWindow::openDB()
{
    QString address = QFileDialog::getOpenFileName(this,"Open a dataBase...");
    database(address);
}

void MainWindow::saveDB()
{
    QString address = QFileDialog::getSaveFileName(this,"save this dataBase...","DataDB","database(*.db)");

    QFile::copy("DataDB.db",address);
}

void convertTime(int sec,QString& min,QString& hour)
{
    int toMin= sec/60;
    min= QString::number(toMin%60);
    hour= QString::number((toMin-min.toInt())/60);
}

QString twoDigits(QString number)
{
    if (number.toInt() < 10)
        number = "0" + number;
    return number;
}

void MainWindow::editShow()
{
    edit *Edit = new edit;
    Edit->show();
}

void setMoneys(QString moneytime, QString moneyghofl)
{
    QSqlQuery qMTime,qMGhofl;
    qMTime.exec("update settings set valuesInt='"+moneytime+"' where name='moneyTime'");
    qMGhofl.exec("update settings set valuesInt='"+moneyghofl+"' where name='moneyGhofl'");
}

void MainWindow::setZero()
{
    db.exec("insert into settings values('moneyTime', 0)");
    db.exec("insert into settings values('moneyGhofl', 0)");
}

void readMoneys()
{
    QSqlQuery qsetTime, qsetGhofl;
    qsetTime.exec("select valuesInt from settings where name='moneyTime'");
    qsetGhofl.exec("select valuesInt from settings where name='moneyGhofl'");

    if (qsetTime.first() && qsetGhofl.first()) {
        moneyTime = qsetTime.value(0).toInt();
        moneyGhofl = qsetGhofl.value(0).toInt();
    }
}



void MainWindow::on_actionEdit_numbers_triggered()
{
    editShow();
}

void MainWindow::on_actionSize_Window_triggered()
{
    winsize *win = new winsize;
    win->show();
}

void MainWindow::on_actionAdd_Day_triggered()
{
    add_day *addDay = new add_day;
    addDay->show();
}

void MainWindow::on_actionAdd_Snapp_triggered()
{
    add_snapp *addSnapp = new add_snapp;
    addSnapp->show();
}

void MainWindow::on_actionEdit_items_triggered()
{
    edit_items *editItems = new edit_items;
    editItems->show();
}

void MainWindow::on_actionDelete_items_triggered()
{
    delete_items *deleteI = new delete_items;
    deleteI->show();
}

void MainWindow::on_PbUpdate_clicked()
{
    mainCode(); 
}
