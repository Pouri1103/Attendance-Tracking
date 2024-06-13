#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

//-------------------------------------

extern QSqlDatabase db;
extern int moneyTime, moneyGhofl;
extern int rowDays;
extern int rowSnapp;
void setMoneys(QString,QString);
void readMoneys();
void convertTime(int,QString&,QString&);
QString twoDigits(QString);

//-------------------------------------

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void database(QString);
    void mainCode();
    void setZero();
    void editShow();
    void openDB();
    void saveDB();

private slots:
    void on_actionEdit_numbers_triggered();

    void on_PbUpdate_clicked();

    void on_actionSize_Window_triggered();

    void on_actionAdd_Day_triggered();

    void on_actionAdd_Snapp_triggered();

    void on_actionEdit_items_triggered();

    void on_actionDelete_items_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
