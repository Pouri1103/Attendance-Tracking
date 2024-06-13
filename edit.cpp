#include "edit.h"
#include "ui_edit.h"
#include "mainwindow.h"

edit::edit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::edit)
{
    ui->setupUi(this);

    /////////////////////////////////////////////////////////////////

    connect(ui->PbCancel,&QAbstractButton::clicked,this,&edit::close);

    /////////////////////////////////////////////////////////////////

}

edit::~edit()
{
    delete ui;
}

void edit::on_PbSave_clicked()
{
    QString time = ui->LeTime->text();
    QString ghofl = ui->LeGhofl->text();

    if (ui->checkBox->isChecked())
    {
        moneyTime = time.toInt();
        moneyGhofl = ghofl.toInt();
    }
    else {
        setMoneys(time,ghofl);
        readMoneys();
    }

    this->close();

//    MainWindow mm;
//    mm.mainCode();
}

